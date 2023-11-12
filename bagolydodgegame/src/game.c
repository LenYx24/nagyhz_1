#include "../include/game.h"

Uint32 update(Uint32 ms, void *param) {
  createuserevent();
  return ms;
}
void game(Event *e, State *state) {
  Player player = {.point = {960, 540},
                   .size = {100, 100},
                   .texture = loadimage("resources/infocbagoly.png")};
  Timer timer = createtimer(10, update);
  Texture bg = loadimage("resources/map.png");
  Rect dest = {(Point){0, 0}, (Size){1280, 960}};
  renderimage(&bg, &dest);
  bool game = true;
  while (game) {
    if (e->event != NULL) {
      switch (e->event->type) {
      case SDL_MOUSEBUTTONDOWN:
        //   if (event.button.button == SDL_BUTTON_RIGHT) {
        //     player.dest.x = event.button.x;
        //     player.dest.y = event.button.y;
        //     circleRGBA(renderer, event.button.x, event.button.y, 3, 0, 0,
        //     200, 255);
        //   }
        // a felhasználónak jelezni hogy kattintott
        renderupdate();
        break;

      case SDL_USEREVENT:
        renderimage(&bg, NULL);
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
        Rect dest = {(Point){player.point.x - (player.size.width / 2.0),
                             player.point.y - (player.size.width / 2.0)},
                     (Size){player.size.width, player.size.width}};
        renderimage(&player.texture, &dest);
        renderupdate();
        break;
      case SDL_QUIT:
        *state = QUIT;
        break;
      }
    }
    removetimer(&timer);
    destroytexture(&bg);
  }
}