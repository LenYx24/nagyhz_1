#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include "render.h"
#include "entity.h"
#include "state.h"
#include "macros.h"
#include "overlay.h"
void game(SDL_Event *e, State *state);
#endif