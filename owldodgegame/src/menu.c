#include "../include/menu.h"
#define MAINMENU_BTARRSIZE 6
#define HELPMENU_BTARRSIZE 1
#define GAMEOVERMENU_BTARRSIZE 5

static Size defaultbtsize = {200, 40};

void drawbuttons(Button *buttons, int size)
{
  for (int i = 0; i < size; i++)
  {
    int padd = 10;
    Point downrigth = {buttons[i].pos.x + defaultbtsize.width, buttons[i].pos.y + defaultbtsize.height};
    renderbox(buttons[i].pos, downrigth, buttons[i].bgcolor);
    Point textpoint = (Point){.x = buttons[i].pos.x + padd, .y = buttons[i].pos.y + padd};
    rendertext(textpoint, c_white, buttons[i].text);
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
void seteasymode(Button *b)
{
  b->selected = true;
  setdifficulty(EASY);
}
void setmediummode(Button *b)
{
  b->selected = true;
  setdifficulty(MEDIUM);
}
void sethardmode(Button *b)
{
  b->selected = true;
  setdifficulty(HARD);
}
void back()
{
  setsubmenustate(STARTMENU);
}
void quit()
{
  setmainstate(QUIT);
}
int brow(int r)
{
  int pad = 20;
  int margin = 20;
  return margin + r * (defaultbtsize.height + pad);
}
int bcol(int c)
{
  int pad = 20;
  int margin = 20;
  return margin + c * (defaultbtsize.width + pad);
}
void setselectedbt(Button *buttons, int size, int idx)
{
  for (int i = 0; i < size; i++)
  {
    if (i == idx)
      buttons[i].bgcolor = c_btselected;
    else
      buttons[i].bgcolor = c_btbgcolor;
  }
}
void resetbtcolors(Button *buttons, int size)
{
  for (int i = 0; i < size; i++)
  {
    buttons[i].bgcolor = c_btbgcolor;
  }
}
void handlehover(SDL_Event *e, Button *buttons, int size)
{
  Point mousepos = {e->button.x, e->button.y};
  for (int i = 0; i < size; i++)
  {
    if (withinbounds((Rect){buttons[i].pos, defaultbtsize}, mousepos))
    {
      buttons[i].bgcolor = (SDL_Color){100, 0, 0, 255};
      break;
    }
  }
}
void handleclick(SDL_Event *e, Button *buttons, int size)
{
  if (e->button.button == SDL_BUTTON_LEFT)
  {
    Point mousepos = {e->button.x, e->button.y};
    for (int i = 0; i < size; i++)
    {
      if (withinbounds((Rect){buttons[i].pos, defaultbtsize}, mousepos))
      {
        buttons[i].onclick(&buttons[i]);
        break;
      }
    }
  }
}
void scoreboard()
{
  int col1 = 500;
  int px = 100;
  int height = 400;
  int py = 40;
  rendertext((Point){col1, height}, c_white, "helyezes");
  rendertext((Point){col1 + px, height}, c_white, "pontszam");
  rendertext((Point){col1 + 2 * px, height}, c_white, "felhasznalonev");
  height += py;
  int i = 1;
  for (ScoreNode *cr = getscores(); cr != NULL; cr = cr->next)
  {
    char place[20];
    sprintf(place, "%d", i);
    char point[20];
    sprintf(point, "%lf", cr->score.points);
    rendertext((Point){col1, height}, c_white, place);
    rendertext((Point){col1 + px, height}, c_white, point);
    rendertext((Point){col1 + 2 * px, height}, c_white, cr->score.playername);
    i++;
    height += py;
  }
}
void startmenu(SDL_Event *e)
{
  renderbox((Point){0, 0}, (Point){WINDOWWIDTH, WINDOWHEIGHT}, (SDL_Color){20, 20, 20, 255});

  Button buttons[MAINMENU_BTARRSIZE] = {
      {{bcol(0), brow(0)}, "Uj jatek", newgame},
      {{bcol(0), brow(1)}, "Segitseg", help},
      {{bcol(0), brow(2)}, "Konnyu", seteasymode},
      {{bcol(1), brow(2)}, "Kozepes", setmediummode},
      {{bcol(2), brow(2)}, "Nehez", sethardmode},
      {{bcol(0), brow(3)}, "Kilepes", quit},
  };
  int offset = 2;
  drawbuttons(buttons, GAMEOVERMENU_BTARRSIZE);
  renderupdate();
  while (getmenustate() == STARTMENU && getmainstate() == MENU)
  {
    while (SDL_PollEvent(e))
    {
      resetbtcolors(buttons, MAINMENU_BTARRSIZE);
      setselectedbt(buttons, MAINMENU_BTARRSIZE, getdifficulty() + offset);
      switch (e->type)
      {
      case SDL_MOUSEMOTION:
        handlehover(e, buttons, MAINMENU_BTARRSIZE);
        break;
      case SDL_MOUSEBUTTONDOWN:
        handleclick(e, buttons, MAINMENU_BTARRSIZE);
        break;
      case SDL_QUIT:
        setmainstate(QUIT);
        return;
        break;
      }
      drawbuttons(buttons, MAINMENU_BTARRSIZE);
    }
    renderupdate();
  }
}
void helpmenu(SDL_Event *e)
{
  renderbox((Point){0, 0}, (Point){WINDOWWIDTH, WINDOWHEIGHT}, (SDL_Color){20, 20, 20, 255});
  Button buttons[HELPMENU_BTARRSIZE] = {
      {{bcol(0), brow(0)}, "Vissza", back},
  };
  rendertext((Point){350, 120}, c_white, "Q kepesseg");
  rendertext((Point){370, 150}, c_white, "Kilo egy kek sugar alaku lovedeket, amely ha eltalal egy ellenseg baglyot, akkor megsemmisiti.");
  rendertext((Point){350, 200}, c_white, "D kepesseg");
  rendertext((Point){370, 230}, c_white, "Egy kisebb tavolsagra teleportalja a karaktert.");
  renderupdate();
  while (getmenustate() == HELPMENU && getmainstate() == MENU)
  {
    while (SDL_PollEvent(e))
    {
      resetbtcolors(buttons, HELPMENU_BTARRSIZE);
      switch (e->type)
      {
      case SDL_MOUSEMOTION:
        handlehover(e, buttons, HELPMENU_BTARRSIZE);
        break;
      case SDL_MOUSEBUTTONDOWN:
        handleclick(e, buttons, HELPMENU_BTARRSIZE);
        break;
      case SDL_QUIT:
        setmainstate(QUIT);
        return;
        break;
      }
      drawbuttons(buttons, HELPMENU_BTARRSIZE);
    }
    renderupdate();
  }
}

static char playername[50];

void gameovermenu(SDL_Event *e)
{
  renderbox((Point){0, 0}, (Point){WINDOWWIDTH, WINDOWHEIGHT}, (SDL_Color){20, 20, 20, 255});
  Button buttons[MAINMENU_BTARRSIZE] = {
      {{bcol(0), brow(0)}, "Ujrakezdes", newgame},
      {{bcol(0), brow(1)}, "Konnyu", seteasymode},
      {{bcol(1), brow(1)}, "Kozepes", setmediummode},
      {{bcol(2), brow(1)}, "Nehez", sethardmode},
      {{bcol(0), brow(2)}, "Vissza", back},
  };
  int diffbtoffset = 1;
  if (strlen(playername) == 0)
  {
    rendertext((Point){20, 20}, c_white, "Nev: ");
    size_t length = 50;
    SDL_Rect pos = {.x = 20, .y = 50, .w = 200, .h = 30};
    bool inputsaved = input_text(playername, length, pos, c_btbgcolor, c_white);
    if (inputsaved)
    {
      insertnewscore(playername);
    }
    renderbox((Point){0, 0}, (Point){WINDOWWIDTH, WINDOWHEIGHT}, (SDL_Color){20, 20, 20, 255});
  }
  else
  {
    drawbuttons(buttons, GAMEOVERMENU_BTARRSIZE);
    insertnewscore(playername);
  }
  scoreboard();
  renderupdate();
  while (getmenustate() == GAMEOVERMENU && getmainstate() == MENU)
  {
    while (SDL_PollEvent(e))
    {
      resetbtcolors(buttons, GAMEOVERMENU_BTARRSIZE);
      setselectedbt(buttons, GAMEOVERMENU_BTARRSIZE, getdifficulty() + diffbtoffset);
      switch (e->type)
      {
      case SDL_MOUSEMOTION:
        handlehover(e, buttons, GAMEOVERMENU_BTARRSIZE);
        break;
      case SDL_MOUSEBUTTONDOWN:
        handleclick(e, buttons, GAMEOVERMENU_BTARRSIZE);
        break;
      case SDL_QUIT:
        setmainstate(QUIT);
        return;
        break;
      }
      drawbuttons(buttons, GAMEOVERMENU_BTARRSIZE);
    }
    renderupdate();
  }
}
void menu(SDL_Event *e)
{
  renderupdate();
  while (getmainstate() == MENU)
  {
    switch (getmenustate())
    {
    case STARTMENU:
      startmenu(e);
      break;
    case HELPMENU:
      helpmenu(e);
      break;
    case GAMEOVERMENU:
      gameovermenu(e);
      break;
    }
  }
}