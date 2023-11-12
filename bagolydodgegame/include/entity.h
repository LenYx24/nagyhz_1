#ifndef ENTITY_H
#define ENTITY_H
#include "math_helper.h"
#include "render.h"
#include <SDL2/SDL_image.h>
struct Entity
{
  Point point;
  Point dest;
  Size size;
  SDL_Texture *texture;
};
typedef struct Entity Fireball;
typedef struct Entity Player;

void move();

#endif