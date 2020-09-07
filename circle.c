#include <math.h>
#include <stdio.h>
#include "circle.h"
#include "mathutils.h"
#include <math.h>

int SDL_RenderFillOval(SDL_Renderer *renderer, int32_t x, int32_t y, int32_t width, int32_t height, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float blur)
{
    uint32_t halfWidth = width >> 1, halfHeight = height >> 1;
    uint64_t ww = halfWidth * halfWidth;
    uint64_t hh = halfHeight * halfHeight;
    uint64_t hhww = hh * ww;
    uint64_t normHhww = (hhww - (hhww * blur)) + 0.5;
    uint64_t xFactor;
    uint32_t xx, yy;
    uint64_t val;
    int32_t draw_x1, draw_x2, draw_y1, draw_y2;
    SDL_Rect rect;
    Uint8 curA = a, lastA = a;

    if(width & 1)
    {
        rect.x = halfWidth;
        rect.y = 0;
        rect.w = 1;
        rect.h = height;
        SDL_RenderFillRect(renderer, &rect);
    }
    if(height & 1)
    {
        rect.y = halfHeight;
        rect.x = 0;
        rect.w = width;
        rect.h = 1;
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_SetRenderDrawColor(renderer, r, g, b, curA);

    for (xx = 0; xx < halfWidth; xx++) {
        draw_x1 = x + (halfWidth - 1 - xx);
        draw_x2 = x + width - 1 - (halfWidth - 1 - xx);
        xFactor = xx * xx * hh;
        for (yy = 0; yy < halfHeight; yy++) {
            val = xFactor + yy * yy * ww;
            if (val <= hhww) {
                draw_y1 = y + (halfHeight - 1 - yy);
                draw_y2 = y + height - 1 - (halfHeight - 1 - yy);
                if(val <= normHhww)
                {
                    curA = a;
                }
                else
                {
                    curA = ((float) (hhww - val) / (float) (hhww - normHhww)) * a + 0.5;
                }
                if(curA != lastA)
                {
                    lastA = curA;
                    SDL_SetRenderDrawColor(renderer, r, g, b, curA);
                }
                SDL_RenderDrawPoint(renderer, draw_x1, draw_y1);
                SDL_RenderDrawPoint(renderer, draw_x1, draw_y2);
                SDL_RenderDrawPoint(renderer, draw_x2, draw_y1);
                SDL_RenderDrawPoint(renderer, draw_x2, draw_y2);
            }
        }
    }
    return 0;
}
