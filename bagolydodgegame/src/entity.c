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
    renderobject(player->texture, (Rect){gettopleftpoint(player->position, player->imgsize), player->imgsize});
}
void movefireballs(FireballNode *fireballs)
{
    for (FireballNode *current = fireballs; current != NULL; current = current->next)
    {
        Fireball *f = &current->fireball;
        int speed = f->speed;
        Vector2 v = {.x = f->direction.x * speed, .y = f->direction.y * speed};
        f->position = addvectortopoint(f->position, v);
        renderobject(f->texture, (Rect){gettopleftpoint(f->position, f->imgsize), f->imgsize});
    }
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
    Point destpos = (Point){x, y};
    int distance = twopointsdistance(player->position, destpos);
    if (distance >= player->flash.range)
    {
        int ratio = player->flash.range / distance;
        destpos = (Point){player->position.x + ratio * destpos.x, player->position.y + ratio * destpos.y};
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