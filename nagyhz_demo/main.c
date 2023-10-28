#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_render.h>
#include <math.h>
#include <stdbool.h>

typedef struct Point {
  double x, y;
} Point;
typedef struct Size {
  int width, height;
} Size;

struct Entity {
  Point point;
  Point dest;
  Size size;
};
typedef struct Entity Fireball;
typedef struct Entity Player;
Player player = {.point = {960, 540}, .size = {20, 20}};
/* ablak megnyitasa */
void sdl_init(int szeles, int magas, SDL_Window **pwindow,
              SDL_Renderer **prenderer) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
    exit(1);
  }
  SDL_Window *window =
      SDL_CreateWindow("SDL peldaprogram", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
  if (window == NULL) {
    SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
    exit(1);
  }
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (renderer == NULL) {
    SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
    exit(1);
  }
  SDL_RenderClear(renderer);

  *pwindow = window;
  *prenderer = renderer;
}
Uint32 idozit(Uint32 ms, void *param) {
  SDL_Event ev;
  ev.type = SDL_USEREVENT;
  SDL_PushEvent(&ev);
  return ms; /* ujabb varakozas */
}
Point substract(Point p1, Point p2) {
  Point result = {p2.x - p1.x, p2.y - p1.y};
  return result;
}
int main() {
  SDL_Window *window;
  SDL_Renderer *renderer;
  sdl_init(1920, 1080, &window, &renderer);
  boxRGBA(renderer, 0, 0, 1920, 1080, 0, 100, 0, 255);
  SDL_RenderPresent(renderer);

  SDL_TimerID id = SDL_AddTimer(20, idozit, NULL);
  bool game = true;
  while (game) {
    SDL_Event event;
    SDL_WaitEvent(&event);
    switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:
      if (event.button.button == SDL_BUTTON_RIGHT) {
        player.dest.x = event.button.x;
        player.dest.y = event.button.y;
      }
      break;

    case SDL_USEREVENT:
      filledCircleRGBA(renderer, player.point.x, player.point.y,
                       player.size.width, 0, 100, 0, 255); // torles
      // játékos mozgatása vector irányba
      Point dest_pos_v = substract(player.point, player.dest);
      int p1 = pow(player.point.x - player.dest.x, 2);
      int p2 = pow(player.point.y - player.dest.y, 2);
      double r = sqrt(p1 + p2);
      if (r > 1) {
        player.point.x += 2 * dest_pos_v.x / r;
        player.point.y += 2 * dest_pos_v.y / r;
      }
      filledCircleRGBA(renderer, player.point.x, player.point.y,
                       player.size.width, 100, 100, 255, 255);
      break;
    case SDL_QUIT:
      game = false;
      break;
    }
    SDL_RenderPresent(renderer);
  }
  SDL_RemoveTimer(id);

  SDL_Quit();
  return 0;
}
