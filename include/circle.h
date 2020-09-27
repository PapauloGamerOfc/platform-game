#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED
#include "SDL.h"
#include <stdint.h>

int SDL_RenderFillOval(SDL_Renderer *renderer, int32_t x, int32_t y, int32_t width, int32_t height, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float blur);

#endif // CIRCLE_H_INCLUDED
