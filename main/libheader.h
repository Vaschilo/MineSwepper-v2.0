/*¬ этом хедере 
объ€вл€ютс€ все библиотеки, 
хран€тс€ все константы, 
обща€ структура q, 
заголавки общих функций(они описаны в Functions.cpp)*/

#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <time.h>
#include "stdlib.h"
#include <iostream>

#define HEIGHT 700
#define WIDTH 1170

#define Pole 9 //easy level
#define H_pole 16 //norm and hard level
#define W_pole 30 //hard level

#define NOBE 10	//easy level
#define NOBN 40 //normal level
#define NOBH 99 //easy level

#define shans rand() % (heit * weit - 1)

struct q
{
	int sp;						//сери€ побед
	int real[H_pole * W_pole];
	int game[H_pole * W_pole];
};

void draw_texture(SDL_Renderer*& renderer, SDL_Rect rect, const char* fname);
int checktouch(int X, int Y, int x0, int x, int hx, int y0, int y, int hy);
int getmax(q& g, int weit, int heit);
void open(q& g, int q, int heit, int weit);
void init(q& g, int heit, int weit, int bombs);
void draw_text(SDL_Renderer*& renderer, char* text, int x, int y, int h, int w);
int schet(q& g, int weit, int heit, int number, int x);

int getsp(const char* fname, bool status);
void loadmusic(const char* fname);
//void sound(const char* name);