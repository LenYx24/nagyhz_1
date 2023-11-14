#include "../include/menu.h"
void button(char *name, Rect rect)
{
  renderbox(rect.pos, rectdownrightpoint(rect), (SDL_Color){200, 0, 0, 255});
  Point textpoint = (Point){.x = rect.pos.x + 10, .y = rect.pos.y + (rect.size.height / 2)};
  rendertext(textpoint, (SDL_Color){255, 255, 255, 255}, "Start");
}
void menu(SDL_Event *e, State *state)
{
  int pady = 20;
  Size btsize = {180, 30};
  Rect startbt = {.pos = {20, pady}, btsize};
  button("Start", startbt);
  Rect exitbt = {.pos = {20, pady + btsize.y}, btsize};
  button("Start", startbt);
  renderupdate();
  while (*state == MENU)
  {
    SDL_WaitEvent(e);
    switch (e->type)
    {
    case SDL_MOUSEBUTTONDOWN:
      if (e->button.button == SDL_BUTTON_LEFT)
      {
        Point mousepos = {e->button.x, e->button.y};
        if (withinbounds(startbt, mousepos))
        {
          *state = GAME;
        }
      }
      break;
    case SDL_QUIT:
      *state = QUIT;
      break;
    }
    renderupdate();
  }
}