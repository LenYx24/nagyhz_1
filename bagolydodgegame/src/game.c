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
                   .texture = loadimage("resources/player.png"),
                   .flash = (Flash){
                       .props = (SpellProperties){
                           .cooldown = 3.0f,
                           .range = 300.0f,
                           .oncd = false},
                       .cdcounter = 3.0f,
                   },
                   .missileprops = (SpellProperties){
                       .cooldown = 1.0f,
                       .range = 500.0f,
                       .oncd = false,
                       .texture = loadimage("resources/missile.png"),
                       .imgsize = (Size){100, 20},
                   }};

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
    case SDL_KEYDOWN:
      switch (e->key.keysym.sym)
      {
      case SDLK_d:
      {
        if (!player.flash.props.oncd)
        {
          playerflash(&player);
        }
        player.flash.props.oncd = true;
        break;
      }
      case SDLK_q: // lövedék létrehozása
      {
        if (!player.missileprops.oncd)
        {
          spawnmissile(&player);
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
        fireballs = spawnfireball(fireballs, fireballtexture, player.position, fireballspeed);
      }

      // mozgatás

      moveplayer(&player);
      movefireballs(fireballs);

      // ütközések

      if (checkcollisioncircles(&player, fireballs))
        *state = MENU;

      // játékos képességek
      if (player.flash.props.oncd)
      {
        player.flash.cdcounter -= ms / 1000.0;
        if (player.flash.cdcounter <= 0.0f)
        {
          player.flash.cdcounter = player.flash.props.cooldown;
          player.flash.props.oncd = false;
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
  freefireballs(fireballs);
  SDL_RemoveTimer(timer);
  SDL_DestroyTexture(background);
  SDL_DestroyTexture(fireballtexture);
  SDL_DestroyTexture(enemytexture);
  SDL_DestroyTexture(player.texture);
}