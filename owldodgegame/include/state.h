#ifndef STATE_H
#define STATE_H
#include <stdlib.h>
typedef enum MainState
{
    MENU,
    GAME,
    QUIT
} MainState;
typedef enum MenuState
{
    STARTMENU,
    HELPMENU,
    GAMEOVERMENU,
} MenuState;
typedef struct States
{
    MainState main;
    MenuState menu;
} States;
MainState getmainstate();
MenuState getmenustate();
void setmainstate(MainState state);
void setsubmenustate(MenuState s);
#endif