#include "../include/mainloop.h"

void loop()
{
  State state = MENU;
  Uint32 t1, t2 = 0, delta;
  double fps = 144.0;
  double mindelta = 1000 / fps;
  SDL_Event e;
  while (state != QUIT)
  {
    t1 = SDL_GetTicks();
    delta = t1 - t2;

    if (delta > mindelta)
    {
      // SDL_Log("fps: %d", 1000 / delta);
      t2 = t1;
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