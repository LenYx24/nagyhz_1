#include "../include/menu.h"
void button(char *name, Rect rect)
{
  renderbox(rect.pos, rectdownrightpoint(rect), (SDL_Color){200, 0, 0, 255});
  Point textpoint = (Point){.x = rect.pos.x + 10, .y = rect.pos.y + 10};
  rendertext(textpoint, (SDL_Color){255, 255, 255, 255}, name);
}
void menu(SDL_Event *e, State *state)
{
  int pady = 20;
  Size btsize = {180, 30};

  Rect startbt = {.pos = {20, pady}, btsize};
  button("Start", startbt);

  Rect exitbt = {.pos = {20, 2 * pady + btsize.height}, btsize};
  button("Exit", exitbt);

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
        else if (withinbounds(exitbt, mousepos))
        {
          *state = QUIT;
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