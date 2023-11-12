#include "../include/menu.h"
void menu(Event *e, State *state) {
  renderbox((Point){20, 20}, (Point){200, 50}, (Color){200, 0, 0, 255});
  rendertext((Point){100, 30}, (Color){255, 255, 255, 255}, "Start");
  renderupdate();
  if (e.event != NULL) {
    printf("etype: %d\n",e->event->type);
    switch (e.event->type) {
    case SDL_MOUSEBUTTONDOWN:
      if (e.event->button.button == SDL_BUTTON_LEFT) {
        Point mousepos = {e.event->button.x, e.event->button.y};
        Rect bt1 = {(Point){20, 20}, (Size){120, 70}};
        if (withinbounds(bt1, mousepos)) {
          printf("withinbounds");
          *state = GAME;
        }
      }
      break;
    case SDL_QUIT:
      printf("SDL_QUIT");
      *state = QUIT;
      break;
    }
  }
}