#ifndef SCOREBOARD_H
#define SCOREBOARD_H
/*
 * @file scoreboard.h
 * @brief A dicsőségtábláért felelős modul
 * A dicsőségtáblát tárolja egy belső változóban amit függvényekkel érhetnek el
 * a külső modulok
 */
#include <stdbool.h>
#include <string.h>

#include "../lib/debugmalloc.h"

#include "state.h"
/**
 * @brief Egy adott pontszámot eltároló struktúra
 *
 */
typedef struct Score {
  double points;           /**< Az adott pontszám*/
  char playername[50 + 1]; /**< A játékos neve (maximum 50 karakter hosszú)*/
} Score;
/**
 * @brief Az eredményeket tartalmazó láncolt lista egy elemét leíró struktúra
 *
 */
typedef struct ScoreNode {
  Score score;                   /**< az elért eredmény*/
  struct ScoreNode *prev, *next; /**< a lista következő eleme*/
} ScoreNode;
/**
 * @brief Betölti a dicsőséglista állását a fájlból
 * ha nincs ilyen fájl, akkor létrehozza azt
 * @param filename a fájl elérési útvonala
 */
void loadscoresfromfile(char *filename);
/**
 * @brief Elmenti a dicsőséglista állását az adott fájlba
 *
 * @param filename a fájl elérési útvonala
 */
void savescoreboardtofile(char *filename);
/**
 * @brief Visszaadja a modul által tárolt láncolt lista első elemére mutató
 * pointert
 *
 * @return ScoreNode* a láncolt lista
 */
ScoreNode *getscores();
/**
 * @brief Visszaadja a jelenlegi körben elért pontszámot
 *
 * @return double
 */
double getcurrentpoint();
/**
 * @brief Növeli a modul által tárolt pontszámot a nehézség szerint
 *
 * @param point
 */
void incrementcurrentscore(int point);
/**
 * @brief Alaphelyzetbe állítja a modul által tárolt pontszámot
 *
 */
void resetcurrentpoint();
/**
 * @brief A modul által tárolt listába beszúrja az új eredményt
 *
 * @param name Ehhez a névhez fog tartozni a körben elért pontszám
 */
void insertnewscore(char *name);
/**
 * @brief Felszabadítja a modul által tárolt dicsőséglistát (ami egy láncolt
 * lista)
 * A program végén meg kell hívni
 */
void freescoreboard();
#endif