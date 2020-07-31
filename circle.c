#include <math.h>
#include <stdio.h>
#include "circle.h"
#include "mathutils.h"
#include <math.h>

int SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int size)
{
    double fSize = size;
    double halfSize = (fSize - 1.0) / 2.0;
    double ss = halfSize * halfSize;
    double xFactor, xMinusHalfSize, yMinusHalfSize;
    SDL_Rect rect = {0, 0, 1, 0};
    int xx, yy;

    for(xx = 0; xx < size; xx++)
    {
        rect.x = x + xx;
        xMinusHalfSize = xx - halfSize;
        xFactor = xMinusHalfSize * xMinusHalfSize;
        for(yy = 0; yy < size; yy++)
        {
            yMinusHalfSize = yy - halfSize;
            if(xFactor+yMinusHalfSize*yMinusHalfSize > ss - halfSize && xFactor+yMinusHalfSize*yMinusHalfSize < ss + halfSize)
            {
                rect.y = y + yy;
                rect.h = size - (yy << 1);
                SDL_RenderFillRect(renderer, &rect);
                break;
            }
        }
    }
    return 0;
}

int SDL_RenderFillOval(SDL_Renderer *renderer, int x, int y, int width, int height)
{
    SDL_Rect rect = {0, 0, 1, 0};
    double fHeight = height, fWidth = width;
    double halfWidth = (fWidth - 1.0) / 2.0, halfHeight = (fHeight - 1.0) / 2.0;
    double hh = halfHeight * halfHeight;
    double ww = halfWidth * halfWidth;
    double xFactor, xMinusHalfWidth, yMinusHalfHeight;
    int xx, yy;

    for (xx = 0; xx < width; xx++) {
        rect.x = x + xx;
        xMinusHalfWidth = xx - halfWidth;
        xFactor = xMinusHalfWidth * xMinusHalfWidth * hh;
        for (yy = 0; yy < height; yy++) {
            yMinusHalfHeight = yy - halfHeight;
            if (xFactor + yMinusHalfHeight * yMinusHalfHeight
                    * ww > (hh - halfHeight) * (ww - halfWidth) && xFactor + yMinusHalfHeight * yMinusHalfHeight
                    * ww < (hh + halfHeight) * (ww + halfWidth)) {
                rect.y = y + yy;
                rect.h = height - (yy << 1);
                SDL_RenderFillRect(renderer, &rect);
                break;
            }
        }
    }
    return 0;
}
