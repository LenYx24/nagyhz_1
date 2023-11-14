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
  Player player = {.point = {960, 540},
                   .size = {100, 100},
                   .texture = loadimage("resources/infocbagoly.png")};
  FireballNode *fireballs = NULL;
  int fireballspawnms = 0;

  SDL_Texture *bg = loadimage("resources/map.png");

  SDL_Texture *fireballtexture = loadimage("resources/map.png");
  renderupdate();
  while (*state == GAME)
  {
    SDL_WaitEvent(e);
    switch (e->type)
    {
    case SDL_MOUSEBUTTONDOWN:
      if (e->button.button == SDL_BUTTON_RIGHT)
      {
        player.dest.x = e->button.x;
        player.dest.y = e->button.y;
      }
      renderupdate();
      break;

    case SDL_USEREVENT:

      renderimage(bg, &dest);

      fireballspawnms += 1;
      if (fireballspawnms == 100)
      {
        fireballspawnms = 0;
        spawnfireball(fireballs, fireballtexture, player.point);
      }
      moveplayer(&player);
      renderupdate();
      break;
    case SDL_QUIT:
      *state = QUIT;
      break;
    }
  }

  SDL_RemoveTimer(timer);
  destroytexture(bg);
}