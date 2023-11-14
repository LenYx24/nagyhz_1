#ifndef ENTITY_H
#define ENTITY_H
#include "math_helper.h"
#include "render.h"
#include <SDL2/SDL_image.h>
typedef struct Player
{
  Point point;
  Point dest;
  Size size;
  SDL_Texture *texture;
} Player;

typedef struct Fireball
{
  Point point;
  Vector2 dest;
  int radius;
  SDL_Texture *texture;
} Fireball;

typedef struct Enemy
{
  Point point;
  Point dest;
  Size size;
  SDL_Texture *texture;
} Enemy;

typedef struct FireballNode
{
  Fireball fireball;
  struct FireballNode *next;
} FireballNode;

void moveplayer(Player *player);
void spawnfireball(FireballNode *list, SDL_Texture *t, Point playerpos);

#endif