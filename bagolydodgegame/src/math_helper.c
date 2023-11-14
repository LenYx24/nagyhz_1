#include "../include/math_helper.h"

Point substract(Point p1, Point p2)
{
  Point result = {p2.x - p1.x, p2.y - p1.y};
  return result;
}
bool withinbounds(Rect r, Point p)
{
  int left = r.pos.x;
  int right = left + r.size.width;
  int top = r.pos.y;
  int bottom = top + r.size.height;
  return (left <= p.x && p.x <= right) && (top <= p.y && p.y <= bottom);
}

Point randomspawnpoint()
{
  Point p;
  if (rand() % 2)
  { // bal vagy jobb oldalt
    p.y = rand() % WINDOWHEIGHT;
    if (rand() % 2)
      p.x = 0; // bal
    else
      p.x = WINDOWWIDTH; // jobb
  }
  else
  { // fent vagy lent
    p.x = rand() % WINDOWWIDTH;
    if (rand() % 2)
      p.y = 0; // fent
    else
      p.y = WINDOWHEIGHT; // lent
  }
  return p;
}

int twopointsdistance(Point p1, Point p2)
{
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
Vector2 vectorfromtwopoints(Point start, Point end)
{
  return (Vector2){.x = end.x - start.x, .y = end.y - start.y};
}
Point gettopleftpoint(Point pos, Size size)
{
  return (Point){pos.x - size.width / 2, pos.y - size.height / 2};
}
Point addvectortopoint(Point p, Vector2 v)
{
  return (Point){.x = p.x + v.x, .y = p.y + v.y};
}
Vector2 normalizevector(Vector2 v)
{
  int distance = sqrt(pow(v.x, 2) + pow(v.y, 2));
  return (Vector2){.x = v.x / distance, .y = v.y / distance};
}