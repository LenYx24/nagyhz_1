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

FireballNode *movefireballs(FireballNode *fireballs)
{
    FireballNode *prevfireball = NULL;
    FireballNode *current = fireballs;
    while (current != NULL)
    {
        Fireball *f = &current->fireball;
        if (outofscreen(f->position, f->imgsize))
        {
            if (prevfireball == NULL)
            {
                FireballNode *newfirst = current->next;
                free(current);
                fireballs = newfirst;
                current = fireballs;
            }
            else
            {
                prevfireball->next = current->next;
                free(current);
                current = prevfireball->next;
            }
        }
        else
        {
            int speed = f->speed;
            Vector2 v = {.x = f->direction.x * speed, .y = f->direction.y * speed};
            f->position = addvectortopoint(f->position, v);
            renderrectangle(f->texture, (Rect){gettopleftpoint(f->position, f->imgsize), f->imgsize});
            prevfireball = current;
            current = current->next;
        }
    }
    return fireballs;
}

FireballNode *spawnfireball(FireballNode *list, SDL_Texture *ftexture, Point playerpos, double speed)
{
    FireballNode *newfireball = (FireballNode *)malloc(sizeof(FireballNode));
    newfireball->next = list;
    Point spawnpoint = randomspawnpoint();
    Vector2 dest = normalizevector(vectorfromtwopoints(spawnpoint, playerpos));

    Fireball e = {
        .position = spawnpoint,
        .direction = dest,
        .hitboxradius = 35,
        .imgsize = {70, 70},
        .texture = ftexture,
        .speed = speed};
    newfireball->fireball = e;
    return newfireball;
}
void freefireballs(FireballNode *fireballs)
{
    FireballNode *temp = NULL;
    for (FireballNode *current = fireballs; current != NULL; current = temp)
    {
        temp = current->next;
        free(current);
    }
}

void movemissiles(Player *player)
{
    for (MissileNode *current = player->missiles; current != NULL; current = current->next)
    {
        Missile *m = &current->missile;
        int speed = player->missileprops.speed;
        Vector2 v = {.x = m->direction.x * speed, .y = m->direction.y * speed};
        m->position = addvectortopoint(m->position, v);
        renderrectanglerotated(
            player->missileprops.texture,
            (Rect){gettopleftpoint(m->position, player->missileprops.imgsize),
                   player->missileprops.imgsize},
            m->angle);
    }
}
MissileNode *spawnmissile(Player *player)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    Point mousepos = {(double)x, (double)y};
    MissileNode *newmissile = (MissileNode *)malloc(sizeof(MissileNode));
    newmissile->next = player->missiles;
    Vector2 dest = normalizevector(vectorfromtwopoints(player->position, mousepos));

    Missile m = {
        .position = player->position,
        .direction = dest,
        .distancetraveled = player->missileprops.range,
        .cdcounter = player->missileprops.cooldown,
        .angle = tanindegrees(dest.x, dest.y)};
    newmissile->missile = m;
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

bool checkcollisioncircles(Player *player, FireballNode *fireballs)
{
    for (FireballNode *current = fireballs; current != NULL; current = current->next)
    {
        Fireball *f = &current->fireball;
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
    if (distance >= player->flash.props.range)
    {
        double ratio = player->flash.props.range / (double)distance;
        double destx = player->position.x * (1 - ratio) + (ratio * destpos.x);
        double desty = player->position.y * (1 - ratio) + (ratio * destpos.y);
        destpos = (Point){destx, desty};
    }
    player->position = destpos;
}

// bool checkcollisionrect(Player *player, FireballNode *fireballs)
// {
//     for (FireballNode *current = fireballs; current != NULL; current = current->next)
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