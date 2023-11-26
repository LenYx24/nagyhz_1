#ifndef OVERLAY_H
#define OVERLAY_H
/*
 * @file overlay.h
 * @brief A játéknézetben megjelenő felhasználói felület, a játékélményt
 * elősegítő jelzők és szövegek megjelenítéséért felelős modul
 *
 */
#include <stdbool.h>
#include <string.h>

#include "entity.h"
#include "macros.h"
#include "math_helper.h"
#include "render.h"
#include "scoreboard.h"
#include "state.h"
/**
 * @brief A jobb felső sarokban mutatja egy valós típusú változóban az eltelt
 * másodperceket
 *
 * @param seconds A kör kezdete óta eltelt másodpercek
 */
void showseconds(double seconds);
/**
 * @brief Kimutatja a jelenlegi körben elért pontok számát a jobb felső
 * sarokban, a másodpercszámláló alatt
 *
 */
void showpoints();
/**
 * @brief A játékos két képességéhez tartozó töltési időt mutatja két kis
 * négyzetben Ha zöld a négyzet, akkor használható a képesség, ha piros, akkor
 * még nem
 * @param player a játékosra mutató pointer
 */
void showcooldowns(Player *player);
#endif