#ifndef ENTITY_H
#define ENTITY_H
#include "math_helper.h"
struct Entity {
  Point point;
  Point dest;
  Size size;
};
typedef struct Entity Fireball;
typedef struct Entity Player;

#endif