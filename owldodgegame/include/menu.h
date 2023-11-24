#ifndef MENU_H
#define MENU_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "render.h"
#include "state.h"
#include "math_helper.h"
#include "macros.h"
typedef struct Button
{
    Point pos;
    char text[10];
    void (*onclick)(struct Button *bt);
    bool selected;
    SDL_Color bgcolor;
} Button;

void menu(SDL_Event *e);
#endif