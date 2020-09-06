#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED
#include "SDL.h"
#include <stdint.h>

int SDL_RenderFillCircle(SDL_Renderer *renderer, int32_t x, int32_t y, int32_t size);

int SDL_RenderFillOval(SDL_Renderer *renderer, int32_t x, int32_t y, int32_t width, int32_t height);

#endif // CIRCLE_H_INCLUDED
