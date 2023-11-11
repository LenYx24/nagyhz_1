#ifndef RENDER_H
#define RENDER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include "math_helper.h"
#include "color.h"

typedef struct Texture {
    SDL_Texture *t;
} Texture;

typedef struct Event {
    SDL_Event *event;
} Event;

typedef struct Timer {
    SDL_TimerID id;
} Timer;

void createwindow(Size windowsize, char* title);
void rendererquit();

Texture loadimage(char *pathname);
void renderimage(Texture *t, Rect *dest);
void destroytexture(Texture *t);

void renderbox(Point topleft, Point downright, Color color);
void rendertext(Point pos,Color color, char*text);

void waitevent(Event *e);

void renderupdate();

Timer createtimer(Uint32 ms, void *callback);
void removetimer(Timer *t);

void createuserevent();
#endif