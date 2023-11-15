#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "math_helper.h"
#include "render.h"

typedef struct Spell
{
  const double cooldown;
  const double range;
  double cdcounter;
  bool oncd;
  SDL_Texture *texture;
  Size imgsize;
  int speed;
} Spell;

typedef struct Missile
{
  Point position;
  Vector2 direction;
  double angle;
  double distancetraveled;
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

  Spell flash;
  Spell missileprops;
  MissileNode *missiles;
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

typedef struct EntityNode
{
  Entity entity;
  struct EntityNode *next;
} EntityNode;

void moveplayer(Player *player);

FireballNode *movefireballs(FireballNode *fireballs);
FireballNode *spawnfireball(FireballNode *list, SDL_Texture *t, Point playerpos, double speed);
void freefireballs(FireballNode *fireballs);

MissileNode *movemissiles(Player *player);
MissileNode *spawnmissile(Player *player);
void freemissiles(Player *player);

bool checkcollisioncircles(Player *player, FireballNode *fireballs);

void playerflash(Player *player);
#endif