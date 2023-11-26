#ifndef OVERLAY_H
#define OVERLAY_H
#include <string.h>
#include <stdbool.h>

#include "math_helper.h"
#include "state.h"
#include "render.h"
#include "entity.h"
#include "scoreboard.h"

void showseconds(double seconds);
void showcooldowns(Player *player);
void showpoints();
#endif