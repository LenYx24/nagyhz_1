#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "math_helper.h"
#include "render.h"
#include "state.h"

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

typedef struct SpawnProps
{
  int rate;
  int lowerlimit;
  int counter;
  int incrementer;
  int speed;
} SpawnProps;

void moveplayer(Player *player);

EntityNode *moveentities(EntityNode *entities, bool rotatedimage);
void entitychangedir(EntityNode *entities, Point playerpos);
EntityNode *spawnentity(EntityNode *list, SDL_Texture *t, Point playerpos, double speed);
void freeentities(EntityNode *entities);

MissileNode *movemissiles(Player *player);
MissileNode *spawnmissile(Player *player);
void freemissiles(Player *player);

bool checkcollisioncircles(Player *player, EntityNode *entities);
void checkcollisionmissileenemy(Player *player, EntityNode **enemies);

void playerflash(Player *player);

void setspeedbydiff(SpawnProps *p, int basespeed);
bool updatespawnprops(SpawnProps *p);
#endif