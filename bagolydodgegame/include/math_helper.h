#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>

#include "macros.h"

typedef struct Point
{
  double x, y;
} Point;
typedef struct Vector2
{
  double x, y;
} Vector2;
typedef struct Size
{
  int width, height;
} Size;
typedef struct Rect
{
  Point pos;
  Size size;
} Rect;
Point substract(Point p1, Point p2);
bool withinbounds(Rect r, Point p);
Point randomspawnpoint();
#endif