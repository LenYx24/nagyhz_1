#include "../include/menu.h"
#define BUTTONARRSIZE 6

static Size defaultbtsize = {180, 30};

void drawbuttons(Button *buttons, int size)
{
  for (int i = 0; i < size; i++)
  {
    int padd = 10;
    Point downrigth = {buttons[i].pos.x + defaultbtsize.width, buttons[i].pos.y + defaultbtsize.height};
    renderbox(buttons[i].pos, downrigth, buttons[i].bgcolor);
    Point textpoint = (Point){.x = buttons[i].pos.x + padd, .y = buttons[i].pos.y + padd};
    rendertext(textpoint, (SDL_Color){255, 255, 255, 255}, buttons[i].text);
  }
}
void newgame()
{
  setmainstate(GAME);
}
void help()
{
  setsubmenustate(HELPMENU);
}
void back()
{
  setsubmenustate(STARTMENU);
}
void quit()
{
  setmainstate(QUIT);
}
int row(int r)
{
  int pad = 20;
  int margin = 20;
  return margin + r * (defaultbtsize.height + pad);
}
int col(int c)
{
  int margin = 20;
  int pad = 20;
  return margin + c * (defaultbtsize.width + pad);
}
void resetbtcolors(Button *buttons)
{
  for (int i = 0; i < BUTTONARRSIZE; i++)
  {
    buttons[i].bgcolor = (SDL_Color){200, 0, 0, 255};
  }
}
void handlehover(SDL_Event *e, Button *buttons)
{
  Point mousepos = {e->button.x, e->button.y};
  for (int i = 0; i < BUTTONARRSIZE; i++)
  {
    if (withinbounds((Rect){buttons[i].pos, defaultbtsize}, mousepos))
    {
      buttons[i].bgcolor = (SDL_Color){100, 0, 0, 255};
      break;
    }
  }
}
void handleclick(SDL_Event *e, Button *buttons)
{
  if (e->button.button == SDL_BUTTON_LEFT)
  {
    Point mousepos = {e->button.x, e->button.y};
    for (int i = 0; i < BUTTONARRSIZE; i++)
    {
      if (withinbounds((Rect){buttons[i].pos, defaultbtsize}, mousepos))
      {
        buttons[i].onclick();
        break;
      }
    }
  }
}
void helpmenu(SDL_Event *e)
{
  renderbox((Point){0, 0}, (Point){WINDOWWIDTH, WINDOWHEIGHT}, (SDL_Color){20, 20, 20, 255});
  Button buttons[BUTTONARRSIZE] = {
      {{col(0), row(0)}, "Vissza", back},
  };
  rendertext((Point){col(2), row(2)}, (SDL_Color){255, 255, 255, 255}, "Q kepesseg");
  rendertext((Point){col(3), row(2)}, (SDL_Color){255, 255, 255, 255}, "Kilo egy kek sugar alaku lovedeket, amely ha eltalal egy rossz baglyot, akkor megsemmisiti.");
  rendertext((Point){col(2), row(2)}, (SDL_Color){255, 255, 255, 255}, "D kepesseg");
  rendertext((Point){col(3), row(2)}, (SDL_Color){255, 255, 255, 255}, "Egy kisebb tavolsagra teleportalja a karaktert.");
  renderupdate();
  while (getmenustate() == HELPMENU)
  {
    while (SDL_PollEvent(e))
    {
      resetbtcolors(buttons);
      switch (e->type)
      {
      case SDL_MOUSEMOTION:
        handlehover(e, buttons);
        break;
      case SDL_MOUSEBUTTONDOWN:
        handleclick(e, buttons);
        break;
      case SDL_QUIT:
        setmainstate(QUIT);
        break;
      }
      drawbuttons(buttons, BUTTONARRSIZE);
    }
    renderupdate();
  }
}
void menu(SDL_Event *e)
{
  renderbox((Point){0, 0}, (Point){WINDOWWIDTH, WINDOWHEIGHT}, (SDL_Color){20, 20, 20, 255});

  Button buttons[BUTTONARRSIZE] = {
      {{col(0), row(0)}, "Uj jatek", newgame},
      {{col(0), row(1)}, "Segitseg", help},
      {{col(0), row(2)}, "Konnyu", help},
      {{col(1), row(2)}, "Kozepes", help},
      {{col(2), row(2)}, "Nehez", help},
      {{col(0), row(3)}, "Kilepes", quit},
  };
  resetbtcolors(buttons);
  renderupdate();
  while (getmainstate() == MENU)
  {
    while (SDL_PollEvent(e))
    {
      resetbtcolors(buttons);
      switch (e->type)
      {
      case SDL_MOUSEMOTION:
        handlehover(e, buttons);
        break;
      case SDL_MOUSEBUTTONDOWN:
        handleclick(e, buttons);
        break;
      case SDL_QUIT:
        setmainstate(QUIT);
        break;
      }
      drawbuttons(buttons, BUTTONARRSIZE);
    }
    renderupdate();
  }
}