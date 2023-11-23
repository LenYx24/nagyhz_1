#ifndef MENU_H
#define MENU_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "state.h"
#include "math_helper.h"
#include "macros.h"

typedef void (*callback)();
typedef struct Button
{
    Point pos;
    char text[10];
    callback onclick;
    SDL_Color bgcolor;
} Button;

void menu(SDL_Event *e);
#endif