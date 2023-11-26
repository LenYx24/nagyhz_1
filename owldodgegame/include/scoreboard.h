#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <stdbool.h>
#include <string.h>

#include "../lib/debugmalloc.h"

#include "state.h"

typedef struct Score {
  double points;
  char playername[50];
} Score;
typedef struct ScoreNode {
  Score score;
  struct ScoreNode *prev, *next;
} ScoreNode;

void loadscoresfromfile(char *filename);
void savescoreboardtofile(char *filename);
ScoreNode *getscores();
double getcurrentpoint();
void incrementcurrentscore(int point);
void resetcurrentpoint();
void insertnewscore(char *name);
void freescoreboard();
#endif