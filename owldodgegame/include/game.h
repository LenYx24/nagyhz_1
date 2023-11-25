#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <math.h>

#include "../lib/debugmalloc.h"

#include "render.h"
#include "entity.h"
#include "state.h"
#include "macros.h"
#include "overlay.h"
#include "scoreboard.h"

void game(SDL_Event *e);
#endif