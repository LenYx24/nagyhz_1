#include "../include/state.h"
States state = {MENU, STARTMENU};
Difficulty difficulty = EASY;
MainState getmainstate() { return state.main; }
MenuState getmenustate() { return state.menu; }
Difficulty getdifficulty() { return difficulty; }
void setmainstate(MainState s) { state.main = s; }
void setsubmenustate(MenuState s) { state.menu = s; }
void setdifficulty(Difficulty diff) { difficulty = diff; }
