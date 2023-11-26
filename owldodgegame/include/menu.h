#ifndef MENU_H
#define MENU_H
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../lib/debugmalloc.h"

#include "macros.h"
#include "math_helper.h"
#include "render.h"
#include "scoreboard.h"
#include "state.h"

typedef struct Button {
  Point pos;
  char text[10];
  void (*onclick)(struct Button *bt);
  bool selected;
  SDL_Color bgcolor;
} Button;

void menu();
#endif