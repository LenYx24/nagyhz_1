#ifndef MENU_H
#define MENU_H
/*
 * @file menu.h
 * @brief A menünézetért felelős modul
 * Ez a modul jeleníti meg a gombokat és a dicsőséglistát
 */
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../lib/debugmalloc.h"

#include "macros.h"
#include "math_helper.h"
#include "render.h"
#include "scoreboard.h"
#include "state.h"
/**
 * @brief Egy gomb adatait eltároló struktúra
 *
 */
typedef struct Button {
  Point pos;                          /**< a gomb pozicíója*/
  char text[30];                      /**< a gomb szövege*/
  void (*onclick)(struct Button *bt); /**< a gombra való kattintáskor ez a
                                         függvény hívódik meg*/
  bool selected; /**< ha a felhasználó utoljára erre a gombra kattintott akkor
                    igaz (csak azoknál a gomboknál van beállítva amelynél számít
                    (nehézségkiválasztás gombjai))*/
  SDL_Color bgcolor; /**< a gomb háttérszíne*/
} Button;
/**
 * @brief A függvény az almenüállapot alapján mutatja valamelyik menüt
 *
 */
void menu();
#endif