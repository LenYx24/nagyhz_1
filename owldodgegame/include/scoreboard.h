#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include "state.h"
typedef struct Score{
    int score;
    Difficulty diff;
    char *playername;
}Score;
void loadfromfile();
void savetofile();
#endif