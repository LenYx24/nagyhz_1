#include "../include/entity.h"

void moveplayer(Player *player)
{
    int distance = twopointsdistance(player->position, player->destination);
    Vector2 destposvect = normalizevector(vectorfromtwopoints(player->position, player->destination));
    double speed = player->speed;
    if (distance > speed)
    {
        player->position.x += speed * destposvect.x;
        player->position.y += speed * destposvect.y;
    }
    renderrectangle(player->texture, (Rect){gettopleftpoint(player->position, player->imgsize), player->imgsize});
}

EntityNode *moveentities(EntityNode *entities)
{
    EntityNode *preventity = NULL;
    EntityNode *current = entities;
    while (current != NULL)
    {
        Entity *f = &current->entity;
        rendercircle(f->position, f->hitboxradius, (SDL_Color){0, 0, 200, 255});
        if (outofscreen(f->position, f->imgsize))
        {
            if (preventity == NULL)
            {
                EntityNode *newfirst = current->next;
                free(current);
                entities = newfirst;
                current = entities;
            }
            else
            {
                preventity->next = current->next;
                free(current);
                current = preventity->next;
            }
        }
        else
        {
            int speed = f->speed;
            Vector2 v = {.x = f->direction.x * speed, .y = f->direction.y * speed};
            f->position = addvectortopoint(f->position, v);
            renderrectangle(f->texture, (Rect){gettopleftpoint(f->position, f->imgsize), f->imgsize});
            preventity = current;
            current = current->next;
        }
    }
    return entities;
}
void entitychangedir(EntityNode *entities, Point playerpos)
{
    for (EntityNode *current = entities; current != NULL; current = current->next)
    {
        Vector2 newdir = normalizevector(vectorfromtwopoints(current->entity.position, playerpos));
        current->entity.direction = newdir;
    }
}

EntityNode *spawnentity(EntityNode *list, SDL_Texture *ftexture, Point playerpos, double speed)
{
    EntityNode *newentity = (EntityNode *)malloc(sizeof(EntityNode));
    newentity->next = list;
    Point spawnpoint = randomspawnpoint();
    Vector2 dest = normalizevector(vectorfromtwopoints(spawnpoint, playerpos));

    Entity e = {
        .position = spawnpoint,
        .direction = dest,
        .hitboxradius = 42,
        .imgsize = {85, 85},
        .texture = ftexture,
        .speed = speed};
    newentity->entity = e;
    return newentity;
}
void freeentities(EntityNode *entities)
{
    EntityNode *temp = NULL;
    for (EntityNode *current = entities; current != NULL; current = temp)
    {
        temp = current->next;
        free(current);
    }
}

MissileNode *spawnmissile(Player *player)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    Point mousepos = {(double)x, (double)y};
    MissileNode *newmissile = (MissileNode *)malloc(sizeof(MissileNode));
    newmissile->next = player->missiles;
    Vector2 dir = normalizevector(vectorfromtwopoints(player->position, (Point){(double)mousepos.x, (double)mousepos.y}));
    newmissile->missile = (Missile){
        .position = player->position,
        .direction = dir,
        .distancetraveled = 0,
        .angle = getangle(dir)};
    return newmissile;
}
MissileNode *movemissiles(Player *player)
{
    MissileNode *prev = NULL;
    MissileNode *current = player->missiles;
    while (current != NULL)
    {
        Missile *m = &current->missile;
        if (m->distancetraveled >= player->missileprops.range)
        {
            if (prev == NULL)
            {
                MissileNode *newfirst = current->next;
                free(current);
                player->missiles = newfirst;
                current = newfirst;
            }
            else
            {
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        }
        else
        {
            int speed = player->missileprops.speed;
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
void freemissiles(Player *player)
{
    MissileNode *temp = NULL;
    for (MissileNode *current = player->missiles; current != NULL; current = temp)
    {
        temp = current->next;
        free(current);
    }
}

bool checkcollisioncircles(Player *player, EntityNode *entities)
{
    for (EntityNode *current = entities; current != NULL; current = current->next)
    {
        Entity *f = &current->entity;
        int distance = twopointsdistance(f->position, player->position);
        if (distance <= f->hitboxradius + player->hitboxradius)
            return true;
    }
    return false;
}
void checkcollisionmissileenemy(Player *player, EntityNode **enemies)
{
    EntityNode *prevenemy = NULL;
    EntityNode *enemyiter = *enemies;
    while (enemyiter != NULL)
    {
        bool removal = false;
        MissileNode *prevmissile = NULL;
        MissileNode *missileiter = player->missiles;
        while (missileiter != NULL)
        {
            Missile *missile = &missileiter->missile;
            Point circlecenter = enemyiter->entity.position;
            Point rectcenter = {
                missile->position.x,
                missile->position.y};
            rendercircle(rectcenter, 3.0f, (SDL_Color){0, 255, 0, 255});
            SDL_Log("%lf", player->missileprops.imgsize.width / 2.0f);
            double m_cos = cos(missile->angle);
            double m_sin = sin(missile->angle);

            Point rotatedcirclecenter = {
                .x = m_cos * (circlecenter.x - rectcenter.x) - m_sin * (circlecenter.y - rectcenter.y) + rectcenter.x,
                .y = m_sin * (circlecenter.x - rectcenter.x) + m_cos * (circlecenter.y - rectcenter.y) + rectcenter.y,
            };
            Point closestpoint;

            if (rotatedcirclecenter.x < missile->position.x)
                closestpoint.x = missile->position.x;
            else if (rotatedcirclecenter.x > missile->position.x + player->missileprops.imgsize.width)
                closestpoint.x = missile->position.x;
            else
                closestpoint.x = rotatedcirclecenter.x;

            if (rotatedcirclecenter.y < missile->position.y)
                closestpoint.y = missile->position.y;
            else if (rotatedcirclecenter.y > missile->position.y + player->missileprops.imgsize.height)
                closestpoint.y = missile->position.y;
            else
                closestpoint.y = rotatedcirclecenter.y;

            int distance = twopointsdistance(rotatedcirclecenter, closestpoint);
            if (distance < enemyiter->entity.hitboxradius)
            {
                // ütköznek, missile és enemy törlése
                if (prevmissile == NULL) // első elem törlése
                {
                    MissileNode *tmp = missileiter->next;
                    free(missileiter);
                    missileiter = tmp;
                    player->missiles = tmp;
                }
                else
                {
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
                }
                else
                {
                    prevenemy->next = enemyiter->next;
                    free(enemyiter);
                    enemyiter = prevenemy->next;
                }
                player->missileprops.oncd = false;
                removal = true;
                SDL_Log("collision");
            }
            if (removal == false)
            {
                prevmissile = missileiter;
                missileiter = missileiter->next;
                break;
            }
        }
        if (removal == false)
        {
            prevenemy = enemyiter;
            enemyiter = enemyiter->next;
        }
    }
}

void playerflash(Player *player)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    Point destpos = {(double)x, (double)y};
    int distance = twopointsdistance(player->position, destpos);
    if (distance >= player->flash.range)
    {
        double ratio = player->flash.range / (double)distance;
        double destx = player->position.x * (1 - ratio) + (ratio * destpos.x);
        double desty = player->position.y * (1 - ratio) + (ratio * destpos.y);
        destpos = (Point){destx, desty};
    }
    player->position = destpos;
}