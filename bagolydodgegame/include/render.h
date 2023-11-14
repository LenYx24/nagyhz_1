#ifndef RENDER_H
#define RENDER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include "math_helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

SDL_Texture *loadimage(char *pathname);
void renderimage(SDL_Texture *t, Rect *dest);
void destroytexture(SDL_Texture *t);

void createuserevent();

void createwindow(Size windowsize, char *title);
void rendererquit();

void renderbox(Point topleft, Point downright, SDL_Color color);
void rendertext(Point pos, SDL_Color color, char *text);

void renderupdate();
#endif