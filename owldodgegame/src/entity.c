#include "../include/entity.h"

void moveplayer(Player *player) {
  GameObject *character = &player->character;

  int distance = twopointsdistance(character->position, player->destination);
  player->character.direction = normalizevector(
      vectorfromtwopoints(character->position, player->destination));

  if (distance > character->speed) {
    character->position.x += character->speed * character->direction.x;
    character->position.y += character->speed * character->direction.y;
  }
  renderrectangle(
      character->texture,
      (Rect){gettopleftpoint(character->position, character->imgsize),
             character->imgsize});
}
void playerflash(Player *player) {
  int x, y;
  SDL_GetMouseState(&x, &y);
  Point destpos = {(double)x, (double)y};
  int distance = twopointsdistance(player->character.position, destpos);

  // ha a hatótávon kívűlre szeretne teleportálni,akkor ugyanabba az irányba, de
  // közelebbi helyre fogja elteleportálni
  if (distance >= player->flash.range) {
    double ratio = player->flash.range / (double)distance;
    double destx =
        player->character.position.x * (1 - ratio) + (ratio * destpos.x);
    double desty =
        player->character.position.y * (1 - ratio) + (ratio * destpos.y);
    destpos = (Point){destx, desty};
  }
  player->character.position = destpos;
}
EntityNode *moveentities(EntityNode *entities, bool rotatedimage) {
  EntityNode *preventity = NULL;
  EntityNode *current = entities;

  while (current != NULL) {
    GameObject *f = &current->entity;
    rendercircle(f->position, f->hitboxradius, (SDL_Color){0, 0, 200, 255});
    if (outofscreen(f->position, f->imgsize)) {
      if (preventity == NULL) {
        EntityNode *newfirst = current->next;
        free(current);
        entities = newfirst;
        current = entities;
      } else {
        preventity->next = current->next;
        free(current);
        current = preventity->next;
      }
    } else {
      Vector2 v = {.x = f->direction.x * f->speed,
                   .y = f->direction.y * f->speed};
      f->position = addvectortopoint(f->position, v);
      double angle = getangle(v);
      if (!rotatedimage)
        angle = 0;
      renderrectanglerotated(
          f->texture,
          (Rect){gettopleftpoint(f->position, f->imgsize), f->imgsize}, angle);
      preventity = current;
      current = current->next;
    }
  }
  return entities;
}
void entitychangedir(EntityNode *entities, Point playerpos) {
  for (EntityNode *current = entities; current != NULL;
       current = current->next) {
    Vector2 newdir = normalizevector(
        vectorfromtwopoints(current->entity.position, playerpos));
    current->entity.direction = newdir;
  }
}

EntityNode *spawnentity(EntityNode *list, Point playerpos, GameObject props) {
  EntityNode *newentity = (EntityNode *)malloc(sizeof(EntityNode));
  newentity->next = list;
  Point spawnpoint = randomspawnpoint();
  Vector2 dest = normalizevector(vectorfromtwopoints(spawnpoint, playerpos));

  GameObject e = props;
  e.position = spawnpoint;
  e.direction = dest;
  newentity->entity = e;
  return newentity;
}
void updatespellcooldown(Spell *spell, int ms) {
  if (spell->cooldown.oncd) {
    spell->cooldown.cdcounter -= ms / 1000.0;
    if (spell->cooldown.cdcounter <= 0.0f) {
      spell->cooldown.cdcounter = spell->cooldown.cd;
      spell->cooldown.oncd = false;
    }
  }
}
void freeentities(EntityNode *entities) {
  EntityNode *temp = NULL;
  for (EntityNode *current = entities; current != NULL; current = temp) {
    temp = current->next;
    free(current);
  }
}

MissileNode *spawnmissile(Player *player) {
  int x, y;
  SDL_GetMouseState(&x, &y);
  Point mousepos = {(double)x, (double)y};
  MissileNode *newmissile = (MissileNode *)malloc(sizeof(MissileNode));
  newmissile->next = player->missiles;
  Vector2 dir = normalizevector(vectorfromtwopoints(
      player->character.position, (Point){mousepos.x, mousepos.y}));
  newmissile->missile = (Missile){.position = player->character.position,
                                  .direction = dir,
                                  .distancetraveled = 0,
                                  .angle = getangle(dir)};
  return newmissile;
}
MissileNode *movemissiles(Player *player) {
  MissileNode *prev = NULL;
  MissileNode *current = player->missiles;
  while (current != NULL) {
    Missile *m = &current->missile;
    if (m->distancetraveled >= player->missileprops.range) {
      if (prev == NULL) {
        MissileNode *newfirst = current->next;
        free(current);
        player->missiles = newfirst;
        current = newfirst;
      } else {
        prev->next = current->next;
        free(current);
        current = prev->next;
      }
    } else {
      double speed = player->missileprops.speed;
      Vector2 v = {m->direction.x * speed, m->direction.y * speed};
      m->position = addvectortopoint(m->position, v);
      m->distancetraveled += vectorlength(v);
      renderrectanglerotated(
          player->missileprops.texture,
          (Rect){gettopleftpoint(m->position, player->missileprops.imgsize),
                 player->missileprops.imgsize},
          m->angle);
      prev = current;
      current = current->next;
    }
  }
  return player->missiles;
}
void freemissiles(Player *player) {
  MissileNode *temp = NULL;
  for (MissileNode *current = player->missiles; current != NULL;
       current = temp) {
    temp = current->next;
    free(current);
  }
}

