#include "../include/scoreboard.h"
static ScoreNode *scores = NULL;
static double currentpoint = 0;
static double mediummultiplier = 1.5f;
static double hardmultiplier = 2.0f;

void loadscoresfromfile(char *filename) {
  FILE *f;
  f = fopen(filename, "r");
  if (f != NULL) {
    for (int i = 0; i < 5; i++) {
      char row[256];
      if (fgets(row, 256, f) != NULL) {
        ScoreNode *s = (ScoreNode *)malloc(sizeof(ScoreNode));
        // adatbetöltés
        double pts;
        sscanf(row, "%lf;%s", &pts, s->score.playername);
        s->score.points = pts;

        s->next = scores;
        s->prev = NULL;

        if (scores != NULL) {
          scores->prev = s;
        }

        scores = s;
      } else
        break;
    }
  } else {
    f = fopen(filename, "w");
  }

  fclose(f);
}
void savescoreboardtofile(char *filename) {
  FILE *f;
  f = fopen(filename, "w");
  if (f != NULL) {
    for (ScoreNode *current = scores; current != NULL;
         current = current->next) {
      fprintf(f, "%lf;%s\n", current->score.points, current->score.playername);
    }
  }
  fclose(f);
}
ScoreNode *getscores() { return scores; }
double getcurrentpoint() { return currentpoint; }
void resetcurrentpoint() { currentpoint = 0; }

void incrementcurrentscore(int point) {
  switch (getdifficulty()) {
  case EASY:
    currentpoint += point;
    break;
  case MEDIUM:
    currentpoint += point * mediummultiplier;
    break;
  case HARD:
    currentpoint += point * hardmultiplier;
    break;
  }
}
void insertnewscore(char *name) {
  ScoreNode *newnode = (ScoreNode *)malloc(sizeof(ScoreNode));
  newnode->score = (Score){currentpoint};
  strcpy(newnode->score.playername, name);
  newnode->next = NULL;
  newnode->prev = NULL;
  if (scores == NULL) {
    scores = newnode;
  } else {
    bool inserted = false;
    int numofscores = 1;
    ScoreNode *last = scores;
    while (last->next != NULL) {
      numofscores++;
      last = last->next;
    }
    for (ScoreNode *current = scores; current != NULL;
         current = current->next) {
      if (current->score.points < currentpoint) {
        if (current->prev == NULL) // ha a jelenlegi elemnek nincs előző eleme,
                                   // akkor a lista elejére szúrúnk be
        {
          newnode->next = scores;
          current->prev = newnode;
          scores = newnode;
        } else {
          newnode->prev = current->prev;
          newnode->prev->next = newnode;
          newnode->next = current;
          current->prev = newnode;
        }
        inserted = true;
        if (numofscores == 5) // ha mind az öt hely le van foglalva, akkor az
                              // utolsó hatodik elemet törölni kell
        {
          ScoreNode *tmp = last->prev;
          free(last);
          tmp->next = NULL;
        }
        break;
      }
    }
    if (!inserted &&
        numofscores < 5) // ha nem szúrtunk be az utolsóig, de még van hely a
                         // végén, akkor oda kerül az új érték
    {
      last->next = newnode;
    }
  }
}

void freescoreboard() {
  ScoreNode *current = scores;
  while (current != NULL) {
    ScoreNode *tmp = current->next;
    free(current);
    current = tmp;
  }
}