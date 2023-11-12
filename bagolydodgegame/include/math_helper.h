#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct Point
{
  double x, y;
} Point;
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
// megnézi, hogy az adott téglalapban benne van-e a pont
bool withinbounds(Rect r, Point p);
#endif