#ifndef RENDER_H
#define RENDER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include "math_helper.h"

extern SDL_Color c_white;

SDL_Texture *loadimage(char *pathname);

void createwindow(Size windowsize, char *title);

void renderbox(Point topleft, Point downright, SDL_Color color);
void renderrectangle(SDL_Texture *t, Rect dest);
void renderrectanglerotated(SDL_Texture *t, Rect dest, double rotation);
void rendertext(Point pos, SDL_Color color, char *text);
void rendercircle(Point p, int radius, SDL_Color c);

void renderupdate();
#endif