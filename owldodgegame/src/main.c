#include <time.h>
#include <SDL2/SDL.h>

#include "../include/entity.h"
#include "../include/math_helper.h"
#include "../include/state.h"
#include "../include/menu.h"
#include "../include/game.h"

#include "../lib/debugmalloc.h"


int main(int argc, char *argv[])
{
  srand((unsigned)time(0));

  // az ablak inicializálása
  Size windowsize = {WINDOWWIDTH, WINDOWHEIGHT};
  char *title = "bagolyjatek";
  createwindow(windowsize, title);
  initfont("./fonts/LiberationSerif-Regular.ttf", 32);

  char filename[] = "scoreboard.txt";
  loadscoresfromfile(filename);

  setmainstate(MENU);
  setsubmenustate(STARTMENU);
  setdifficulty(EASY);

  Uint32 t1 = 0, t2 = 0;
  Uint32 deltatime;
  double fps = 144.0;
  double mindelta = 1000 / fps;

  while (getmainstate() != QUIT)
  {
    t1 = SDL_GetTicks();
    deltatime = t1 - t2;

    if (deltatime > mindelta)
    {
      t2 = t1;
      switch (getmainstate())
      {
      case MENU:
        menu();
        break;
      case GAME:
        game();
        break;
      case QUIT:
      default:
        break;
      }
    }
  }

  savescoreboardtofile(filename);
  freescoreboard();
  SDL_Quit();

  return 0;
}
