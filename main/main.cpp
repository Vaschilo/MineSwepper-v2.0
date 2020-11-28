/*В этом файле находится main. Здесь описана менюшка, запускается музыка и др.*/

#include "libheader.h"
int r(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Surface*& screen);
int e(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Surface*& screen, q& g);
int n(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Surface*& screen, q& g);
int h(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Surface*& screen, q& g);

#define O		//on/off music

int main(int argc, char* argv[])
{
	int b = -1;
	q g;

	SDL_Window* window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface* screen = SDL_GetWindowSurface(window);
	SDL_RenderClear(renderer);

#ifdef ON
	//=========MUSIC==========//
	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
	loadmusic("1.wav");
	/*sound("1.wav");*/
#endif

	//Проверка существования файлов
	FILE* f;
	fopen_s(&f, "easy.txt", "r");
	if (f == NULL) system("echo -1 > easy.txt");
	else
	{
		if (b == -1) fscanf_s(f, "%d", &b);
		fclose(f);
	}
	fopen_s(&f, "normal.txt", "r");
	if (f == NULL) system("echo -1 > normal.txt");
	else
	{
		if (b == -1) fscanf_s(f, "%d", &b);
		fclose(f);
	}
	fopen_s(&f, "hard.txt", "r");
	if (f == NULL) system("echo -1 > hard.txt");
	else
	{
		if (b == -1) fscanf_s(f, "%d", &b);
		fclose(f);
	}
	b++;

	SDL_UpdateWindowSurface(window);

	//Кнопки в меню
	SDL_Rect rect;
	rect.x = 0; rect.y = 0; rect.w = WIDTH; rect.h = HEIGHT;
	if (b) draw_texture(renderer, rect, "bmp_menu//mainmenufon.bmp");
	else draw_texture(renderer, rect, "bmp_menu//errmainmenufon.bmp");

	rect.x = WIDTH / 2 - 250;	//width of buttons 500, height 58 //СПАСИБО, Я ИЗ ПРОШЛОГО, ТЫ КРАСАААВА
	rect.y = HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 6;
	rect.h = 58; rect.w = 500;
	if (b) draw_texture(renderer, rect, "bmp_menu//easy.bmp");
	else draw_texture(renderer, rect, "bmp_menu//easybl.bmp");

	rect.y = HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 30 - HEIGHT / 12 + HEIGHT / 15;
	if (b) draw_texture(renderer, rect, "bmp_menu//normal.bmp");
	else draw_texture(renderer, rect, "bmp_menu//normalbl.bmp");

	rect.y = HEIGHT / 2 - HEIGHT / 24 + HEIGHT / 15;
	if (b) draw_texture(renderer, rect, "bmp_menu//hard.bmp");
	else draw_texture(renderer, rect, "bmp_menu//hardbl.bmp");

	rect.y = HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 30 + HEIGHT / 15;
	draw_texture(renderer, rect, "bmp_menu//rules.bmp");

	rect.y = HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 15 + HEIGHT / 12 + HEIGHT / 15;
	draw_texture(renderer, rect, "bmp_menu//exit.bmp");

	SDL_RenderPresent(renderer);


	SDL_Event event;
	bool exit = true;

	while (exit)
	{
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT) exit = false;

		if ((event.button.x >= WIDTH / 2 - WIDTH / 4) &&
			(event.button.x <= WIDTH - WIDTH / 4) &&
			(event.button.y >= HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 15 - HEIGHT / 6 + HEIGHT / 15) &&
			(event.button.y <= HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 15 - HEIGHT / 6 + HEIGHT / 15 + HEIGHT / 12) &&
			(event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT) && (b))
		{
			if (!e(window, renderer, screen, g)) exit = false;
			else
			{
				SDL_RenderClear(renderer);
				rect.x = 0; rect.y = 0; rect.w = WIDTH; rect.h = HEIGHT;
				if (b) draw_texture(renderer, rect, "bmp_menu//mainmenufon.bmp");
				else draw_texture(renderer, rect, "bmp_menu//errmainmenufon.bmp");

				rect.x = WIDTH / 2 - 250;	//width of buttons 500, height 58 //СПАСИБО, Я ИЗ ПРОШЛОГО
				rect.y = HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 6;
				rect.h = 58; rect.w = 500;
				if (b) draw_texture(renderer, rect, "bmp_menu//easy.bmp");
				else draw_texture(renderer, rect, "bmp_menu//easybl.bmp");

				rect.y = HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 30 - HEIGHT / 12 + HEIGHT / 15;
				if (b) draw_texture(renderer, rect, "bmp_menu//normal.bmp");
				else draw_texture(renderer, rect, "bmp_menu//normalbl.bmp");

				rect.y = HEIGHT / 2 - HEIGHT / 24 + HEIGHT / 15;
				if (b) draw_texture(renderer, rect, "bmp_menu//hard.bmp");
				else draw_texture(renderer, rect, "bmp_menu//hardbl.bmp");

				rect.y = HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 30 + HEIGHT / 15;
				draw_texture(renderer, rect, "bmp_menu//rules.bmp");

				rect.y = HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 15 + HEIGHT / 12 + HEIGHT / 15;
				draw_texture(renderer, rect, "bmp_menu//exit.bmp");

				SDL_RenderPresent(renderer);
			}
		}

		if ((event.button.x >= WIDTH / 2 - WIDTH / 4) &&
			(event.button.x <= WIDTH - WIDTH / 4) &&
			(event.button.y >= HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 30 - HEIGHT / 12 + HEIGHT / 15) &&
			(event.button.y <= HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 30 - HEIGHT / 12 + HEIGHT / 15 + HEIGHT / 12) &&
			(event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT) && (b))
		{
			if (!n(window, renderer, screen, g)) exit = false;
			else
			{
				SDL_RenderClear(renderer);
				rect.x = 0; rect.y = 0; rect.w = WIDTH; rect.h = HEIGHT;
				if (b) draw_texture(renderer, rect, "bmp_menu//mainmenufon.bmp");
				else draw_texture(renderer, rect, "bmp_menu//errmainmenufon.bmp");

				rect.x = WIDTH / 2 - 250;	//width of buttons 500, height 58
				rect.y = HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 6;
				rect.h = 58; rect.w = 500;
				if (b) draw_texture(renderer, rect, "bmp_menu//easy.bmp");
				else draw_texture(renderer, rect, "bmp_menu//easybl.bmp");

				rect.y = HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 30 - HEIGHT / 12 + HEIGHT / 15;
				if (b) draw_texture(renderer, rect, "bmp_menu//normal.bmp");
				else draw_texture(renderer, rect, "bmp_menu//normalbl.bmp");

				rect.y = HEIGHT / 2 - HEIGHT / 24 + HEIGHT / 15;
				if (b) draw_texture(renderer, rect, "bmp_menu//hard.bmp");
				else draw_texture(renderer, rect, "bmp_menu//hardbl.bmp");

				rect.y = HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 30 + HEIGHT / 15;
				draw_texture(renderer, rect, "bmp_menu//rules.bmp");

				rect.y = HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 15 + HEIGHT / 12 + HEIGHT / 15;
				draw_texture(renderer, rect, "bmp_menu//exit.bmp");

				SDL_RenderPresent(renderer);
			}
		}

		if ((event.button.x >= WIDTH / 2 - WIDTH / 4) &&
			(event.button.x <= WIDTH - WIDTH / 4) &&
			(event.button.y >= HEIGHT / 2 - HEIGHT / 24 + HEIGHT / 15) &&
			(event.button.y <= HEIGHT / 2 - HEIGHT / 24 + HEIGHT / 15 + HEIGHT / 12) &&
			(event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT) && (b))
		{
			if (!h(window, renderer, screen, g)) exit = false;
			else
			{
				SDL_RenderClear(renderer);
				rect.x = 0; rect.y = 0; rect.w = WIDTH; rect.h = HEIGHT;
				if (b) draw_texture(renderer, rect, "bmp_menu//mainmenufon.bmp");
				else draw_texture(renderer, rect, "bmp_menu//errmainmenufon.bmp");

				rect.x = WIDTH / 2 - 250;	//width of buttons 500, height 58
				rect.y = HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 6;
				rect.h = 58; rect.w = 500;
				if (b) draw_texture(renderer, rect, "bmp_menu//easy.bmp");
				else draw_texture(renderer, rect, "bmp_menu//easybl.bmp");

				rect.y = HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 30 - HEIGHT / 12 + HEIGHT / 15;
				if (b) draw_texture(renderer, rect, "bmp_menu//normal.bmp");
				else draw_texture(renderer, rect, "bmp_menu//normalbl.bmp");

				rect.y = HEIGHT / 2 - HEIGHT / 24 + HEIGHT / 15;
				if (b) draw_texture(renderer, rect, "bmp_menu//hard.bmp");
				else draw_texture(renderer, rect, "bmp_menu//hardbl.bmp");

				rect.y = HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 30 + HEIGHT / 15;
				draw_texture(renderer, rect, "bmp_menu//rules.bmp");

				rect.y = HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 15 + HEIGHT / 12 + HEIGHT / 15;
				draw_texture(renderer, rect, "bmp_menu//exit.bmp");

				SDL_RenderPresent(renderer);
			}
		}

		if ((event.button.x >= WIDTH / 2 - WIDTH / 4) &&
			(event.button.x <= WIDTH - WIDTH / 4) &&
			(event.button.y >= HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 30 + HEIGHT / 15) &&
			(event.button.y <= HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 30 + HEIGHT / 15 + HEIGHT / 12) &&
			(event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
		{

			if (!r(window, renderer, screen)) exit = false;
			else
			{
				b = 1;
				SDL_RenderClear(renderer);
				rect.x = 0; rect.y = 0; rect.w = WIDTH; rect.h = HEIGHT;
				if (b) draw_texture(renderer, rect, "bmp_menu//mainmenufon.bmp");
				else draw_texture(renderer, rect, "bmp_menu//errmainmenufon.bmp");

				rect.x = WIDTH / 2 - 250;	//width of buttons 500, height 58
				rect.y = HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 6;
				rect.h = 58; rect.w = 500;
				if (b) draw_texture(renderer, rect, "bmp_menu//easy.bmp");
				else draw_texture(renderer, rect, "bmp_menu//easybl.bmp");

				rect.y = HEIGHT / 2 - HEIGHT / 24 - HEIGHT / 30 - HEIGHT / 12 + HEIGHT / 15;
				if (b) draw_texture(renderer, rect, "bmp_menu//normal.bmp");
				else draw_texture(renderer, rect, "bmp_menu//normalbl.bmp");

				rect.y = HEIGHT / 2 - HEIGHT / 24 + HEIGHT / 15;
				if (b) draw_texture(renderer, rect, "bmp_menu//hard.bmp");
				else draw_texture(renderer, rect, "bmp_menu//hardbl.bmp");

				rect.y = HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 30 + HEIGHT / 15;
				draw_texture(renderer, rect, "bmp_menu//rules.bmp");

				rect.y = HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 15 + HEIGHT / 12 + HEIGHT / 15;
				draw_texture(renderer, rect, "bmp_menu//exit.bmp");

				SDL_RenderPresent(renderer);
			}

		}

		if ((event.button.x >= WIDTH / 2 - WIDTH / 4) &&
			(event.button.x <= WIDTH - WIDTH / 4) &&
			(event.button.y >= HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 15 + HEIGHT / 12 + HEIGHT / 15) &&
			(event.button.y <= HEIGHT / 2 + HEIGHT / 24 + HEIGHT / 15 + HEIGHT / 12 + HEIGHT / 15 + HEIGHT / 12) &&
			(event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
			exit = false;
	}

	SDL_FreeSurface(screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}