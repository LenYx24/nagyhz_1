#include "../include/mainloop.h"

void loop(){
    State state = MENU;
    while (state != QUIT) {
    Event e;
    SDL_WaitEvent(&e.event);
    if (state == MENU) {
      menu(&e, &state);
    } else {
      game(&e, &state);
    }
  }
}