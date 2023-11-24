#include "../include/mainloop.h"

void loop()
{
  setmainstate(MENU);
  setsubmenustate(STARTMENU);
  setdifficulty(EASY);
  Uint32 t1, t2 = 0, delta;
  double fps = 144.0;
  double mindelta = 1000 / fps;
  SDL_Event e;
  while (getmainstate() != QUIT)
  {
    t1 = SDL_GetTicks();
    delta = t1 - t2;

    if (delta > mindelta)
    {
      // SDL_Log("fps: %d", 1000 / delta);
      t2 = t1;
      switch (getmainstate())
      {
      case MENU:
        menu(&e);
        break;
      case GAME:
        game(&e);
        break;
      case QUIT:
        break;
      }
    }
  }
}