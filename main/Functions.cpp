//В этом cpp хранятся общие функции для всех уровней.

#include "libheader.h"

void loadmusic(const char* fname)
{
	Mix_Music* fon = Mix_LoadMUS(fname);
	if (fon == NULL) { std::cout << "background music doesn't loaded\n"; };
	Mix_PlayMusic(fon, -1);
}
//void sound(const char* name)
//{
//	Mix_Chunk* Sound = Mix_LoadWAV(name);
//	Mix_PlayChannel(-1, Sound, 0);
//}
void draw_texture(SDL_Renderer*& renderer, SDL_Rect rect, const char* fname)
{
	SDL_Surface* myImage = SDL_LoadBMP(fname);
	SDL_SetColorKey(myImage, SDL_TRUE, SDL_MapRGB(myImage->format, 0, 0, 0));

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, myImage);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(myImage);
}
int checktouch(int X, int Y, int x0, int x, int hx, int y0, int y, int hy)
{
	int co = 0;
	for (int j = y0; j < y; j += hy)
		for (int i = x0; i < x; i += hx)
			if ((X > i) && (X < i + hx) && (Y > j) && (Y < j + hy))
				return co;
			else co++;
	return -1;
}
int getmax(q& g, int weit, int heit)
{
	int max = 0;
	int q;
	for (q = weit; q < weit * heit; q++)
	{
		max = 0;
		if (g.real[q] == 0)
		{
			if ((q - weit >= 0) && (!g.game[q - weit]))						max++; 	// Верх
			if ((q + weit < heit * weit) && (!g.game[q + weit]))			max++;	// Низ
			if (((q + 1) % weit) && (!g.game[q + 1]))						max++;	// Право
			if ((q % weit) && (!g.game[q - 1]))								max++;	// Лево
			if ((q - weit >= 0) && (q % weit) && (!g.game[q - weit - 1]))	max++;	// В-Л
			if ((q - weit >= 0) && ((q + 1) % weit) && (!g.game[q - weit + 1]))max++;// В-П
			if ((q + weit < heit * weit) && (q % weit) && (!g.game[q + weit - 1]))max++;// Н-Л
			if ((q + weit < heit * weit) && ((q + 1) % weit) && (!g.game[q + weit + 1]))max++;	// Н-П
		}
		if (max == 8) break;
	}
	return q;
}
void open(q& g, int q, int heit, int weit)
{
	g.game[q] = 1;
	if (g.real[q] == 0)
	{
		if ((q - weit >= 0) && (!g.game[q - weit]))						open(g, q - weit, heit, weit); 	// Верх
		if ((q + weit < weit * heit) && (!g.game[q + weit]))			open(g, q + weit, heit, weit);	// Низ
		if (((q + 1) % weit) && (!g.game[q + 1]))						open(g, q + 1, heit, weit);		// Право
		if ((q % weit) && (!g.game[q - 1]))								open(g, q - 1, heit, weit);		// Лево
		if ((q - weit >= 0) && (q % weit) && (!g.game[q - 1 - weit]))	open(g, q - weit - 1, heit, weit);// В-Л
		if ((q - weit >= 0) && ((q + 1) % weit) && (!g.game[q - weit + 1]))open(g, q - weit + 1, heit, weit);// В-П
		if ((q + weit < weit * heit) && (q % weit) && (!g.game[q + weit - 1]))open(g, q + weit - 1, heit, weit);// Н-Л
		if ((q + weit < weit * heit) && ((q + 1) % weit) && (!g.game[q + weit + 1]))open(g, q + weit + 1, heit, weit);// Н-П
	}
}
void init(q& g, int heit, int weit, int bombs)
{
	int a = 0;
	for (int i = 0; i < heit * weit; i++)
	{
		g.real[i] = 0;
		g.game[i] = 0;
	}
	/* =============== Ставим бомбы ============== */
	while (a < bombs)
		for (int i = 0; i < weit * heit; i++)
			if ((g.real[i] != 9) && (shans < bombs)) { g.real[i] = 9; if (++a == bombs) break; }
	/* ===== Инициализируем остальные клетки ===== */
	for (int i = 0; i < weit * heit; i++)
	{
		if (g.real[i] == 9) continue;
		if ((i - weit >= 0) && (g.real[i - weit] == 9))								g.real[i]++;		// Верх
		if ((i + weit < weit * heit) && (g.real[i + weit] == 9))					g.real[i]++;		// Низ
		if (((i + 1) % weit) && (g.real[i + 1] == 9))								g.real[i]++;		// Право
		if ((i % weit) && (g.real[i - 1] == 9))										g.real[i]++;		// Лево
		if ((i - weit >= 0) && (i % weit) && (g.real[i - weit - 1] == 9))			g.real[i]++;		// В-Л
		if ((i - weit >= 0) && ((i + 1) % weit) && (g.real[i - weit + 1] == 9))		g.real[i]++;		// В-П
		if ((i + weit < weit * heit) && (i % weit) && (g.real[i + weit - 1] == 9))	g.real[i]++;		// Н-Л
		if ((i + weit < weit * heit) && ((i + 1) % weit) && (g.real[i + weit + 1] == 9))g.real[i]++;	// Н-П
	}
	open(g, getmax(g, heit, weit), heit, weit);
}
void draw_text(SDL_Renderer*& renderer, char* text, int x, int y, int h, int w)
{
	TTF_Init();
	TTF_Font* my_font = TTF_OpenFont("comic.ttf", 500);//old C:\\Windows\\Fonts\\segoeui.ttf
	SDL_Color fore_color = { 255,255,255 };
	SDL_Color back_color = { 0,0,1 };

	SDL_Rect rect = { x,y,w,h };
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Shaded(my_font, text, fore_color, back_color));
	SDL_RenderCopy(renderer, texture, NULL, &rect);

	TTF_Quit();
}
int getsp(const char* fname, bool status)
{
	int i;
	FILE* f;
	fopen_s(&f, fname, "r");
	fscanf_s(f, "%d", &i);
	if (status) fscanf_s(f, "%d", &i);
	fclose(f);
	return i;
}
int schet(q& g, int weit, int heit, int number, int x)
{
	int counter = 0;
	if ((number - weit >= 0) && (g.game[number - weit] == x))counter++;
	if ((number + weit < weit * heit) && (g.game[number + weit] == x))counter++;
	if (((number + 1) % weit) && (g.game[number + 1] == x))counter++;
	if ((number % weit) && (g.game[number - 1] == x))counter++;
	if ((number - weit >= 0) && (number % weit) && (g.game[number - (weit + 1)] == x))counter++;
	if ((number - weit >= 0) && ((number + 1) % weit) && (g.game[number - weit + 1] == x))counter++;
	if ((number + weit < weit * heit) && (number % weit) && (g.game[number + weit - 1] == x))counter++;
	if ((number + weit < weit * heit) && ((number + 1) % weit) && (g.game[number + (weit + 1)] == x))counter++;
	return counter;
}