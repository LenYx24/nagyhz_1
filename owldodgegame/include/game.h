#ifndef GAME_H
#define GAME_H
/*
 * @file game.h
 * @brief A játékban egy kör lefutásáért felelős modul
 * Miután véget ért egy kör, átállítja a program állapotat menüre, vagy
 * kilépésre Az összes dinamikusan foglalt memóriaterületet felszabadítja
 * magától. A főbb csomópont a megjelenítő és az adatművelettel foglalkozó
 * modulok között
 *
 */
#include <SDL2/SDL.h>
#include <math.h>

#include "../lib/debugmalloc.h"

#include "entity.h"
#include "macros.h"
#include "overlay.h"
#include "render.h"
#include "scoreboard.h"
#include "state.h"
/**
 * @brief tárolja azokat az adatokat, amelyek szükségesek ahhoz hogy a
 * játékosnak visszajelezze azt ahova kattintott
 *
 */
typedef struct showposclickfeedback {
  int counter;
  int limit;
  bool show;
  Point pos;
} showposclickfeedback;
/*
 * @brief Levezényel egy kört a játékon belül
 * létrehozza a pályát, játékost, és ellenségeket, majd a render modult
 * használva megjeleníti őket.
 *
 * Kiértékeli az entitások mozgását matematikai számításokkal, és érzékeli, hogy
 * űtközött-e a játékos ellenséggel, mert ha igen, akkor a kör véget ér, és
 * visszatér a függvény
 * @return void
 */
void game();
#endif