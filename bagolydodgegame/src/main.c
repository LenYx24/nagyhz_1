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

int main(int argc, char *argv[])
{
  srand(time(NULL));

  Size windowsize = {WINDOWWIDTH, WINDOWHEIGHT};
  char *title = "bagolyjatek";
  createwindow(windowsize, title);
  // scoreboard load file

  loop();

  rendererquit();
  return 0;
}
