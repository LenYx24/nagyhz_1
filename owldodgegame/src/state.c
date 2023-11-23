#include "../include/state.h"
States state;
MainState getmainstate()
{
    return state.main;
}
MenuState getmenustate()
{
    return state.main;
}
void setmainstate(MainState s)
{
    state.main = s;
}
void setsubmenustate(MenuState s)
{
    state.menu = s;
}
