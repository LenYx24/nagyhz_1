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
  int ms = 10;
  int timer = SDL_AddTimer(ms, update, NULL);

  Rect backgrounddest = {(Point){0, 0}, (Size){1280, 960}};
  Player player = {.position = {WINDOWWIDTH / 2, WINDOWHEIGHT / 2},
                   .imgsize = {100, 100},
                   .hitboxradius = 40,
                   .destination = {WINDOWWIDTH / 2, WINDOWHEIGHT / 2},
                   .speed = 2.7f,
                   .texture = loadimage("resources/player.png")};

  FireballNode *fireballs = NULL;

  int fireballspawncounter = 0;
  int fireballcap = 100;
  double fireballspeed = 5.0f;
  // double fireballspeedcap = 7.0f;

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
        player.destination = (Point){.x = e->button.x, .y = e->button.y};
      break;

    case SDL_USEREVENT:
      renderimagerect(background, &backgrounddest); // háttér újratöltése

      fireballspawncounter++;
      if (fireballspawncounter == fireballcap)
      {
        fireballspawncounter = 0;
        if (fireballcap > 30)
          fireballcap--;
        fireballs = spawnfireball(fireballs, fireballtexture, player.position, fireballspeed);
      }

      moveplayer(&player);
      movefireballs(fireballs);

      if (checkcollisioncircles(&player, fireballs))
        *state = MENU;
      // időmérés
      char t[30];
      sprintf(t, "masodpercek: %lf", seconds);
      rendertext((Point){WINDOWWIDTH - 200, 10}, (SDL_Color){255, 255, 255, 255}, t);
      seconds += ms / 100.0; // 10ms * 100ms = 1s

      renderupdate();
      break;
    case SDL_QUIT:
      *state = QUIT;
      break;
    }
  }
  freefireballs(fireballs);
  SDL_RemoveTimer(timer);
  SDL_DestroyTexture(background);
  SDL_DestroyTexture(fireballtexture);
  SDL_DestroyTexture(enemytexture);
  SDL_DestroyTexture(player.texture);
}