#include "../include/overlay.h"

void showseconds(double seconds)
{
    char msstr[30];
    sprintf(msstr, "masodpercek: %lf", seconds);
    rendertext((Point){WINDOWWIDTH - 200, 10}, (SDL_Color){255, 255, 255, 255}, msstr);
}

void showcooldowns(bool flashoncd)
{
    int pady = 20, padx = 10;
    SDL_Color flashc = {0, 200, 0, 255};
    if (flashoncd)
    {
        flashc = (SDL_Color){200, 0, 0, 255};
    }
    renderbox((Point){.x = WINDOWWIDTH / 2 - padx, .y = WINDOWHEIGHT - pady},
              (Point){.x = WINDOWWIDTH / 2 + padx, .y = WINDOWHEIGHT + pady},
              flashc);
}