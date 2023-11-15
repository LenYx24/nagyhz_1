#include "../include/overlay.h"

void showseconds(double seconds)
{
    char msstr[30];
    sprintf(msstr, "masodpercek: %lf", seconds);
    rendertext((Point){WINDOWWIDTH - 200, 10}, (SDL_Color){255, 255, 255, 255}, msstr);
}
void showcooldowns(Player *player)
{
    SDL_Color green = {0, 200, 0, 255};
    SDL_Color red = {200, 0, 0, 255};
    SDL_Color white = {0, 0, 0, 255};

    SDL_Color flashcolor = green;
    SDL_Color missilecolor = green;

    if (player->flash.props.oncd)
        flashcolor = red;
    if (player->missileprops.oncd)
        missilecolor = red;

    int padbottom = 20, padx = 10, rectyoffest = 5;
    int halfwindowwidth = WINDOWWIDTH / 2;

    int textlength = 20;
    int rectlength = 30;
    int fullwidth = 2 * textlength + 2 * rectlength;

    Point startp = {halfwindowwidth - (fullwidth / 2), WINDOWHEIGHT - padbottom - rectyoffest};
    Point rectdownright = {startp.x + rectlength, WINDOWHEIGHT - padbottom + rectyoffest};

    rendertext(startp, white, "Q:");
    startp.x += textlength + padx;
    rectdownright.x += textlength + padx;

    renderbox(startp, rectdownright, missilecolor);
    startp.x += rectlength + padx;
    rectdownright.x += textlength + padx;

    rendertext(startp, white, "D:");
    startp.x += textlength + padx;
    rectdownright.x += textlength + padx;

    renderbox(startp, rectdownright, flashcolor);
}