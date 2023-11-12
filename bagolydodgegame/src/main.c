#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "../lib/debugmalloc.h"

#include "../include/entity.h"
#include "../include/init.h"
#include "../include/math_helper.h"
#include "../include/render.h"
#include "../include/mainloop.h"

int main(int argc, char *argv[]) {
  Size windowsize = {1280, 960};
  init(windowsize, "bagoly jatek");
  
  loop();

  rendererquit();
  return 0;
}
