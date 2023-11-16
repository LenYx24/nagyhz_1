#ifndef MATH_HELPER_H
#define MATH_HELPER_H
#define PI 3.1416

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include <math.h>
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

Point randomspawnpoint();
Point substracttwopoints(Point p1, Point p2);
Point gettopleftpoint(Point pos, Size size);
Point addvectortopoint(Point p, Vector2 v);
Point rectdownrightpoint(Rect rect);

Vector2 vectorfromtwopoints(Point start, Point end);
Vector2 normalizevector(Vector2 v);

bool withinbounds(Rect r, Point p);
bool outofscreen(Point pos, Size size);

int twopointsdistance(Point p1, Point p2);
int vectorlength(Vector2 v);

double getangle(Vector2 v);

#endif