bool checkcollisioncircles(Player *player, EntityNode *entities) {
  for (EntityNode *current = entities; current != NULL;
       current = current->next) {
    GameObject *f = &current->entity;
    int distance = twopointsdistance(f->position, player->character.position);
    if (distance <= f->hitboxradius + player->character.hitboxradius)
      return true;
  }
  return false;
}
void checkcollisionmissileenemy(Player *player, EntityNode **enemies) {
  EntityNode *prevenemy = NULL;
  EntityNode *enemyiter = *enemies;
  while (enemyiter != NULL) {
    bool removal = false;
    MissileNode *prevmissile = NULL;
    MissileNode *missileiter = player->missiles;
    while (missileiter != NULL) {
      Missile *missile = &missileiter->missile;
      Point circlecenter = enemyiter->entity.position;
      Point rectcenter = {missile->position.x, missile->position.y};
      rendercircle(rectcenter, 3.0f, (SDL_Color){0, 255, 0, 255});
      double m_cos = cos(missile->angle);
      double m_sin = sin(missile->angle);

      Point rotatedcirclecenter = {
          .x = m_cos * (circlecenter.x - rectcenter.x) -
               m_sin * (circlecenter.y - rectcenter.y) + rectcenter.x,
          .y = m_sin * (circlecenter.x - rectcenter.x) +
               m_cos * (circlecenter.y - rectcenter.y) + rectcenter.y,
      };
      Point closestpoint;

      if (rotatedcirclecenter.x < missile->position.x)
        closestpoint.x = missile->position.x;
      else if (rotatedcirclecenter.x >
               missile->position.x + player->missileprops.imgsize.width)
        closestpoint.x = missile->position.x;
      else
        closestpoint.x = rotatedcirclecenter.x;

      if (rotatedcirclecenter.y < missile->position.y)
        closestpoint.y = missile->position.y;
      else if (rotatedcirclecenter.y >
               missile->position.y + player->missileprops.imgsize.height)
        closestpoint.y = missile->position.y;
      else
        closestpoint.y = rotatedcirclecenter.y;

      int distance = twopointsdistance(rotatedcirclecenter, closestpoint);
      if (distance < enemyiter->entity.hitboxradius) {
        // ütköznek, missile és enemy törlése
        if (prevmissile == NULL) // első elem törlése
        {
          MissileNode *tmp = missileiter->next;
          free(missileiter);
          missileiter = tmp;
          player->missiles = tmp;
        } else {
          prevmissile->next = missileiter->next;
          free(missileiter);
          missileiter = prevmissile->next;
        }

        if (prevenemy == NULL) // első elem törlése
        {
          EntityNode *tmp = enemyiter->next;
          free(enemyiter);
          enemyiter = tmp;
          *enemies = tmp;
        } else {
          prevenemy->next = enemyiter->next;
          free(enemyiter);
          enemyiter = prevenemy->next;
        }
        player->missileprops.cooldown.oncd = false;
        removal = true;
        incrementcurrentscore(10);
      }
      if (removal == false) {
        prevmissile = missileiter;
        missileiter = missileiter->next;
        break;
      }
    }
    if (removal == false) {
      prevenemy = enemyiter;
      enemyiter = enemyiter->next;
    }
  }
}

void setspeedbydiff(SpawnProps *p, double basespeed) {
  switch (getdifficulty()) {
  case EASY:
    p->initspeed = basespeed;
    break;
  case MEDIUM:
    p->initspeed = basespeed * 1.2f;
    break;
  case HARD:
    p->initspeed = basespeed * 1.84f;
    break;
  }
}

bool updatespawnprops(SpawnProps *p) {
  p->counter += p->incrementer;
  if (p->counter >= p->rate) {
    p->counter = 0;
    if (p->rate > p->lowerlimit)
      p->rate--;
    return true;
  }
  return false;
}