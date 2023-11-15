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

EntityNode *spawnentity(EntityNode *list, SDL_Texture *ftexture, Point playerpos, double speed)
{
    EntityNode *newentity = (EntityNode *)malloc(sizeof(EntityNode));
    newentity->next = list;
    Point spawnpoint = randomspawnpoint();
    Vector2 dest = normalizevector(vectorfromtwopoints(spawnpoint, playerpos));

    Entity e = {
        .position = spawnpoint,
        .direction = dest,
        .hitboxradius = 35,
        .imgsize = {70, 70},
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

MissileNode *movemissiles(Player *player)
{
    for (MissileNode *current = player->missiles; current != NULL; current = current->next)
    {
        Missile *m = &current->missile;
        int speed = player->missileprops.speed;
        Vector2 v = {m->direction.x * speed, m->direction.y * speed};
        m->position = addvectortopoint(m->position, v);
        renderrectanglerotated(
            player->missileprops.texture,
            (Rect){gettopleftpoint(m->position, player->missileprops.imgsize),
                   player->missileprops.imgsize},
            m->angle);
    }
    return player->missiles;
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
        .distancetraveled = player->missileprops.range,
        .angle = getangle(dir)};
    return newmissile;
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

// bool checkcollisionrect(Player *player, EntityNode *fireballs)
// {
//     for (EntityNode *current = fireballs; current != NULL; current = current->next)
//     {
//         double left = current->fireball.position.x;
//         double right = left + current->fireball.size.width;
//         double top = current->fireball.position.y;
//         double bottom = top + current->fireball.size.height;
//         if (left <= player->position.x && player->position.x <= right &&
//             bottom <= player->position.y && player->position.y <= top)
//             return true;
//     }
//     return false;
// }