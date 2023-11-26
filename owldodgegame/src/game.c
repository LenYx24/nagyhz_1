#include "../include/game.h"

Uint32 update(Uint32 ms, void *param) {
  SDL_Event e;
  e.type = SDL_USEREVENT;
  SDL_PushEvent(&e);
  return ms;
}

void handleinput(Player *player, SDL_Keycode keycode) {
  switch (keycode) {
  case SDLK_d: {
    if (!player->flash.oncd) // ha nincs töltési időn a képesség
    {
      player->flash.oncd = true;
      playerflash(player);
    }
    break;
  }
  case SDLK_q: // lövedék létrehozása
  {
    if (!player->missileprops.oncd) // ha nincs töltési időn a képesség
    {
      player->missileprops.oncd = true;
      player->missiles = spawnmissile(player);
    }
    break;
  }
  case SDLK_s: // játékos mozgásának megállítása
  {
    player->destination = player->position;
    break;
  }
  }
}

void game() {
  int ms = 10;
  int timer = SDL_AddTimer(ms, update, NULL);

  Rect backgrounddest = {(Point){0, 0}, (Size){WINDOWWIDTH, WINDOWHEIGHT}};

  Player player = {.position = {WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f},
                   .destination = {WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f},

                   .hitboxradius = 40,
                   .speed = 2.7f,

                   .imgsize = {100, 100},
                   .texture = loadimage("resources/player.png"),

                   .flash =
                       (Spell){
                           .cooldown = 3.0f,
                           .range = 200.0f,
                           .oncd = false,
                           .cdcounter = 3.0f,
                       },
                   .missileprops =
                       (Spell){
                           .cooldown = 1.0f,
                           .range = 500.0f,
                           .oncd = true,
                           .texture = loadimage("resources/missile.png"),
                           .imgsize = (Size){100, 20},
                           .speed = 7.5f,
                       },
                   .missiles = NULL};

  EntityNode *fireballs = NULL;
  EntityNode *enemies = NULL;

  SpawnProps fireballprops = {
      .rate = 150, .lowerlimit = 20, .counter = 0, .incrementer = 1};
  SpawnProps enemyprops = {
      .rate = 140, .lowerlimit = 30, .counter = 0, .incrementer = 1};

  // a tűzgolyók és ellenségek sebességét beállítjuk a nehézség alapján
  setspeedbydiff(&fireballprops, 3.0f);
  setspeedbydiff(&enemyprops, 2.5f);

  double seconds = 0.0f;

  SDL_Texture *background = loadimage("resources/map.png");
  SDL_Texture *fireballtexture = loadimage("resources/fireball.png");
  SDL_Texture *enemytexture = loadimage("resources/enemy.png");

  resetcurrentpoint(); // minden kör nulla ponttal indul

  SDL_Event e;
  while (getmainstate() == GAME) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_MOUSEBUTTONDOWN:
        if (e.button.button == SDL_BUTTON_RIGHT)
          player.destination = (Point){.x = e.button.x, .y = e.button.y};
        break;
      case SDL_KEYDOWN:
        handleinput(&player, e.key.keysym.sym);
        break;

      case SDL_USEREVENT:
        renderrectangle(background, backgrounddest); // háttér újratöltése

        // új entitások létrehozása
        if (updatespawnprops(&fireballprops))
          fireballs = spawnentity(fireballs, fireballtexture, player.position,
                                  fireballprops.speed);

        if (updatespawnprops(&enemyprops))
          enemies = spawnentity(enemies, enemytexture, player.position,
                                enemyprops.speed);

        // mozgatás

        moveplayer(&player);
        player.missiles = movemissiles(&player);

        bool rotatedimage = true;

        fireballs = moveentities(fireballs, rotatedimage);

        entitychangedir(enemies, player.position);
        enemies = moveentities(enemies, !rotatedimage);

        // ütközések

        // ha ütközött a játékos egy ellenséggel, akkor a körnek vége, tehát
        // átvált kör végi menü nézetre a játék
        if (checkcollisioncircles(&player, fireballs) ||
            checkcollisioncircles(&player, enemies)) {
          setmainstate(MENU);
          setsubmenustate(GAMEOVERMENU);
        }
        checkcollisionmissileenemy(&player, &enemies);

        // játékos képességek

        updatespell(&player.flash, ms);
        updatespell(&player.missileprops, ms);

        // játékfelületi elemek

        seconds += ms / 1000.0;

        // mivel a seconds változó minimum 0.01-el növekszik, ezért elég
        // 10^2-el eltolni, így biztosan egész számot kapunk majd 100-al osztva,
        // megkapjuk, hogy eltelt-e egy másodperc
        if ((int)(seconds * 100) % 100 == 0) {
          incrementcurrentscore(50);
        }

        showcooldowns(&player);
        showseconds(seconds);
        showpoints();

        break;
      case SDL_QUIT:
        setmainstate(QUIT);
        break;
      }
    }

    // megjelenítő frissítése
    renderupdate();
  }

  // felszabadítások

  freeentities(fireballs);
  freeentities(enemies);
  freemissiles(&player);

  SDL_RemoveTimer(timer);

  SDL_DestroyTexture(background);
  SDL_DestroyTexture(fireballtexture);
  SDL_DestroyTexture(enemytexture);
  SDL_DestroyTexture(player.texture);
  SDL_DestroyTexture(player.missileprops.texture);
}