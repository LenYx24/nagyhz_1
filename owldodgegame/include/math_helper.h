#ifndef MATH_HELPER_H
#define MATH_HELPER_H
/*
 * @file math_helper.h
 * @brief A játékban használt matematikai műveletet segítő függvényeket ad a
 * modul Itt vannak deklarálva a geometriában értelmezett struktúrák is
 * (mint pl. a pont, vektor...)
 *
 */
#define PI 3.1416

#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "macros.h"
#include "state.h"
/**
 * @brief Egy pontot jelképez a koordinátarendszerben valós típusú x és y
 * változókkal
 *
 */
typedef struct Point {
  double x, y;
} Point;
/**
 * @brief Egy origó kezdőpontú vektort ír le az alábbi struktúra valós típusú x
 * és y változókkal
 *
 */
typedef struct Vector2 {
  double x, y;
} Vector2;
/**
 * @brief Egy méretet egész típusú szélesség és magasság változókkal leírt
 * struktúra
 *
 */
typedef struct Size {
  int width, height;
} Size;
/**
 * @brief Egy téglalapot ír le egy pont és egy mérettel.
 * A pont a téglalap közepére mutat
 *
 *
 */
typedef struct Rect {
  Point pos;
  Size size;
} Rect;
/**
 * @brief Létrehoz a pálya szélein (egy picivel beljebb) véletlenszerűen
 * generált koordinátát
 *
 * @return Point
 */
Point randomspawnpoint();
/**
 * @brief a pos középpontú és size méretű téglalap bal felső koordinátáját adja
 * vissza
 *
 * @param pos a téglalap középpontja
 * @param size a téglalap mérete
 * @return Point a bal felső koordináta
 */
Point gettopleftpoint(Point pos, Size size);
/**
 * @brief hozzáad egy ponthoz egy vektort
 *
 * @param p a pont
 * @param v a vektor
 * @return Point az így kapott pontot adja vissza
 */
Point addvectortopoint(Point p, Vector2 v);
/**
 * @brief a rect-ként téglalap jobb alsó koordinátáját adja vissza
 *
 * @param rect a téglalap
 * @return Point a jobb alsó koordináta
 */
Point rectdownrightpoint(Rect rect);

/**
 * @brief Két pontból egy vektort csinál.
 *
 * @param start A kezdőpont koordinátája
 * @param end A végpont koordinátája
 * @return Vector2 A két pont által kapott vektor
 */
Vector2 vectorfromtwopoints(Point start, Point end);
/**
 * @brief Normalizálja a vektort, vagyis megtartja az irányát, de a hosszúságát
 * egyre állítja be
 *
 * @param v a vektor
 * @return Vector2 a kapott egy hosszúságú vektor
 */
Vector2 normalizevector(Vector2 v);

/**
 * @brief Megnézi, hogy az adott téglalapban benne van-e a pont
 *
 * @param r téglalap
 * @param p pont
 * @return boolean ha benne van a pont akkor igazzal tér vissza, ha nincs benne,
 * akkor hamissal
 */
bool withinbounds(Rect r, Point p);
/**
 * @brief megnézi, hogy a kapott pos középpontú és size méretű téglalap a
 * képernyőn kívűl van-e
 *
 * @param pos a téglalap középpontja
 * @param size a téglalap mérete
 * @return boolean ha a képernyőn kívűl van, akkor igazzal tér vissza, ha nem
 * akkor meg hamissal
 */
bool outofscreen(Point pos, Size size);

/**
 * @brief Kiszámolja a paraméterként kapott két pont távolságát és visszaadja
 * annak egész típusú értékét
 *
 * @param p1 első pont
 * @param p2 második pont
 * @return int a két pont távolsága
 */
int twopointsdistance(Point p1, Point p2);
/**
 * @brief Megadja, hogy az adott vektornak mekkora a hossza
 *
 * @param v vektor
 * @return int a vektor hossza egész típusú változóként
 */
int vectorlength(Vector2 v);

/**
 * @brief Az sdl más formátumban kéri a forgatáshoz szükséges szöget, ez a
 * függvény ezt az új szöget számolja ki
 *
 * @param v a vektor
 * @return double visszaadja valós típusú értékben, hogy sdl-nek hogyan kell
 * megadni a forgatás értékét
 */
double getangle(Vector2 v);
/**
 * @brief a kapott vektort elfordítja adott szöggel
 *
 * @param v a forgatni kívánt vektor
 * @param angle a szög
 * @return Vector2 az elforgatott vektor
 */
Vector2 rotatevectorbyangle(Vector2 v, double angle);
#endif
