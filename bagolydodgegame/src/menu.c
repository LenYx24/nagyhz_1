#include "../include/menu.h"

void menu(SDL_Event *e, State *state)
{
  renderbox((Point){20, 20}, (Point){200, 50}, (Color){200, 0, 0, 255});
  rendertext((Point){100, 30}, (Color){255, 255, 255, 255}, "Start");
  renderupdate();
  if (e != NULL)
  {
    switch (e->type)
    {
    case SDL_MOUSEBUTTONDOWN:
      if (e->button.button == SDL_BUTTON_LEFT)
      {
        Point mousepos = {e->button.x, e->button.y};
        Rect bt1 = {(Point){20, 20}, (Size){120, 70}};
        if (withinbounds(bt1, mousepos))
        {
          *state = GAME;
        }
      }
      break;
    case SDL_QUIT:
      *state = QUIT;
      break;
    }
  }
}