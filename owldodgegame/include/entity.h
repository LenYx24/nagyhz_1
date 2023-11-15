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

typedef struct Entity
{
  Point position;
  Vector2 direction;
  Size imgsize;
  int hitboxradius;
  SDL_Texture *texture;
  double speed;
  bool followplayer;
} Entity;

typedef struct EntityNode
{
  Entity entity;
  struct EntityNode *next;
} EntityNode;

void moveplayer(Player *player);

EntityNode *moveentities(EntityNode *entities);
EntityNode *spawnentity(EntityNode *list, SDL_Texture *t, Point playerpos, double speed);
void freeentities(EntityNode *entities);

MissileNode *movemissiles(Player *player);
MissileNode *spawnmissile(Player *player);
void freemissiles(Player *player);

bool checkcollisioncircles(Player *player, EntityNode *entities);

void playerflash(Player *player);
#endif