#include "../include/render.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

void createwindow(Size windowsize, char *title)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
    exit(1);
  }
  window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       windowsize.width, windowsize.height, 0);
  if (window == NULL)
  {
    SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
    exit(1);
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (renderer == NULL)
  {
    SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
    exit(1);
  }
  SDL_RenderClear(renderer);
  printf("w: %p\n", &window);
  printf("r: %p\n", &renderer);
}
void rendererquit() { SDL_Quit(); }

SDL_Texture *loadimage(char *pathname)
{
  SDL_Texture *img = IMG_LoadTexture(renderer, pathname);
  if (img == NULL)
  {
    SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
    exit(1);
  }
  return img;
}
void renderimage(SDL_Texture *t, Rect *dest)
{
  SDL_Rect r = {dest->pos.x, dest->pos.y, dest->size.width, dest->size.height};
  SDL_RenderCopy(renderer, t, NULL, &r);
}
void destroytexture(SDL_Texture *t) { SDL_DestroyTexture(t); }
void renderbox(Point topleft, Point downright, SDL_Color color)
{
  boxRGBA(renderer, topleft.x, topleft.y, downright.x, downright.y, color.r,
          color.g, color.b, color.a);
}

void rendertext(Point pos, SDL_Color color, char *text)
{
  stringRGBA(renderer, pos.x, pos.y, text, color.r, color.g, color.b, color.a);
}

void renderupdate() { SDL_RenderPresent(renderer); }

void createuserevent()
{
  SDL_Event ev;
  ev.type = SDL_USEREVENT;
  SDL_PushEvent(&ev);
}