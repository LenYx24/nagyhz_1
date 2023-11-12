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