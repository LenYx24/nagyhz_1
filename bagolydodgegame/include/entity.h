#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "math_helper.h"
#include "render.h"

typedef struct Flash
{
  double cooldown;
  double cdcounter;
  double range;
  bool oncd;
} Flash;

typedef struct Missile
{
  Point position;
  Vector2 direction;
  double cooldown;
  double range;
} Missile;

typedef struct MissileNode
{
  Missile missile;
  struct MissileNode *next;
} MissileNode;

typedef struct Player
{
  Point position;
  Point destination;

  int hitboxradius;
  double speed;

  Size imgsize;
  SDL_Texture *texture;

  Flash flash;
  MissileNode missiles;
} Player;

typedef struct Fireball
{
  Point position;
  Vector2 direction;
  Size imgsize;
  int hitboxradius;
  SDL_Texture *texture;
  double speed;
} Fireball;

typedef struct Enemy
{
  Point position;
  Point destination;
  Size imgsize;
  int hitboxradius;
  SDL_Texture *texture;
  double speed;
} Enemy;

typedef struct FireballNode
{
  Fireball fireball;
  struct FireballNode *next;
} FireballNode;

void moveplayer(Player *player);

void movefireballs(FireballNode *fireballs);
FireballNode *spawnfireball(FireballNode *list, SDL_Texture *t, Point playerpos, double speed);
void freefireballs(FireballNode *fireballs);

bool checkcollisioncircles(Player *player, FireballNode *fireballs);

void playerflash(Player *player);
#endif