#include "../include/mainloop.h"
void loop(){
    State state = MENU;
    while (state != QUIT) {
    Event *event = NULL;
    waitevent(event);
    if (state == MENU) {
      menu(event, &state);
    } else {
      game(event, &state);
    }
  }
}