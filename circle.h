#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED
#include "SDL.h"

int SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int size);

int SDL_RenderFillOval(SDL_Renderer *renderer, int x, int y, int width, int height);

#endif // CIRCLE_H_INCLUDED
