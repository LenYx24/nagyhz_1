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
                   .destination = {WINDOWWIDTH / 2, WINDOWHEIGHT / 2},

                   .hitboxradius = 40,
                   .speed = 2.7f,

                   .imgsize = {100, 100},
                   .texture = loadimage("resources/player.png"),

                   .flash = (Spell){
                       .cooldown = 3.0f,
                       .range = 200.0f,
                       .oncd = false,
                       .cdcounter = 3.0f,
                   },
                   .missileprops = (Spell){
                       .cooldown = 1.0f,
                       .range = 500.0f,
                       .oncd = false,
                       .texture = loadimage("resources/missile.png"),
                       .imgsize = (Size){100, 20},
                       .speed = 7.0f,
                   },
                   .missiles = NULL};

  EntityNode *fireballs = NULL;
  EntityNode *enemies = NULL;

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
    case SDL_KEYDOWN:
      switch (e->key.keysym.sym)
      {
      case SDLK_d:
      {
        if (!player.flash.oncd)
        {
          playerflash(&player);
        }
        player.flash.oncd = true;
        break;
      }
      case SDLK_q: // lövedék létrehozása
      {
        if (!player.missileprops.oncd)
        {
          player.missiles = spawnmissile(&player);
        }
        player.missileprops.oncd = true;
        break;
      }
      case SDLK_s: // játékos mozgásának megállítása
      {
        player.destination = player.position;
        break;
      }
      }

      break;

    case SDL_USEREVENT:
      renderrectangle(background, backgrounddest); // háttér újratöltése

      // új elemek létrehozása

      fireballspawncounter++;
      if (fireballspawncounter == fireballcap)
      {
        fireballspawncounter = 0;
        if (fireballcap > 30)
          fireballcap--;
        fireballs = spawnentity(fireballs, fireballtexture, player.position, fireballspeed);
      }

      // mozgatás

      moveplayer(&player);
      fireballs = moveentities(fireballs);
      player.missiles = movemissiles(&player);

      // ütközések

      if (checkcollisioncircles(&player, fireballs))
        *state = MENU;

      // játékos képességek
      if (player.flash.oncd)
      {
        player.flash.cdcounter -= ms / 1000.0;
        if (player.flash.cdcounter <= 0.0f)
        {
          player.flash.cdcounter = player.flash.cooldown;
          player.flash.oncd = false;
        }
      }
      if (player.missileprops.oncd)
      {
        player.missileprops.cdcounter -= ms / 1000.0;
        if (player.missileprops.cdcounter <= 0.0f)
        {
          player.missileprops.cdcounter = player.flash.cooldown;
          player.missileprops.oncd = false;
        }
      }
      showcooldowns(&player);

      // időmérés

      showseconds(seconds);
      seconds += ms / 100.0; // 10ms * 100ms = 1s

      // megjelenítő frissítése

      renderupdate();
      break;
    case SDL_QUIT:
      *state = QUIT;
      break;
    }
  }
  freeentities(fireballs);
  freeentities(enemies);
  SDL_RemoveTimer(timer);
  SDL_DestroyTexture(background);
  SDL_DestroyTexture(fireballtexture);
  SDL_DestroyTexture(enemytexture);
  SDL_DestroyTexture(player.texture);
  SDL_DestroyTexture(player.missileprops.texture);
}