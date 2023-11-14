#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL_image.h>

#include "math_helper.h"
#include "render.h"

typedef struct Player
{
  Point position;
  Point destination;
  Size imgsize;
  int hitboxradius;
  SDL_Texture *texture;
  int speed;
} Player;

typedef struct Fireball
{
  Point position;
  Vector2 direction;
  Size imgsize;
  int hitboxradius;
  SDL_Texture *texture;
  int speed;
} Fireball;

typedef struct Enemy
{
  Point position;
  Point destination;
  Size imgsize;
  int hitboxradius;
  SDL_Texture *texture;
  int speed;
} Enemy;

typedef struct FireballNode
{
  Fireball fireball;
  struct FireballNode *next;
} FireballNode;

void moveplayer(Player *player);

void movefireballs(FireballNode *fireballs);
FireballNode *spawnfireball(FireballNode *list, SDL_Texture *t, Point playerpos);
void freefireballs(FireballNode *fireballs);

bool checkcollisioncircles(Player *player, FireballNode *fireballs);

#endif