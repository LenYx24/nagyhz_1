#include "../include/render.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static TTF_Font *font = NULL;

SDL_Color c_white = {255, 255, 255, 255};
SDL_Color c_green = {0, 200, 0, 255};
SDL_Color c_red = {200, 0, 0, 255};
SDL_Color c_menubg = {20, 20, 20, 255};
SDL_Color c_btbg = {200, 0, 0, 255};
SDL_Color c_btbghover = {50, 0, 0, 255};
SDL_Color c_btselected = {130, 20, 20, 255};

void createwindow(Size windowsize, char *title) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
    exit(1);
  }
  window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       windowsize.width, windowsize.height, 0);
  if (window == NULL) {
    SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
    exit(1);
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (renderer == NULL) {
    SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
    exit(1);
  }
  SDL_RenderClear(renderer);
}
void initfont(char *pathname, int size) {
  TTF_Init();
  font = TTF_OpenFont(pathname, size);
  if (font == NULL) {
    SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
    exit(1);
  }
}
void closefont() { TTF_CloseFont(font); }

SDL_Texture *loadimage(char *pathname) {
  SDL_Texture *img = IMG_LoadTexture(renderer, pathname);
  if (img == NULL) {
    SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
    exit(1);
  }
  return img;
}
void renderbox(Point topleft, Point downright, SDL_Color color) {
  boxRGBA(renderer, topleft.x, topleft.y, downright.x, downright.y, color.r,
          color.g, color.b, color.a);
}
void renderrectangle(SDL_Texture *t, Rect dest) {
  SDL_Rect r = {dest.pos.x, dest.pos.y, dest.size.width, dest.size.height};
  SDL_RenderCopy(renderer, t, NULL, &r);
}

void renderrectanglerotated(SDL_Texture *t, Rect dest, double angle) {
  SDL_Rect r = {dest.pos.x, dest.pos.y, dest.size.width, dest.size.height};
  SDL_RenderCopyEx(renderer, t, NULL, &r, angle, NULL, SDL_FLIP_NONE);
}

void rendertext(Point pos, SDL_Color color, char *text) {
  stringRGBA(renderer, pos.x, pos.y, text, color.r, color.g, color.b, color.a);
}

void rendercircle(Point p, int radius, SDL_Color c) {
  circleRGBA(renderer, p.x, p.y, radius, c.r, c.g, c.b, c.a);
}
void renderupdate() { SDL_RenderPresent(renderer); }

bool input_text(char *dest, size_t size, SDL_Rect rect, SDL_Color bgcolor,
                SDL_Color textcolor) {
  /* Ez tartalmazza az aktualis szerkesztest */
  char composition[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
  composition[0] = '\0';
  /* Ezt a kirajzolas kozben hasznaljuk */
  char textandcomposition[size + SDL_TEXTEDITINGEVENT_TEXT_SIZE + 1];
  /* Max hasznalhato szelesseg */
  int maxw = rect.w - 2;
  int maxh = rect.h - 2;

  dest[0] = '\0';

  bool enter = false;
  bool kilep = false;

  SDL_StartTextInput();
  while (!kilep && !enter) {
    /* doboz kirajzolasa */
    boxRGBA(renderer, rect.x, rect.y, rect.x + rect.w - 1, rect.y + rect.h - 1,
            bgcolor.r, bgcolor.g, bgcolor.b, 255);
    rectangleRGBA(renderer, rect.x, rect.y, rect.x + rect.w - 1,
                  rect.y + rect.h - 1, textcolor.r, textcolor.g, textcolor.b,
                  255);
    /* szoveg kirajzolasa */
    int w;
    strcpy(textandcomposition, dest);
    strcat(textandcomposition, composition);
    if (textandcomposition[0] != '\0') {
      SDL_Surface *felirat =
          TTF_RenderUTF8_Blended(font, textandcomposition, textcolor);
      SDL_Texture *felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
      SDL_Rect cel = {rect.x, rect.y, felirat->w < maxw ? felirat->w : maxw,
                      felirat->h < maxh ? felirat->h : maxh};
      SDL_RenderCopy(renderer, felirat_t, NULL, &cel);
      SDL_FreeSurface(felirat);
      SDL_DestroyTexture(felirat_t);
      w = cel.w;
    } else {
      w = 0;
    }
    /* kurzor kirajzolasa */
    if (w < maxw) {
      vlineRGBA(renderer, rect.x + w + 2, rect.y + 2, rect.y + rect.h - 3,
                textcolor.r, textcolor.g, textcolor.b, 192);
    }
    /* megjeleniti a képernyon az eddig rajzoltakat */
    SDL_RenderPresent(renderer);

    SDL_Event event;
    SDL_WaitEvent(&event);
    switch (event.type) {
    /* Kulonleges karakter */
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_BACKSPACE) {
        int textlen = strlen(dest);
        do {
          if (textlen == 0) {
            break;
          }
          if ((dest[textlen - 1] & 0x80) == 0x00) {
            /* Egy bajt */
            dest[textlen - 1] = 0x00;
            break;
          }
          if ((dest[textlen - 1] & 0xC0) == 0x80) {
            /* Bajt, egy tobb-bajtos szekvenciabol */
            dest[textlen - 1] = 0x00;
            textlen--;
          }
          if ((dest[textlen - 1] & 0xC0) == 0xC0) {
            /* Egy tobb-bajtos szekvencia elso bajtja */
            dest[textlen - 1] = 0x00;
            break;
          }
        } while (true);
      }
      if (event.key.keysym.sym == SDLK_RETURN) {
        enter = true;
      }
      break;

    /* A feldolgozott szoveg bemenete */
    case SDL_TEXTINPUT:
      if (strlen(dest) + strlen(event.text.text) < size) {
        strcat(dest, event.text.text);
      }

      /* Az eddigi szerkesztes torolheto */
      composition[0] = '\0';
      break;

    /* Szoveg szerkesztese */
    case SDL_TEXTEDITING:
      strcpy(composition, event.edit.text);
      break;

    case SDL_QUIT:
      /* visszatesszuk a sorba ezt az eventet, mert
       * sok mindent nem tudunk vele kezdeni */
      SDL_PushEvent(&event);
      kilep = true;
      break;
    }
  }

  /* igaz jelzi a helyes beolvasast; = ha enter miatt allt meg a ciklus */
  SDL_StopTextInput();
  return enter;
}