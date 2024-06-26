#include "../include/menu.h"
#define MAINMENU_BTARRSIZE 7
#define HELPMENU_BTARRSIZE 1
#define GAMEOVERMENU_BTARRSIZE 5

static Size defaultbtsize = {200, 40};
static char playername[50 + 1] = "\0";

void drawbuttons(Button *buttons, int size) {
  for (int i = 0; i < size; i++) {
    int padd = 10;
    Point downrigth = {buttons[i].pos.x + defaultbtsize.width,
                       buttons[i].pos.y + defaultbtsize.height};
    renderbox(buttons[i].pos, downrigth, buttons[i].bgcolor);
    Point textpoint =
        (Point){.x = buttons[i].pos.x + padd, .y = buttons[i].pos.y + padd};
    rendertext(textpoint, c_white, buttons[i].text);
  }
}
void resetbackground() {
  renderbox((Point){0, 0}, (Point){WINDOWWIDTH, WINDOWHEIGHT}, c_menubg);
}
void newgame() { setmainstate(GAME); }
void help() { setsubmenustate(HELPMENU); }
void seteasymode(Button *b) {
  b->selected = true;
  setdifficulty(EASY);
}
void setmediummode(Button *b) {
  b->selected = true;
  setdifficulty(MEDIUM);
}
void sethardmode(Button *b) {
  b->selected = true;
  setdifficulty(HARD);
}
void newname() {
  resetbackground();
  rendertext((Point){20, 20}, c_white,
             "Add meg az uj felhasznaloneved (maximum 50 karakter): ");
  char currentname[31 + 51];
  sprintf(currentname, "jelenlegi felhasznaloneved: %s", playername);
  rendertext((Point){20, 50}, c_white, currentname);
  size_t length = 50;
  SDL_Rect pos = {.x = 20, .y = 100, .w = 200, .h = 30};
  input_text(playername, length, pos, c_btbg, c_white);
  resetbackground();
}
void back() { setsubmenustate(STARTMENU); }
void quit() { setmainstate(QUIT); }
int brow(int r) {
  int pad = 20;
  int margin = 20;
  return margin + r * (defaultbtsize.height + pad);
}
int bcol(int c) {
  int pad = 20;
  int margin = 20;
  return margin + c * (defaultbtsize.width + pad);
}
void setselectedbt(Button *buttons, int size, int idx) {
  for (int i = 0; i < size; i++) {
    if (i == idx)
      buttons[i].bgcolor = c_btselected;
    else
      buttons[i].bgcolor = c_btbg;
  }
}
void resetbtcolors(Button *buttons, int size) {
  for (int i = 0; i < size; i++) {
    buttons[i].bgcolor = c_btbg;
  }
}
void handlehover(SDL_Event *e, Button *buttons, int size) {
  Point mousepos = {e->button.x, e->button.y};
  for (int i = 0; i < size; i++) {
    if (withinbounds((Rect){buttons[i].pos, defaultbtsize}, mousepos)) {
      buttons[i].bgcolor = c_btbghover;
      break;
    }
  }
}
void handleclick(SDL_Event *e, Button *buttons, int size) {
  if (e->button.button == SDL_BUTTON_LEFT) {
    Point mousepos = {e->button.x, e->button.y};
    for (int i = 0; i < size; i++) {
      if (withinbounds((Rect){buttons[i].pos, defaultbtsize}, mousepos)) {
        buttons[i].onclick(&buttons[i]);
        break;
      }
    }
  }
}
void scoreboard() {
  int col1 = 700;
  int px = 100;
  int height = 10;
  int py = 40;

  rendertext((Point){col1, height}, c_white, "helyezes");
  rendertext((Point){col1 + px, height}, c_white, "pontszam");
  rendertext((Point){col1 + 2 * px, height}, c_white, "felhasznalonev");

  height += py;
  int i = 1;
  for (ScoreNode *cr = getscores(); cr != NULL; cr = cr->next) {
    char place[20];
    sprintf(place, "%d.", i);
    char point[20];
    sprintf(point, "%.2lf", cr->score.points);
    rendertext((Point){col1, height}, c_white, place);
    rendertext((Point){col1 + px, height}, c_white, point);
    rendertext((Point){col1 + 2 * px, height}, c_white, cr->score.playername);
    i++;
    height += py;
  }
}
void startmenu() {

  Button buttons[MAINMENU_BTARRSIZE] = {
      {{bcol(0), brow(0)}, "Uj jatek", newgame},
      {{bcol(0), brow(1)}, "Segitseg", help},
      {{bcol(0), brow(2)}, "Konnyu", seteasymode},
      {{bcol(1), brow(2)}, "Kozepes", setmediummode},
      {{bcol(2), brow(2)}, "Nehez", sethardmode},
      {{bcol(0), brow(3)}, "Uj nev", newname},
      {{bcol(0), brow(4)}, "Kilepes", quit},
  };
  // a tömbben melyik elemtől kezdődnek a nehézséget szabályzó gombok
  int offset = 2;
  drawbuttons(buttons, GAMEOVERMENU_BTARRSIZE);
  scoreboard();
  SDL_Event e;
  renderupdate();
  while (getmenustate() == STARTMENU && getmainstate() == MENU) {
    while (SDL_PollEvent(&e)) {
      resetbtcolors(buttons, MAINMENU_BTARRSIZE);
      setselectedbt(buttons, MAINMENU_BTARRSIZE, getdifficulty() + offset);
      switch (e.type) {
      case SDL_MOUSEMOTION:
        handlehover(&e, buttons, MAINMENU_BTARRSIZE);
        break;
      case SDL_MOUSEBUTTONDOWN:
        handleclick(&e, buttons, MAINMENU_BTARRSIZE);
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
void helpmenu() {
  Button buttons[HELPMENU_BTARRSIZE] = {
      {{bcol(0), brow(0)}, "Vissza", back},
  };
  rendertext((Point){350, 120}, c_white, "Q kepesseg");
  rendertext((Point){370, 150}, c_white,
             "Kilo egy kek sugar alaku lovedeket, amely ha eltalal egy "
             "ellenseg baglyot, akkor megsemmisiti.");
  rendertext((Point){350, 200}, c_white, "D kepesseg");
  rendertext((Point){370, 230}, c_white,
             "Egy kisebb tavolsagra teleportalja a karaktert.");

  SDL_Event e;
  renderupdate();
  while (getmenustate() == HELPMENU && getmainstate() == MENU) {
    while (SDL_PollEvent(&e)) {
      resetbtcolors(buttons, HELPMENU_BTARRSIZE);
      switch (e.type) {
      case SDL_MOUSEMOTION:
        handlehover(&e, buttons, HELPMENU_BTARRSIZE);
        break;
      case SDL_MOUSEBUTTONDOWN:
        handleclick(&e, buttons, HELPMENU_BTARRSIZE);
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

void gameovermenu() {
  Button buttons[GAMEOVERMENU_BTARRSIZE] = {
      {{bcol(0), brow(0)}, "Ujrakezdes", newgame},
      {{bcol(0), brow(1)}, "Konnyu", seteasymode},
      {{bcol(1), brow(1)}, "Kozepes", setmediummode},
      {{bcol(2), brow(1)}, "Nehez", sethardmode},
      {{bcol(0), brow(2)}, "Vissza", back},
  };

  // a tömbben melyik elemtől kezdődnek a nehézséget szabályzó gombok
  int diffbtoffset = 1;

  // ha üres a név mező akkor kell bekérni a felhasználó nevét
  if (strlen(playername) == 0) {
    rendertext((Point){20, 20}, c_white,
               "Add meg a felhasznaloneved (maximum 50 karakter): ");
    size_t length = 50;
    SDL_Rect pos = {.x = 20, .y = 50, .w = 200, .h = 30};
    bool inputsaved = input_text(playername, length, pos, c_btbg, c_white);
    if (inputsaved) {
      insertnewscore(playername);
    }
  } else {
    drawbuttons(buttons, GAMEOVERMENU_BTARRSIZE);
    insertnewscore(playername);
  }
  resetbackground();
  scoreboard();
  renderupdate();
  SDL_Event e;
  while (getmenustate() == GAMEOVERMENU && getmainstate() == MENU) {
    while (SDL_PollEvent(&e)) {
      resetbtcolors(buttons, GAMEOVERMENU_BTARRSIZE);
      setselectedbt(buttons, GAMEOVERMENU_BTARRSIZE,
                    getdifficulty() + diffbtoffset);
      switch (e.type) {
      case SDL_MOUSEMOTION:
        handlehover(&e, buttons, GAMEOVERMENU_BTARRSIZE);
        break;
      case SDL_MOUSEBUTTONDOWN:
        handleclick(&e, buttons, GAMEOVERMENU_BTARRSIZE);
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
void menu() {
  renderupdate();
  while (getmainstate() == MENU) {
    resetbackground();
    switch (getmenustate()) {
    case STARTMENU:
      startmenu();
      break;
    case HELPMENU:
      helpmenu();
      break;
    case GAMEOVERMENU:
      gameovermenu();
      break;
    }
  }
}