#ifndef RENDER_H
#define RENDER_H
/*
 * @file render.h
 * @brief A megjelenítéssel foglalkozó modul
 * Ez a modul kommunikál az sdl külső könyvtárral, és rajzoltatja ki a
 * textúrákat, illetve különböző alakzatokat, vagy ír ki szöveget a képernyőre.
 * Az SDL_Color struktúrát használva a többi modulnak elérhetővé tesz különböző
 * színeket. Ezek a színek mind c_ prefixxel rendelkeznek
 */
#include "math_helper.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

extern SDL_Color c_white;
extern SDL_Color c_green;
extern SDL_Color c_red;
extern SDL_Color c_btselected;
extern SDL_Color c_btbgcolor;
/**
 * @brief Inicializálja az ablakot és a megjelenítőt.
 * Ha hibába ütközik, akkor kiírja a konzolra és kilép a program.
 * Az infoc oldalról származik a kódrészlet
 * @param windowsize Ekkora méretű lesz a létrehozott ablak
 * @param title Ez lesz az ablak fejlécére írva
 */
void createwindow(Size windowsize, char *title);
/**
 * @brief Betölti az adott betűtípust
 *
 * @param pathname a betűtípushoz vezető útvonal
 * @param size a betűtípus mérete
 */
void initfont(char *fonttype, int size);
/**
 * @brief Betölti egy texturúba a képet
 * Ha nem sikerült betölteni a képet akkor kiírja a hibát a konzolra és
 * bezáródik a program
 * @param pathname Ezen az útvonalon lévő képet tölti be
 * @return SDL_Texture* A betöltött texturára mutató pointer adja vissza értékül
 */
SDL_Texture *loadimage(char *pathname);

/**
 * @brief Egy dobozt jelenít meg a kijelzőn
 *
 * @param topleft A doboz bal felső sarkának koordinátája
 * @param downright A doboz jobb alsó sarkának koordinátája
 * @param color A doboz belsejének a színe
 */
void renderbox(Point topleft, Point downright, SDL_Color color);
/**
 * @brief Egy téglalapban texturát jelenít meg a kijelzőn
 *
 * @param t A textúra
 * @param dest A téglalap
 */
void renderrectangle(SDL_Texture *t, Rect dest);
/**
 * @brief Egy téglalapban texturát jelenít meg a kijelzőn, de az x tengelytől
 * óramutató járásával megegyező irányban adott szöggel
 *
 * @param t A textúra
 * @param dest A téglalap
 * @param rotation Az adott szög
 */
void renderrectanglerotated(SDL_Texture *t, Rect dest, double rotation);
/**
 * @brief Egy adott pozícióba adott színű szöveget ír ki
 *
 * @param pos A szöveg pozíciója
 * @param color A szöveg színe
 * @param text Maga a kiírandó szöveg
 */
void rendertext(Point pos, SDL_Color color, char *text);
/**
 * @brief Kirajzol egy kört a kijelzőre
 *
 * @param p A kör középpontja
 * @param radius A kör sugara
 * @param c A kör körvonalának színe
 */
void rendercircle(Point p, int radius, SDL_Color c);
/**
 * @brief Frissíti a kijelző jelenlegi állását
 *
 */
void renderupdate();

/** Beolvas egy szoveget a billentyuzetrol.
 * A rajzolashoz hasznalt font es a megjelenito az utolso parameterek.
 * Az elso a tomb, ahova a beolvasott szoveg kerul.
 * A masodik a maximális hossz, ami beolvasható.
 * A visszateresi erteke logikai igaz, ha sikerult a beolvasas.
 * az infoc oldalról származik a kódrészlet
 * @param dest A szöveg ahova másolja majd az értéket
 * @param size A szöveg mérete
 * @param rect A mező(téglalap) mérete
 * @param bgcolor A mező háttérszíne
 * @param textcolor A mező szövegének színe
 * @return boolean ha enter miatt tér vissza a függvény akkor igazzal, ha nem
 * emiatt akkor hamissal tér vissza
 */
bool input_text(char *dest, size_t size, SDL_Rect rect, SDL_Color bgcolor,
                SDL_Color textcolor);
#endif