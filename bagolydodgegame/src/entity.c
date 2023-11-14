#include "../include/entity.h"

void moveplayer(Player *player)
{
    Point destposv = substract(player->point, player->dest);
    int p1 = pow(player->point.x - player->dest.x, 2);
    int p2 = pow(player->point.y - player->dest.y, 2);
    double r = sqrt(p1 + p2);
    int speed = 2;
    if (r > speed)
    {
        player->point.x += speed * destposv.x / r;
        player->point.y += speed * destposv.y / r;
    }
    Rect playerimgdest = {(Point){player->point.x - (player->size.width / 2.0),
                                  player->point.y - (player->size.width / 2.0)},
                          (Size){player->size.width, player->size.width}};
    renderimage(player->texture, &playerimgdest);
}
void spawnfireball(FireballNode *list, SDL_Texture *texture, Point playerpos)
{
    FireballNode *newfireball = (FireballNode *)malloc(sizeof(FireballNode));
    newfireball->next = list;
    Point spawnpoint = randomspawnpoint();
    Vector2 dest = {.x = fabs(spawnpoint.x - playerpos.x), .y = fabs(spawnpoint.y - playerpos.y)};

    Fireball e = {
        .point = spawnpoint,
        .dest = dest,
        .radius = 10,
        .texture = texture};
    newfireball->fireball = e;
}