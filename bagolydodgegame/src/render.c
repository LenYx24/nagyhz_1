#include "../include/render.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void createwindow(Size windowsize, char *title) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
    exit(1);
  }
  SDL_Window *w =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       windowsize.width, windowsize.height, 0);
  if (w == NULL) {
    SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
    exit(1);
  }
  SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_SOFTWARE);
  if (r == NULL) {
    SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
    exit(1);
  }
  SDL_RenderClear(r);
  window = w;
  renderer = r;
}
void rendererquit() { SDL_Quit(); }

Texture loadimage(char *pathname) {
  Texture t1;
  SDL_Texture *img = IMG_LoadTexture(renderer, pathname);
  if (img == NULL) {
    SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
    exit(1);
  }
  t1.t = img;
  return t1;
}
void renderimage(Texture *t, Rect *dest) {
  SDL_Rect r = {dest->pos.x, dest->pos.y, dest->size.width, dest->size.height};
  SDL_RenderCopy(renderer, t->t, NULL, &r);
}
void destroytexture(Texture *t) { SDL_DestroyTexture(t->t); }
void renderbox(Point topleft, Point downright, Color color) {
  boxRGBA(renderer, topleft.x, topleft.y, downright.x, downright.y, color.R,
          color.G, color.B, color.A);
}

void rendertext(Point pos, Color color, char *text) {
  stringRGBA(renderer, pos.x, pos.y, text, color.R, color.G, color.B, color.A);
}

void waitevent(Event *e) { SDL_WaitEvent(e->event); }

void renderupdate() { SDL_RenderPresent(renderer); }

Timer createtimer(Uint32 ms, void *callback) {
  Timer t;
  t.id = SDL_AddTimer(ms, callback, NULL);
  return t;
}
void removetimer(Timer *t) { SDL_RemoveTimer(t->id); }

void createuserevent() {
  SDL_Event ev;
  ev.type = SDL_USEREVENT;
  SDL_PushEvent(&ev);
}