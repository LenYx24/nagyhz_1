#include "../include/game.h"

Uint32 update(Uint32 ms, void *param)
{
  SDL_Event ev;
  ev.type = SDL_USEREVENT;
  SDL_PushEvent(&ev);
  return ms;
}
void game(SDL_Event *e, State *state)
{
  int timer = SDL_AddTimer(10, update, NULL);
  Rect dest = {(Point){0, 0}, (Size){1280, 960}};
  Player player = {.position = {WINDOWWIDTH / 2, WINDOWHEIGHT / 2},
                   .imgsize = {100, 100},
                   .hitboxradius = 40,
                   .destination = {WINDOWWIDTH / 2, WINDOWHEIGHT / 2},
                   .speed = 2.7f;
  .texture = loadimage("resources/player.png")
};
FireballNode *fireballs = NULL;
int fireballspawnms = 0;
int fireballcap = 100;
double seconds = 0.0f;
SDL_Texture *background = loadimage("resources/map.png");

SDL_Texture *fireballtexture = loadimage("resources/fireball.png");
SDL_Texture *enemytexture = loadimage("resources/enemy.png");
renderupdate();
while (*state == GAME)
{
  SDL_WaitEvent(e);
  switch (e->type)
  {
  case SDL_MOUSEBUTTONDOWN:
    if (e->button.button == SDL_BUTTON_RIGHT)
    {
      player.destination.x = e->button.x;
      player.destination.y = e->button.y;
    }
    renderupdate();
    break;

  case SDL_USEREVENT:
    renderimagerect(background, &dest); // háttér újratöltése

    fireballspawnms += 1;
    if (fireballspawnms == fireballcap)
    {
      fireballspawnms = 0;
      if (fireballcap > 30)
        fireballcap -= 2;
      fireballs = spawnfireball(fireballs, fireballtexture, player.position);
    }
    moveplayer(&player);
    movefireballs(fireballs);

    if (checkcollisioncircles(&player, fireballs))
    {
      SDL_Log("COLLISION");
      *state = MENU;
    }
    // időmérés
    char t[10];
    sprintf(t, "%lf", seconds);
    rendertext((Point){WINDOWWIDTH - 200, 10}, (SDL_Color){255, 255, 255, 255}, t);
    seconds += 0.01;

    renderupdate();
    break;
  case SDL_QUIT:
    *state = QUIT;
    break;
  }
}
freefireballs(fireballs);
SDL_RemoveTimer(timer);
destroytexture(background);
}