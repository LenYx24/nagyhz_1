#ifndef STATE_H
#define STATE_H
/*
 * @file state.h
 * @brief A játék állapotát tartja számon egy belső változóban, amelyet
 * függvényeken keresztül tesz elérhetővé a külső modulok számára.
 * A belső state változó alapértelmezett értéke a MENU főállapot és a STARTMENU
 * almenüállapot. A nehézség alapértelmezett értéke EASY
 */
#include <SDL2/SDL.h>
#include <stdlib.h>
/**
 * @brief A főállapotot leíró felsorolt típus
 *
 */
typedef enum MainState { MENU, GAME, QUIT } MainState;
/**
 * @brief A menü főállapoton belül lévő almenüket leíró felsorolt típus
 *
 */
typedef enum MenuState {
  STARTMENU,
  HELPMENU,
  GAMEOVERMENU,
} MenuState;
/**
 * @brief A játékban használt nehézséget leíró felsorolt típus
 *
 */
typedef enum Difficulty { EASY, MEDIUM, HARD } Difficulty;
/**
 * @brief A főállapotot és az almenü állapotot tartalmazó struktúra
 *
 */
typedef struct States {
  MainState main;
  MenuState menu;
} States;
/**
 * @brief Visszaadja a főállapotának jelenlegi értékét
 *
 * @return MainState
 */
MainState getmainstate();
/**
 * @brief Visszaadja a menü alállapotának jelenlegi értékét
 *
 * @return MenuState
 */
MenuState getmenustate();
/**
 * @brief Visszaadja a játék jelenleg beállított nehézségét
 *
 * @return Difficulty
 */
Difficulty getdifficulty();
/**
 * @brief Beállítja a paraméterként kapott állapotra a főállapotot
 *
 * @param state
 */
void setmainstate(MainState state);
/**
 * @brief Beállítja a paraméterként kapott állapotra az almenüállapotot
 *
 * @param s
 */
void setsubmenustate(MenuState s);
/**
 * @brief Beállítja a program nehézségét a paraméterként kapott nehézségértékre
 *
 * @param diff
 */
void setdifficulty(Difficulty diff);
#endif
