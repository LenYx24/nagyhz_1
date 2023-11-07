#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <math.h>
#include <stdbool.h>

#include "../include/init.h"
#include "../include/math_helper.h"
#include "../include/entity.h"
#include "../include/render.h"

Uint32 idozit(Uint32 ms, void *param) {
  SDL_Event ev;
  ev.type = SDL_USEREVENT;
  SDL_PushEvent(&ev);
  return ms;
}
int main(int argc, char *argv[]) {
  Player player = {.point = {960, 540}, .size = {100, 100}};
  Size wsize = {1280,960};
  init(wsize,"bagoly jatek");

  Texture bg = loadimage("resources/map.png");
  Texture bagoly = loadimage("resources/infocbagoly.png");
  Rect dest = {(Point){0,0},(Size){1280,960}};
  renderimage(bg,dest);

  bool quit = false, ismenu = true;
  while (!quit) {
    if (ismenu) {
      renderimage(bg,NULL);
      renderbox((Point){20,20},(Point){200,50},(Color){200,0,0,255});
      rendertext((Point){100,30},(Color){255,255,255,255},"Start");
      renderupdate();
      SDL_Event event;
      SDL_WaitEvent(&event);
      switch (event.type) {
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
          Point mousepos ={event.button.x, event.button.y};
          Rect bt1 = {(Point){20,20},(Size){120,70}};
          if (withinbounds(bt1,mousepos)) {
            ismenu = false;
            renderimage(bg,NULL);
          }
        }
        break;
      case SDL_QUIT:
        quit = true;
        break;
      }
    } else {
      SDL_TimerID id = SDL_AddTimer(10, idozit, NULL);
      bool game = true;
      while (game) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_RIGHT) {
            player.dest.x = event.button.x;
            player.dest.y = event.button.y;
            circleRGBA(renderer, event.button.x, event.button.y, 3, 0, 0, 200,
                       255);
          }
          renderupdate();
          break;

        case SDL_USEREVENT:
          SDL_RenderCopy(renderer, bg, NULL, &dest); // reset
          // játékos mozgatása vector irányba
          Point dest_pos_v = substract(player.point, player.dest);
          int p1 = pow(player.point.x - player.dest.x, 2);
          int p2 = pow(player.point.y - player.dest.y, 2);
          double r = sqrt(p1 + p2);
          int speed = 2;
          if (r > speed) {
            player.point.x += speed * dest_pos_v.x / r;
            player.point.y += speed * dest_pos_v.y / r;
          }
          Rect dest = {player.point.x - (player.size.width / 2.0),
                           player.point.y - (player.size.width / 2.0),
                           player.size.width, player.size.width};
          renderimage(bagoly, dest);
          renderupdate();
          break;
        case SDL_QUIT:
          game = false;
          quit = true;
          break;
        }
      }
      SDL_RemoveTimer(id);
    }
  }
  destroytexture(bg);

  SDL_Quit();
  return 0;
}
