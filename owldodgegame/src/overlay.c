#include "../include/overlay.h"

void showseconds(double seconds) {
  char msstr[30];
  sprintf(msstr, "tizedmasodpercek: %.2lf", seconds);
  rendertext((Point){WINDOWWIDTH - 250, 10}, c_white, msstr);
}
void showpoints() {
  char str[30];
  sprintf(str, "pontok: %.2lf", getcurrentpoint());
  rendertext((Point){WINDOWWIDTH - 200, 40}, c_white, str);
}
void showcooldowns(Player *player) {

  SDL_Color flashcolor = c_green;
  SDL_Color missilecolor = c_green;

  if (player->flash.oncd)
    flashcolor = c_red;
  if (player->missileprops.oncd)
    missilecolor = c_red;

  int padbottom = 20, padx = 10, rectyoffest = 5;
  int halfwindowwidth = WINDOWWIDTH / 2;

  int textlength = 20;
  int rectlength = 20;
  int fullwidth = 2 * textlength + 2 * rectlength;

  Point startp = {halfwindowwidth - (fullwidth / 2.0f),
                  WINDOWHEIGHT - padbottom - rectyoffest};
  Point rectdownright = {startp.x + rectlength,
                         WINDOWHEIGHT - padbottom + rectyoffest};

  rendertext(startp, c_white, "Q:");
  startp.x += textlength + padx;
  rectdownright.x += textlength + padx;

  renderbox(startp, rectdownright, missilecolor);
  startp.x += rectlength + padx;
  rectdownright.x += rectlength + padx;

  rendertext(startp, c_white, "D:");
  startp.x += textlength + padx;
  rectdownright.x += textlength + padx;

  renderbox(startp, rectdownright, flashcolor);
}