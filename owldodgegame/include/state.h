#ifndef STATE_H
#define STATE_H
#include "SDL2/SDL.h"
#include <stdlib.h>

#define WINDOWWIDTH 1280
#define WINDOWHEIGHT 960
typedef enum MainState { MENU, GAME, QUIT } MainState;
typedef enum MenuState {
  STARTMENU,
  HELPMENU,
  GAMEOVERMENU,
} MenuState;
typedef enum Difficulty { EASY, MEDIUM, HARD } Difficulty;
typedef struct States {
  MainState main;
  MenuState menu;
} States;
MainState getmainstate();
MenuState getmenustate();
Difficulty getdifficulty();
void setmainstate(MainState state);
void setsubmenustate(MenuState s);
void setdifficulty(Difficulty diff);
#endif