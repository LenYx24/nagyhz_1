#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/debugmalloc.h"

#include "../include/entity.h"
#include "../include/math_helper.h"
#include "../include/render.h"
#include "../include/mainloop.h"
#include "../include/macros.h"
#include "../include/scoreboard.h"

int main(int argc, char *argv[])
{
  srand((unsigned)time(0));

  Size windowsize = {WINDOWWIDTH, WINDOWHEIGHT};
  char *title = "bagolyjatek";
  createwindow(windowsize, title);
  // char filename[] = "scoreboard.txt";
  // loadfromfile(filename);

  loop();

  // scoreboard save
  SDL_Quit();
  return 0;
}
