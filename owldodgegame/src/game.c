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
    if (!player->flash.cooldown.oncd) // ha nincs töltési időn a képesség
    {
      player->flash.cooldown.oncd = true;
      playerflash(player);
    }
    break;
  }
  case SDLK_q: // lövedék létrehozása
  {
    if (!player->missileprops.cooldown.oncd) // ha nincs töltési időn a képesség
    {
      player->missileprops.cooldown.oncd = true;
      player->missiles = spawnmissile(player);
    }
    break;
  }
  case SDLK_s: // játékos mozgásának megállítása
  {
    player->character.direction = (Vector2){0, 0};
    player->destination = player->character.position;
    break;
  }
  }
}

void game() {
  int ms = 10;
  int timer = SDL_AddTimer(ms, update, NULL);

  Rect backgrounddest = {(Point){0, 0}, (Size){WINDOWWIDTH, WINDOWHEIGHT}};
  Size owlsize = {80, 80};

  Player player = {
      .character =
          {
              .position = {WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f},
              .direction = {0, 0},
              .hitboxradius = 40,
              .speed = 2.7f,

              .imgsize = owlsize,
              .texture = loadimage("resources/player.png"),
          },
      .destination = {WINDOWWIDTH / 2.0f, WINDOWHEIGHT / 2.0f},
      .flash =
          (Spell){
              .cooldown =
                  {
                      .cd = 3.0f,
                      .oncd = false,
                      .cdcounter = 3.0f,
                  },
              .range = 200.0f,
          },
      .missileprops =
          (Spell){
              .cooldown =
                  {
                      .cd = 1.0f,
                      .oncd = true,
                  },
              .range = 500.0f,
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

  SDL_Texture *background = loadimage("resources/map.jpg");
  SDL_Texture *fireballtexture = loadimage("resources/fireball.png");
  SDL_Texture *enemytexture = loadimage("resources/enemy.png");

  showposclickfeedback mouseclickfeedback = {
      .counter = 0, .limit = 10, .show = false, .pos = {0, 0}};

  resetcurrentpoint(); // minden kör nulla ponttal indul

  SDL_Event e;
  while (getmainstate() == GAME) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_MOUSEBUTTONDOWN:
        if (e.button.button == SDL_BUTTON_RIGHT) {
          Point mousepos = (Point){.x = e.button.x, .y = e.button.y};
          player.destination = mousepos;
          mouseclickfeedback.pos = mousepos;
          mouseclickfeedback.counter = 0;
          mouseclickfeedback.show = true;
        }
        break;
      case SDL_KEYDOWN:
        handleinput(&player, e.key.keysym.sym);
        break;

      case SDL_USEREVENT:
        renderrectangle(background, backgrounddest); // háttér újratöltése

        // egérgomb kattintás helyének mutatása

        if (mouseclickfeedback.show &&
            mouseclickfeedback.counter <= mouseclickfeedback.limit) {
          mouseclickfeedback.counter++;
          if (mouseclickfeedback.counter >= mouseclickfeedback.limit)
            mouseclickfeedback.show = false;
          rendercircle(mouseclickfeedback.pos, 7, c_green);
        }

        // új entitások létrehozása
        if (updatespawnprops(&fireballprops)) {
          GameObject fireballobjectprops = {.hitboxradius = 36,
                                            .imgsize = {75, 75},
                                            .texture = fireballtexture,
                                            .speed = fireballprops.initspeed};
          fireballs = spawnentity(fireballs, player.character.position,
                                  fireballobjectprops);
        }

        if (updatespawnprops(&enemyprops)) {
          GameObject enemyobjectprops = {.hitboxradius = 42,
                                         .imgsize = owlsize,
                                         .texture = enemytexture,
                                         .speed = enemyprops.initspeed};
          enemies =
              spawnentity(enemies, player.character.position, enemyobjectprops);
        }

        // mozgatás

        moveplayer(&player);
        player.missiles = movemissiles(&player);

        bool rotatedimage = true;

        fireballs = moveentities(fireballs, rotatedimage);

        entitychangedir(enemies, player.character.position);
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

        updatespellcooldown(&player.flash, ms);
        updatespellcooldown(&player.missileprops, ms);

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
  SDL_DestroyTexture(player.character.texture);
  SDL_DestroyTexture(player.missileprops.texture);
}
