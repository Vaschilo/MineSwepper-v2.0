#include "libheader.h"

int r(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Surface*& screen)
{
	SDL_RenderClear(renderer);
	draw_texture(renderer, { 0,0,WIDTH,HEIGHT }, "bmp_menu//rule.bmp");
	SDL_RenderPresent(renderer);
	SDL_Event event;
	int i;
	FILE* f;
	fopen_s(&f, "easy.txt", "r");
	fscanf_s(f, "%d", &i);
	fclose(f);
	if (i == -1) { fopen_s(&f, "easy.txt", "w"); fprintf_s(f, "0 0"); fclose(f); }
	fopen_s(&f, "normal.txt", "r");
	fscanf_s(f, "%d", &i);
	fclose(f);
	if (i == -1) { fopen_s(&f, "normal.txt", "w"); fprintf_s(f, "0 0"); fclose(f); }
	fopen_s(&f, "hard.txt", "r");
	fscanf_s(f, "%d", &i);
	fclose(f);
	if (i == -1) { fopen_s(&f, "hard.txt", "w"); fprintf_s(f, "0 0"); fclose(f); }
	while (1)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) return 0;
		if ((event.button.x >= 250) &&
			(event.button.x <= 920) &&
			(event.button.y >= 580) &&
			(event.button.y <= 660) &&
			(event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
		{
			SDL_Delay(300);
			return 1;
		}
	}
	return 1;
}