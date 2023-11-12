#include "../include/mainloop.h"

void loop()
{
  State state = MENU;
  Uint32 t1, t2 = 0, delta;
  double fps = 60.0;
  double mindelta = 1000 / fps;
  while (state != QUIT)
  {
    t1 = SDL_GetTicks();
    delta = t1 - t2;

    if (delta > mindelta)
    {
      // SDL_Log("fps: %d", 1000 / delta);
      t2 = t1;

      SDL_Event e;
      SDL_WaitEvent(&e);
      if (state == MENU)
      {
        menu(&e, &state);
      }
      else
      {
        game(&e, &state);
      }
    }
  }
}