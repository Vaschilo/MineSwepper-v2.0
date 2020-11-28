/*Лёгкий уровень*/

#include "libheader.h"

int e(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Surface*& screen,q& g)
{
	srand(time(NULL));

	char text[100];			//текст на счетчике
	int h = 0, h2 = 0;		//игровые переменные
	int Marks = 10;			//считает кол-во флажков на карте
	int Bombs = 0;			//считает кол-во раздифуженных бомб
	int Cletk = 0;			//считает кол-во открытых клеток
	int coco = 0;			//используется в вычислении - какую кнопку нажали
	int co = 0;				//используется в отрисовке
	SDL_Rect rect;
	int m = 0;				//0 = нет сохр. игры;	1 = есть сохр. игра
	bool gameprocess = 0;	//0 = lose;				1 = win

	SDL_Event event;
	bool exit = true;

	g.sp = getsp("easy.txt", 0);
	if (g.sp == -1) { FILE* f; fopen_s(&f, "easy.txt", "w"); fprintf_s(f, "%d %d", 0, 0); fclose(f); g.sp = 0;}
	else m = getsp("easy.txt", 1);

	if (m == 0) init(g, Pole, Pole, NOBE);
	else
	{
		SDL_RenderClear(renderer);
		rect.y = rect.x = 0; rect.w = WIDTH; rect.h = HEIGHT;
		draw_texture(renderer, rect, "bmp_menu//mainmenufon.bmp");
		rect = { 934,85,201,262 };
		draw_texture(renderer, rect, "easy_level//sp.bmp");
		rect.x = WIDTH / 2 - 250; rect.w = 500; rect.h = 58;
		rect.y = HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 30 - HEIGHT / 12 + HEIGHT / 15;
		draw_texture(renderer, rect, "easy_level//withs.bmp");
		rect.y = HEIGHT / 2 - HEIGHT / 24 + HEIGHT / 15;
		draw_texture(renderer, rect, "easy_level//withouts.bmp");
		rect.y = HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 30 + HEIGHT / 15;
		draw_texture(renderer, rect, "easy_level//onglm.bmp");
		_itoa_s(g.sp, text, 10, 10);
		draw_text(renderer, text, 949, 100, 200, 171);
		SDL_RenderPresent(renderer);
		while (true)
		{
			SDL_PollEvent(&event);
			if (event.type == SDL_QUIT) return 0;
			if ((event.button.x >= WIDTH / 2 - WIDTH / 4) &&
				(event.button.x <= WIDTH - WIDTH / 4) &&
				(event.button.y >= HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 30 - HEIGHT / 12 + HEIGHT / 15) &&
				(event.button.y <= HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 30 - HEIGHT / 12 + HEIGHT / 15 + HEIGHT / 12) &&
				(event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
			{
				/* снизу считывается*/
				FILE* f;
				fopen_s(&f, "easy.txt", "r");
				fscanf_s(f, "%d ", &g.sp);
				fscanf_s(f, "%d ", &m);
				for (int i = 0; i < Pole * Pole; i++)
					fscanf_s(f, "%d ", &g.real[i]);
				for (int i = 0; i < Pole * Pole; i++)
					fscanf_s(f, "%d ", &g.game[i]);
				fclose(f);
				for (int i = 0; i < Pole * Pole; i++)
				{
					if (g.game[i] == -1)
					{
						Marks--;
						if (g.real[i] == 9) Bombs++;
					}
				}
				break;
			}
			if ((event.button.x >= WIDTH / 2 - WIDTH / 4) &&
				(event.button.x <= WIDTH - WIDTH / 4) &&
				(event.button.y >= HEIGHT / 2 - HEIGHT / 24 + HEIGHT / 15) &&
				(event.button.y <= HEIGHT / 2 - HEIGHT / 24 + HEIGHT / 15 + HEIGHT / 12) &&
				(event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) 
			{
				init(g, Pole, Pole, NOBE);
				g.sp = 0;
				break;
			}
			if ((event.button.x >= WIDTH / 2 - WIDTH / 4) &&
				(event.button.x <= WIDTH - WIDTH / 4) &&
				(event.button.y >= HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 30 + HEIGHT / 15) &&
				(event.button.y <= HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 30 + HEIGHT / 15 + HEIGHT / 12) &&
				(event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
			{
				SDL_Delay(400);
				return 1;
			}
		}
	}
	SDL_RenderClear(renderer);
	{
		rect.x = 0; rect.y = 0; rect.w = WIDTH; rect.h = HEIGHT;		draw_texture(renderer, rect, "fon.bmp");
		rect = { 35,85,210,260 }; draw_texture(renderer, rect, "easy_level//fl.bmp");
		rect = { 934,85,201,262 }; draw_texture(renderer, rect, "easy_level//sp.bmp");
		rect.x = 271; rect.y = HEIGHT - 25; rect.w = 628; rect.h = 1;	draw_texture(renderer, rect, "easy_level//rp.bmp");
		rect.x = WIDTH - 272; rect.y = 48; rect.h = 627; rect.w = 1;	draw_texture(renderer, rect, "easy_level//vp.bmp");
		rect.w = 57; rect.h = 57; for(rect.x = 271; rect.x < WIDTH - 272; rect.x += 57) draw_texture(renderer, rect, "easy_level//wall.bmp");
		rect.y = HEIGHT - 82;		for (rect.x = 271; rect.x < WIDTH - 272; rect.x += 57) draw_texture(renderer, rect, "easy_level//wall.bmp");
		rect.x = 271;				for (rect.y = 48; rect.y < HEIGHT - 82; rect.y += 57) draw_texture(renderer, rect, "easy_level//wall.bmp");
		rect.x = WIDTH - 329;		for (rect.y = 48; rect.y < HEIGHT - 82; rect.y += 57) draw_texture(renderer, rect, "easy_level//wall.bmp");
	}
	//Рамка
	{
		rect.w = rect.h = 57;
		for (rect.y = 105; rect.y < HEIGHT - 138; rect.y += 57)
			for (rect.x = 328; rect.x < WIDTH - 329; rect.x += 57)
			{
				if (g.game[co] == 1)
				{
					if (g.real[co] == 0)draw_texture(renderer, rect, "easy_level//0.bmp");
					if (g.real[co] == 1)draw_texture(renderer, rect, "easy_level//1.bmp");
					if (g.real[co] == 2)draw_texture(renderer, rect, "easy_level//2.bmp");
					if (g.real[co] == 3)draw_texture(renderer, rect, "easy_level//3.bmp");
					if (g.real[co] == 4)draw_texture(renderer, rect, "easy_level//4.bmp");
					if (g.real[co] == 5)draw_texture(renderer, rect, "easy_level//5.bmp");
					if (g.real[co] == 6)draw_texture(renderer, rect, "easy_level//6.bmp");
					if (g.real[co] == 7)draw_texture(renderer, rect, "easy_level//7.bmp");
					if (g.real[co] == 8)draw_texture(renderer, rect, "easy_level//8.bmp");
				}
				else
				{
					if (g.game[co] == -1) draw_texture(renderer, rect, "easy_level//flag.bmp");
					if (g.game[co] == 0) draw_texture(renderer, rect, "easy_level//grass.bmp");
				}
				co++;
			}
	}  
	//Отрисовка игр поля
	rect = { 50,450,190,200 }; draw_texture(renderer, rect, "easy_level//endegm.bmp");
	rect = { 930,450,190,200 }; draw_texture(renderer, rect, "easy_level//endexit.bmp");
	_itoa_s(Marks, text, 10, 10);
	draw_text(renderer, text, 50, 100, 200, 171);
	_itoa_s(g.sp, text, 10, 10);
	draw_text(renderer, text, WIDTH - 171 - 50, 100, 200, 171);
	SDL_RenderPresent(renderer);
	m = 2;
	while (exit)
	{
		SDL_PollEvent(&event);

		if ((event.type == SDL_QUIT)|| ((event.button.x >= 930) &&
			(event.button.x <= 1120) &&
			(event.button.y >= 450) &&
			(event.button.y <= 650) &&
			(event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)))
		{
			exit = false; 
			FILE* f;
			fopen_s(&f, "easy.txt", "w"); 
			fprintf_s(f, "%d ", g.sp);
			fprintf_s(f, "%d ", 1);
			for (int i = 0; i < Pole * Pole; i++) fprintf_s(f, "%d ", g.real[i]);
			for (int i = 0; i < Pole * Pole; i++) fprintf_s(f, "%d ", g.game[i]);
			fclose(f);
			return 0;
		}
		if ((event.button.x >= 50) &&
			(event.button.x <= 240) &&
			(event.button.y >= 450) &&
			(event.button.y <= 650) &&
			(event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
		{
			exit = false;
			FILE* f;
			fopen_s(&f, "easy.txt", "w");
			fprintf_s(f, "%d ", g.sp);
			fprintf_s(f, "%d ", 1);
			for (int i = 0; i < Pole * Pole; i++) fprintf_s(f, "%d ", g.real[i]);
			for (int i = 0; i < Pole * Pole; i++) fprintf_s(f, "%d ", g.game[i]);
			fclose(f);
			SDL_Delay(500);
			return 1;
		}
		if ((event.button.button == SDL_BUTTON_LEFT)&&(event.type == SDL_MOUSEBUTTONDOWN))
		{
			coco = checktouch(event.button.x, event.button.y, 328, WIDTH - 329, 57, 105, HEIGHT - 138, 57);
			if (coco >= 0)
			{
				rect = { 0,0,57,57 };
				if ((g.real[coco] == 9) && (g.game[coco] == 0)) { exit = false; gameprocess = 0; }
				if (g.game[coco] == 1)
				{
					co = 0;
					h = schet(g, Pole, Pole, coco, 1);
					h2 = schet(g, Pole, Pole, coco, -1);
					if (coco - 9 >= 0) co++;
					if (coco + 9 <= Pole * Pole) co++;
					if ((coco + 1) % Pole) co++;
					if (coco % Pole) co++;
					if ((coco - 9 >= 0) && (coco % Pole)) co++;
					if ((coco - 9 >= 0) && ((coco + 1) % Pole)) co++;
					if ((coco + 9 < 81) && (coco % Pole)) co++;
					if ((coco + 9 < 81) && ((coco + 1) % Pole)) co++;
					if (h == co - g.real[coco])
					{
						if ((coco - 9 >= 0) && (g.game[coco - 9] == 0)) { g.game[coco - 9] = -1; Marks--; if (g.real[coco - 9] == 9) Bombs++; }
						if ((coco + 9 < 81) && (g.game[coco + 9] == 0)) { g.game[coco + 9] = -1; Marks--; if (g.real[coco + 9] == 9) Bombs++; }
						if (((coco + 1) % Pole) && (g.game[coco + 1] == 0)) { g.game[coco + 1] = -1; Marks--; if (g.real[coco + 1] == 9) Bombs++; }
						if ((coco % Pole) && (g.game[coco - 1] == 0)) { g.game[coco - 1] = -1; Marks--; if (g.real[coco - 1] == 9) Bombs++; }
						if ((coco - 9 >= 0) && (coco % Pole) && (g.game[coco - 10] == 0)) { g.game[coco - 10] = -1; Marks--; if (g.real[coco - 10] == 9) Bombs++; }
						if ((coco - 9 >= 0) && ((coco + 1) % Pole) && (g.game[coco - 8] == 0)) { g.game[coco - 8] = -1; Marks--; if (g.real[coco - 8] == 9) Bombs++; }
						if ((coco + 9 < 81) && (coco % Pole) && (g.game[coco + 8] == 0)) { g.game[coco + 8] = -1; Marks--;  if (g.real[coco + 8] == 9) Bombs++; }
						if ((coco + 9 < 81) && ((coco + 1) % Pole) && (g.game[coco + 10] == 0)) { g.game[coco + 10] = -1; Marks--;  if (g.real[coco + 10] == 9) Bombs++; }
					}
					if (h2 == g.real[coco])
					{
						if ((coco - 9 >= 0) && (g.game[coco - 9] != -1)) {
							open(g, coco - 9, Pole, Pole); if (g.real[coco - 9] == 9) { exit = false; gameprocess = 0; }
						}
						if ((coco + 9 < 81) && (g.game[coco + 9] != -1)) {
							open(g, coco + 9, Pole, Pole); if (g.real[coco + 9] == 9) { exit = false; gameprocess = 0; }
						}
						if (((coco + 1) % Pole) && (g.game[coco + 1] != -1)) {
							open(g, coco + 1, Pole, Pole); if (g.real[coco + 1] == 9) { exit = false; gameprocess = 0; }
						}
						if ((coco % Pole) && (g.game[coco - 1] != -1)) {
							open(g, coco - 1, Pole, Pole); if (g.real[coco - 1] == 9) { exit = false; gameprocess = 0; }
						}
						if ((coco - 9 >= 0) && (coco % Pole) && (g.game[coco - 10] != -1)) {
							open(g, coco - 10, Pole, Pole); if (g.real[coco - 10] == 9) { exit = false; gameprocess = 0; }
						}
						if ((coco - 9 >= 0) && ((coco + 1) % Pole) && (g.game[coco - 8] != -1)) {
							open(g, coco - 8, Pole, Pole); if (g.real[coco - 8] == 9) { exit = false; gameprocess = 0; }
						}
						if ((coco + 9 < 81) && (coco % Pole) && (g.game[coco + 8] != -1)) {
							open(g, coco + 8, Pole, Pole); if (g.real[coco + 8] == 9) { exit = false; gameprocess = 0; }
						}
						if ((coco + 9 < 81) && ((coco + 1) % Pole) && (g.game[coco + 10] != -1)) {
							open(g, coco + 10, Pole, Pole); if (g.real[coco + 10] == 9) { exit = false; gameprocess = 0; }
						}
					}
				}
				else if (g.game[coco] != -1) open(g, coco, Pole, Pole); 
				Cletk = 0; for (int i = 0; i < Pole * Pole; i++) if (g.game[i] == 1) Cletk++; 
				co = 0;
				for (rect.y = 105; rect.y < HEIGHT - 138; rect.y += 57)
					for (rect.x = 328; rect.x < WIDTH - 329; rect.x += 57)
					{
						if (g.game[co] == 1)
						{
							if (g.real[co] == 0)draw_texture(renderer, rect, "easy_level//0.bmp");
							if (g.real[co] == 1)draw_texture(renderer, rect, "easy_level//1.bmp");
							if (g.real[co] == 2)draw_texture(renderer, rect, "easy_level//2.bmp");
							if (g.real[co] == 3)draw_texture(renderer, rect, "easy_level//3.bmp");
							if (g.real[co] == 4)draw_texture(renderer, rect, "easy_level//4.bmp");
							if (g.real[co] == 5)draw_texture(renderer, rect, "easy_level//5.bmp");
							if (g.real[co] == 6)draw_texture(renderer, rect, "easy_level//6.bmp");
							if (g.real[co] == 7)draw_texture(renderer, rect, "easy_level//7.bmp");
							if (g.real[co] == 8)draw_texture(renderer, rect, "easy_level//8.bmp");
						}
						else
						{
							if (g.game[co] == -1) draw_texture(renderer, rect, "easy_level//flag.bmp");
							if (g.game[co] == 0) draw_texture(renderer, rect, "easy_level//grass.bmp");
						}
						co++;
					}
				_itoa_s(Marks, text, 10, 10);
				draw_text(renderer, text, 50, 100, 200, 171);
				SDL_RenderPresent(renderer);
			}
		} 
		if ((event.button.button == SDL_BUTTON_RIGHT) && (event.type == SDL_MOUSEBUTTONUP) && (m == 1)) m = 2;
		if ((event.button.button == SDL_BUTTON_RIGHT) && (event.type == SDL_MOUSEBUTTONDOWN) && (m == 2))
		{
			rect = { 0,0,57,57 };
			coco = checktouch(event.button.x, event.button.y, 328, WIDTH - 329, 57, 105, HEIGHT - 138, 57);
			if ((coco + 1) && (g.game[coco] != 1))
			{
				if (g.game[coco] == -1) { g.game[coco] = 0; Marks++; if (g.real[coco] == 9) Bombs--; }
				else { g.game[coco] = -1; Marks--; if (g.real[coco] == 9) Bombs++; }
				co = 0;
				for (rect.y = 105; rect.y < HEIGHT - 138; rect.y += 57)
					for (rect.x = 328; rect.x < WIDTH - 329; rect.x += 57)
					{
						if (g.game[co] == -1) draw_texture(renderer, rect, "easy_level//flag.bmp");
						if (g.game[co] == 0) draw_texture(renderer, rect, "easy_level//grass.bmp");
						co++;
					}
				_itoa_s(Marks, text, 10, 10);
				draw_text(renderer, text, 50, 100, 200, 171);
				m = 1;
				SDL_RenderPresent(renderer);
				SDL_Delay(100);
			}
		}
		if ((Marks < 0)&&(!gameprocess))
		{
			rect = { 35,345,210,45 };
			draw_texture(renderer, rect, "easy_level//warning.bmp");
			SDL_RenderPresent(renderer);
			gameprocess = 1;
		}
		if ((Marks == 0) && (gameprocess))
		{
			gameprocess = 0;
			rect = { 35,345,210,45 };
			draw_texture(renderer, rect, "easy_level//antiwarning.bmp");
			SDL_RenderPresent(renderer);
		}
		if (((Marks == 0) && (Bombs == NOBE)) || (Cletk == Pole * Pole - NOBE))
		{
			exit = false;
			gameprocess = 1;
		}
	}
	SDL_Delay(700);
	SDL_RenderClear(renderer);

		rect.y = rect.x = 0; rect.w = WIDTH; rect.h = HEIGHT;
		draw_texture(renderer, rect, "fon.bmp");
		if (gameprocess)
		{
			rect = { 934,85,201,262 };
			draw_texture(renderer, rect, "easy_level//sp.bmp");
			_itoa_s(++g.sp, text, 10, 10);
			draw_text(renderer, text, 949, 100, 200, 171);
			rect = { 35,85,210,260 };
			draw_texture(renderer, rect, "easy_level//WIN.bmp");
		}
		else {g.sp = 0; rect = { 35,85,210,260 };draw_texture(renderer, rect, "easy_level//LOSE.bmp");}
		rect = { 50,450,190,200 }; draw_texture(renderer, rect, "easy_level//endegm.bmp");
		rect = { 930,450,190,200 }; draw_texture(renderer, rect, "easy_level//endexit.bmp");
		rect = { 300,100,570,215 };
		{
			rect.x = 271; rect.y = HEIGHT - 25; rect.w = 628; rect.h = 1;	draw_texture(renderer, rect, "easy_level//rp.bmp");
			rect.x = WIDTH - 272; rect.y = 48; rect.h = 627; rect.w = 1;	draw_texture(renderer, rect, "easy_level//vp.bmp");
			rect.w = 57; rect.h = 57; for (rect.x = 271; rect.x < WIDTH - 272; rect.x += 57) draw_texture(renderer, rect, "easy_level//wall.bmp");
			rect.y = HEIGHT - 82;		for (rect.x = 271; rect.x < WIDTH - 272; rect.x += 57) draw_texture(renderer, rect, "easy_level//wall.bmp");
			rect.x = 271;				for (rect.y = 48; rect.y < HEIGHT - 82; rect.y += 57) draw_texture(renderer, rect, "easy_level//wall.bmp");
			rect.x = WIDTH - 329;		for (rect.y = 48; rect.y < HEIGHT - 82; rect.y += 57) draw_texture(renderer, rect, "easy_level//wall.bmp");
		}
		//Рамка
		{
			co = 0;
			rect.w = rect.h = 57;
			for (rect.y = 105; rect.y < HEIGHT - 138; rect.y += 57)
				for (rect.x = 328; rect.x < WIDTH - 329; rect.x += 57)
				{
					if ((g.game[co] == 1) || ((g.game[co] == -1) && (g.real[co] != 9)))
					{
						if (g.real[co] == 0)draw_texture(renderer, rect, "easy_level//0.bmp");
						if (g.real[co] == 1)draw_texture(renderer, rect, "easy_level//1.bmp");
						if (g.real[co] == 2)draw_texture(renderer, rect, "easy_level//2.bmp");
						if (g.real[co] == 3)draw_texture(renderer, rect, "easy_level//3.bmp");
						if (g.real[co] == 4)draw_texture(renderer, rect, "easy_level//4.bmp");
						if (g.real[co] == 5)draw_texture(renderer, rect, "easy_level//5.bmp");
						if (g.real[co] == 6)draw_texture(renderer, rect, "easy_level//6.bmp");
						if (g.real[co] == 7)draw_texture(renderer, rect, "easy_level//7.bmp");
						if (g.real[co] == 8)draw_texture(renderer, rect, "easy_level//8.bmp");
						if (g.real[co] == 9)draw_texture(renderer, rect, "easy_level//bomb.bmp");
						if (g.game[co] == -1) g.game[co] = 1;
					}
					else
					{
						if (g.game[co] == -1) draw_texture(renderer, rect, "easy_level//bwf.bmp");
						if (g.game[co] == 0)
						{
							if (g.real[co] == 0)draw_texture(renderer, rect, "easy_level//0.bmp");
							if (g.real[co] == 1)draw_texture(renderer, rect, "easy_level//1.bmp");
							if (g.real[co] == 2)draw_texture(renderer, rect, "easy_level//2.bmp");
							if (g.real[co] == 3)draw_texture(renderer, rect, "easy_level//3.bmp");
							if (g.real[co] == 4)draw_texture(renderer, rect, "easy_level//4.bmp");
							if (g.real[co] == 5)draw_texture(renderer, rect, "easy_level//5.bmp");
							if (g.real[co] == 6)draw_texture(renderer, rect, "easy_level//6.bmp");
							if (g.real[co] == 7)draw_texture(renderer, rect, "easy_level//7.bmp");
							if (g.real[co] == 8)draw_texture(renderer, rect, "easy_level//8.bmp");
							if (g.real[co] == 9)draw_texture(renderer, rect, "easy_level//boom.bmp");
							
						}
					}
					co++;
				}
		}
		//Отрисовка игр поля
		SDL_RenderPresent(renderer);
		FILE* f;
		fopen_s(&f, "easy.txt", "w");
		fprintf_s(f, "%d 0", g.sp);
		fclose(f);

		while (true)
		{
			SDL_PollEvent(&event);
			if (event.type == SDL_QUIT) return 0;
			if ((event.button.x >= 50) &&
				(event.button.x <= 240) &&
				(event.button.y >= 450) &&
				(event.button.y <= 650) &&
				(event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
			{
				SDL_Delay(500);
				return 1;
			}
			if ((event.button.x >= 930) &&
				(event.button.x <= 1120) &&
				(event.button.y >= 450) &&
				(event.button.y <= 650) &&
				(event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
			{
				return 0;
			}
		}
		return 0;
}