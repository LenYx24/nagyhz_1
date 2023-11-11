#ifndef ENTITY_H
#define ENTITY_H
#include "math_helper.h"
#include "render.h"
struct Entity {
  Point point;
  Point dest;
  Size size;
  Texture texture;
};
typedef struct Entity Fireball;
typedef struct Entity Player;

void move();

#endif