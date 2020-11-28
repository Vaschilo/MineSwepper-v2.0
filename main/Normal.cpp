/*Нормальный уровень*/

#include "libheader.h"

int n(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Surface*& screen, q& g)
{
	srand(time(NULL));

	char text[100];			//текст на счетчике
	int h = 0, h2 = 0;		//игровые переменные
	int Marks = NOBN;			//считает кол-во флажков на карте
	int Bombs = 0;			//считает кол-во раздифуженных бомб
	int Cletk = 0;			//считает кол-во открытых клеток
	int coco = 0;			//используется в вычислении - какую кнопку нажали
	int co = 0;				//используется в отрисовке
	SDL_Rect rect;
	int m = 0;				//0 = нет сохр. игры;	1 = есть сохр. игра
	bool gameprocess = 0;	//0 = lose;				1 = win

	SDL_Event event;
	bool exit = true;

	g.sp = getsp("normal.txt", 0);
	if (g.sp == -1) { FILE* f; fopen_s(&f, "normal.txt", "w"); fprintf_s(f, "%d %d", 0, 0); fclose(f); g.sp = 0; }
	else m = getsp("normal.txt", 1);

	if (!m) init(g, H_pole, H_pole, NOBN);
	else
	{

		SDL_RenderClear(renderer);
		rect.y = rect.x = 0; rect.w = WIDTH; rect.h = HEIGHT;
		draw_texture(renderer, rect, "bmp_menu//mainmenufon.bmp");
		rect = { 934,85,201,262 };
		draw_texture(renderer, rect, "n_h_level//sp.bmp");
		rect.x = WIDTH / 2 - 250; rect.w = 500; rect.h = 58;
		rect.y = HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 30 - HEIGHT / 12 + HEIGHT / 15;
		draw_texture(renderer, rect, "n_h_level//withs.bmp");
		rect.y = HEIGHT / 2 - HEIGHT / 24 + HEIGHT / 15;
		draw_texture(renderer, rect, "n_h_level//withouts.bmp");
		rect.y = HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 30 + HEIGHT / 15;
		draw_texture(renderer, rect, "n_h_level//onglm.bmp");
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
				fopen_s(&f, "normal.txt", "r");
				fscanf_s(f, "%d ", &g.sp);
				fscanf_s(f, "%d ", &m);
				for (int i = 0; i < H_pole * H_pole; i++)
					fscanf_s(f, "%d ", &g.real[i]);
				for (int i = 0; i < H_pole * H_pole; i++)
				{
					fscanf_s(f, "%d ", &g.game[i]);
				}
				fclose(f);
				for (int i = 0; i < H_pole * H_pole; i++)
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
				init(g, H_pole, H_pole, NOBN);
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
	{
		rect.x = 0; rect.y = 0; rect.w = WIDTH; rect.h = HEIGHT;		draw_texture(renderer, rect, "fon.bmp");
		rect = { 35,85,210,260 }; draw_texture(renderer, rect, "n_h_level//fl.bmp");
		rect = { 934,85,201,262 }; draw_texture(renderer, rect, "n_h_level//sp.bmp");
		rect.x = 270; rect.y = HEIGHT - 25; rect.w = 631; rect.h = 1;	draw_texture(renderer, rect, "n_h_level//gp_n.bmp");
		rect.x = WIDTH - 270; rect.y = 63; rect.h = 612; rect.w = 1;	draw_texture(renderer, rect, "n_h_level//vp.bmp");
		rect.w = 35; rect.h = 34;	for (rect.x = 270; rect.x < WIDTH - 270 - 1; rect.x += 35) draw_texture(renderer, rect, "n_h_level//wall.bmp");
		rect.y = HEIGHT - 25 - 34;	for (rect.x = 270; rect.x < WIDTH - 270 - 1; rect.x += 35) draw_texture(renderer, rect, "n_h_level//wall.bmp");
		rect.x = 270;				for (rect.y = 63; rect.y < HEIGHT - 34 - 1; rect.y += 34) draw_texture(renderer, rect, "n_h_level//wall.bmp");
		rect.x = WIDTH - 270 - 35;	for (rect.y = 63; rect.y < HEIGHT - 34 - 1; rect.y += 34) draw_texture(renderer, rect, "n_h_level//wall.bmp");
	}
	//Рамка
	{
		rect.w = 35;
		rect.h = 34;
		for (rect.y = 97; rect.y < HEIGHT - 34 - 25 - 1; rect.y += 34)
			for (rect.x = 305; rect.x < WIDTH - 305 - 1; rect.x += 35)
			{
				if (g.game[co] == 1)
				{
					if (g.real[co] == 0)draw_texture(renderer, rect, "n_h_level//0.bmp");
					if (g.real[co] == 1)draw_texture(renderer, rect, "n_h_level//1.bmp");
					if (g.real[co] == 2)draw_texture(renderer, rect, "n_h_level//2.bmp");
					if (g.real[co] == 3)draw_texture(renderer, rect, "n_h_level//3.bmp");
					if (g.real[co] == 4)draw_texture(renderer, rect, "n_h_level//4.bmp");
					if (g.real[co] == 5)draw_texture(renderer, rect, "n_h_level//5.bmp");
					if (g.real[co] == 6)draw_texture(renderer, rect, "n_h_level//6.bmp");
					if (g.real[co] == 7)draw_texture(renderer, rect, "n_h_level//7.bmp");
					if (g.real[co] == 8)draw_texture(renderer, rect, "n_h_level//8.bmp");
				}
				else
				{
					if (g.game[co] == -1) draw_texture(renderer, rect, "n_h_level//flag.bmp");
					if (g.game[co] == 0) draw_texture(renderer, rect, "n_h_level//grass.bmp");
				}
				co++;
			}
	}
	//Отрисовка игр поля
	rect = { 50,450,190,200 }; draw_texture(renderer, rect, "n_h_level//endegm.bmp");
	rect = { 930,450,190,200 }; draw_texture(renderer, rect, "n_h_level//endexit.bmp");
	_itoa_s(Marks, text, 10, 10);
	draw_text(renderer, text, 50, 100, 200, 171);
	_itoa_s(g.sp, text, 10, 10);
	draw_text(renderer, text, WIDTH - 171 - 50, 100, 200, 171);
	SDL_RenderPresent(renderer);
	m = 2;
	while (exit)
	{
		SDL_PollEvent(&event);

		if ((event.type == SDL_QUIT) || ((event.button.x >= 930) &&
			(event.button.x <= 1120) &&
			(event.button.y >= 450) &&
			(event.button.y <= 650) &&
			(event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)))
		{
			exit = false;
			FILE* f;
			fopen_s(&f, "normal.txt", "w");
			fprintf_s(f, "%d ", g.sp);
			fprintf_s(f, "%d ", 1);
			for (int i = 0; i < H_pole * H_pole; i++) fprintf_s(f, "%d ", g.real[i]);
			for (int i = 0; i < H_pole * H_pole; i++) fprintf_s(f, "%d ", g.game[i]);
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
			fopen_s(&f, "normal.txt", "w");
			fprintf_s(f, "%d ", g.sp);
			fprintf_s(f, "%d ", 1);
			for (int i = 0; i < H_pole * H_pole; i++) fprintf_s(f, "%d ", g.real[i]);
			for (int i = 0; i < H_pole * H_pole; i++) fprintf_s(f, "%d ", g.game[i]);
			fclose(f);
			SDL_Delay(500);
			return 1;
		}
		if ((event.button.button == SDL_BUTTON_LEFT) && (event.type == SDL_MOUSEBUTTONDOWN))
		{
			coco = checktouch(event.button.x, event.button.y, 305, WIDTH - 306, 35, 97, HEIGHT - 60, 34);
			if (coco >= 0)
			{
				rect = { 0,0,35,34 };
				if ((g.real[coco] == 9) && (g.game[coco] == 0)) { exit = false; gameprocess = 0; }
				if (g.game[coco] == 1)
				{
					co = 0;
					h = schet(g, H_pole, H_pole, coco, 1);
					h2 = schet(g, H_pole, H_pole, coco, -1);
					if (coco - H_pole >= 0) co++;
					if (coco + H_pole <= H_pole * H_pole) co++;
					if ((coco + 1) % H_pole) co++;
					if (coco % H_pole) co++;
					if ((coco - H_pole >= 0) && (coco % H_pole)) co++;
					if ((coco - H_pole >= 0) && ((coco + 1) % H_pole)) co++;
					if ((coco + H_pole < H_pole * H_pole) && (coco % H_pole)) co++;
					if ((coco + H_pole < H_pole * H_pole) && ((coco + 1) % H_pole)) co++;
					if (h == co - g.real[coco])
					{
						if ((coco - H_pole >= 0) && (g.game[coco - H_pole] == 0)) { g.game[coco - H_pole] = -1; Marks--; if (g.real[coco - H_pole] == 9) Bombs++; }
						if ((coco + H_pole < H_pole * H_pole) && (g.game[coco + H_pole] == 0)) { g.game[coco + H_pole] = -1; Marks--; if (g.real[coco + H_pole] == 9) Bombs++; }
						if (((coco + 1) % H_pole) && (g.game[coco + 1] == 0)) { g.game[coco + 1] = -1; Marks--; if (g.real[coco + 1] == 9) Bombs++; }
						if ((coco % H_pole) && (g.game[coco - 1] == 0)) { g.game[coco - 1] = -1; Marks--; if (g.real[coco - 1] == 9) Bombs++; }
						if ((coco - H_pole >= 0) && (coco % H_pole) && (g.game[coco - H_pole - 1] == 0)) { g.game[coco - H_pole - 1] = -1; Marks--; if (g.real[coco - H_pole - 1] == 9) Bombs++; }
						if ((coco - H_pole >= 0) && ((coco + 1) % H_pole) && (g.game[coco - H_pole + 1] == 0)) { g.game[coco - H_pole + 1] = -1; Marks--; if (g.real[coco - H_pole + 1] == 9) Bombs++; }
						if ((coco + H_pole < H_pole * H_pole) && (coco % H_pole) && (g.game[coco + H_pole - 1] == 0)) { g.game[coco + H_pole - 1] = -1; Marks--;  if (g.real[coco + H_pole - 1] == 9) Bombs++; }
						if ((coco + H_pole < H_pole * H_pole) && ((coco + 1) % H_pole) && (g.game[coco + H_pole + 1] == 0)) { g.game[coco + H_pole + 1] = -1; Marks--;  if (g.real[coco + H_pole + 1] == 9) Bombs++; }
					}
					if (h2 == g.real[coco])
					{
						if ((coco - H_pole >= 0) && (g.game[coco - H_pole] != -1)) {
							open(g, coco - H_pole, H_pole, H_pole); if (g.real[coco - H_pole] == 9) { exit = false; gameprocess = 0; }
						}
						if ((coco + H_pole < H_pole * H_pole) && (g.game[coco + H_pole] != -1)) {
							open(g, coco + H_pole, H_pole, H_pole); if (g.real[coco + H_pole] == 9) { exit = false; gameprocess = 0; }
						}
						if (((coco + 1) % H_pole) && (g.game[coco + 1] != -1)) {
							open(g, coco + 1, H_pole, H_pole); if (g.real[coco + 1] == 9) { exit = false; gameprocess = 0; }
						}
						if ((coco % H_pole) && (g.game[coco - 1] != -1)) {
							open(g, coco - 1, H_pole, H_pole); if (g.real[coco - 1] == 9) { exit = false; gameprocess = 0; }
						}
						if ((coco - H_pole >= 0) && (coco % H_pole) && (g.game[coco - H_pole - 1] != -1)) {
							open(g, coco - H_pole - 1, H_pole, H_pole); if (g.real[coco - H_pole - 1] == 9) { exit = false; gameprocess = 0; }
						}
						if ((coco - 9 >= 0) && ((coco + 1) % H_pole) && (g.game[coco - H_pole + 1] != -1)) {
							open(g, coco - H_pole + 1, H_pole, H_pole); if (g.real[coco - H_pole + 1] == 9) { exit = false; gameprocess = 0; }
						}
						if ((coco + H_pole < H_pole * H_pole) && (coco % H_pole) && (g.game[coco + H_pole - 1] != -1)) {
							open(g, coco + H_pole - 1, H_pole, H_pole); if (g.real[coco + H_pole - 1] == 9) { exit = false; gameprocess = 0; }
						}
						if ((coco + H_pole < H_pole * H_pole) && ((coco + 1) % H_pole) && (g.game[coco + H_pole + 1] != -1)) {
							open(g, coco + H_pole + 1, H_pole, H_pole); if (g.real[coco + H_pole + 1] == 9) { exit = false; gameprocess = 0; }
						}
					}

				}
				else if (g.game[coco] != -1)  open(g, coco, H_pole, H_pole);
				Cletk = 0; for (int i = 0; i < H_pole * H_pole; i++) if (g.game[i] == 1) Cletk++;
				co = 0;
				for (rect.y = 97; rect.y < HEIGHT - 34 - 25 - 1; rect.y += 34)
					for (rect.x = 305; rect.x < WIDTH - 305 - 1; rect.x += 35)
					{
						if (g.game[co] == 1)
						{
							if (g.real[co] == 0)draw_texture(renderer, rect, "n_h_level//0.bmp");
							if (g.real[co] == 1)draw_texture(renderer, rect, "n_h_level//1.bmp");
							if (g.real[co] == 2)draw_texture(renderer, rect, "n_h_level//2.bmp");
							if (g.real[co] == 3)draw_texture(renderer, rect, "n_h_level//3.bmp");
							if (g.real[co] == 4)draw_texture(renderer, rect, "n_h_level//4.bmp");
							if (g.real[co] == 5)draw_texture(renderer, rect, "n_h_level//5.bmp");
							if (g.real[co] == 6)draw_texture(renderer, rect, "n_h_level//6.bmp");
							if (g.real[co] == 7)draw_texture(renderer, rect, "n_h_level//7.bmp");
							if (g.real[co] == 8)draw_texture(renderer, rect, "n_h_level//8.bmp");
						}
						else
						{
							if (g.game[co] == -1) draw_texture(renderer, rect, "n_h_level//flag.bmp");
							if (g.game[co] == 0) draw_texture(renderer, rect, "n_h_level//grass.bmp");
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
			m = 1;
			rect = { 0,0,35,34 };
			coco = checktouch(event.button.x, event.button.y, 305, WIDTH - 306, 35, 97, HEIGHT - 60, 34);
			if ((coco + 1) && (g.game[coco] != 1))
			{
				if (g.game[coco] == -1) { g.game[coco] = 0; Marks++; if (g.real[coco] == 9) Bombs--; }
				else { g.game[coco] = -1; Marks--; if (g.real[coco] == 9) Bombs++; }
				co = 0;
				for (rect.y = 97; rect.y < HEIGHT - 34 - 25 - 1; rect.y += 34)
					for (rect.x = 305; rect.x < WIDTH - 305 - 1; rect.x += 35)
					{
						if (g.game[co] == -1) draw_texture(renderer, rect, "n_h_level//flag.bmp");
						if (g.game[co] == 0) draw_texture(renderer, rect, "n_h_level//grass.bmp");
						co++;
					}
				_itoa_s(Marks, text, 10, 10);
				draw_text(renderer, text, 50, 100, 200, 171);
				SDL_RenderPresent(renderer);
				SDL_Delay(100);
			}
		}
		if ((Marks < 0)&&(!gameprocess))
		{
			rect = { 35,345,210,45 };
			draw_texture(renderer, rect, "n_h_level//warning.bmp");
			SDL_RenderPresent(renderer);
			gameprocess = 1;
		}
		if ((Marks == 0)&&(gameprocess))
		{
			gameprocess = 0;
			rect = { 35,345,210,45 };
			draw_texture(renderer, rect, "n_h_level//antiwarning.bmp");
			SDL_RenderPresent(renderer);
		}
		if (((Marks == 0) && (Bombs == NOBN)) || (Cletk == H_pole * H_pole - NOBN))
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
		draw_texture(renderer, rect, "n_h_level//sp.bmp");
		_itoa_s(++g.sp, text, 10, 10);
		draw_text(renderer, text, 949, 100, 200, 171);
		rect = { 35,85,210,260 };
		draw_texture(renderer, rect, "n_h_level//WIN.bmp");
	}
	else { g.sp = 0; rect = { 35,85,210,260 }; draw_texture(renderer, rect, "n_h_level//LOSE.bmp"); }
	rect = { 50,450,190,200 }; draw_texture(renderer, rect, "n_h_level//endegm.bmp");
	rect = { 930,450,190,200 }; draw_texture(renderer, rect, "n_h_level//endexit.bmp");
	rect = { 300,100,570,215 };
	{
		rect.x = 270; rect.y = HEIGHT - 25; rect.w = 631; rect.h = 1;	draw_texture(renderer, rect, "n_h_level//gp_n.bmp");
		rect.x = WIDTH - 270; rect.y = 63; rect.h = 612; rect.w = 1;	draw_texture(renderer, rect, "n_h_level//vp.bmp");
		rect.w = 35; rect.h = 34;	for (rect.x = 270; rect.x < WIDTH - 270 - 1; rect.x += 35) draw_texture(renderer, rect, "n_h_level//wall.bmp");
		rect.y = HEIGHT - 25 - 34;	for (rect.x = 270; rect.x < WIDTH - 270 - 1; rect.x += 35) draw_texture(renderer, rect, "n_h_level//wall.bmp");
		rect.x = 270;				for (rect.y = 63; rect.y < HEIGHT - 34 - 1; rect.y += 34) draw_texture(renderer, rect, "n_h_level//wall.bmp");
		rect.x = WIDTH - 270 - 35;	for (rect.y = 63; rect.y < HEIGHT - 34 - 1; rect.y += 34) draw_texture(renderer, rect, "n_h_level//wall.bmp");
	}
	//Рамка
	{
		co = 0;
		rect.w = 35;
		rect.h = 34;
		for (rect.y = 97; rect.y < HEIGHT - 34 - 25 - 1; rect.y += 34)
			for (rect.x = 305; rect.x < WIDTH - 305 - 1; rect.x += 35)
			{
				if ((g.game[co] == 1) || ((g.game[co] == -1) && (g.real[co] != 9)))
				{
					if (g.real[co] == 0)draw_texture(renderer, rect, "n_h_level//0.bmp");
					if (g.real[co] == 1)draw_texture(renderer, rect, "n_h_level//1.bmp");
					if (g.real[co] == 2)draw_texture(renderer, rect, "n_h_level//2.bmp");
					if (g.real[co] == 3)draw_texture(renderer, rect, "n_h_level//3.bmp");
					if (g.real[co] == 4)draw_texture(renderer, rect, "n_h_level//4.bmp");
					if (g.real[co] == 5)draw_texture(renderer, rect, "n_h_level//5.bmp");
					if (g.real[co] == 6)draw_texture(renderer, rect, "n_h_level//6.bmp");
					if (g.real[co] == 7)draw_texture(renderer, rect, "n_h_level//7.bmp");
					if (g.real[co] == 8)draw_texture(renderer, rect, "n_h_level//8.bmp");
					if (g.real[co] == 9)draw_texture(renderer, rect, "n_h_level//boom.bmp");
					if (g.game[co] == -1) g.game[co] = 1;
				}
				else
				{
					if (g.game[co] == -1) draw_texture(renderer, rect, "n_h_level//bwf.bmp");
					if (g.game[co] == 0)
					{
						if (g.real[co] == 0)draw_texture(renderer, rect, "n_h_level//0.bmp");
						if (g.real[co] == 1)draw_texture(renderer, rect, "n_h_level//1.bmp");
						if (g.real[co] == 2)draw_texture(renderer, rect, "n_h_level//2.bmp");
						if (g.real[co] == 3)draw_texture(renderer, rect, "n_h_level//3.bmp");
						if (g.real[co] == 4)draw_texture(renderer, rect, "n_h_level//4.bmp");
						if (g.real[co] == 5)draw_texture(renderer, rect, "n_h_level//5.bmp");
						if (g.real[co] == 6)draw_texture(renderer, rect, "n_h_level//6.bmp");
						if (g.real[co] == 7)draw_texture(renderer, rect, "n_h_level//7.bmp");
						if (g.real[co] == 8)draw_texture(renderer, rect, "n_h_level//8.bmp");
						if (g.real[co] == 9)draw_texture(renderer, rect, "n_h_level//bomb.bmp");

					}
				}
				co++;
			}
	}
	//Отрисовка игр поля
	SDL_RenderPresent(renderer);
	FILE* f;
	fopen_s(&f, "normal.txt", "w");
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