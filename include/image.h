#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "SDL_image.h"
#include "SDL_TTF.h"
#include "types.h"

typedef struct
{
    SDL_Texture* texture;
    int w, h;
} Image;

int loadImageFont(SDL_Renderer *renderer, TTF_Font *font, const char *text, uchar a, uchar r, uchar g, uchar b, Image *dest);

int loadImageFile(SDL_Renderer *renderer, const char *file, Image *dest);

int loadImageSurface(SDL_Renderer *renderer, SDL_Surface *source, Image *dest);

void destroyImage(Image* image);

void doRenderImage(SDL_Renderer *renderer, const Image *image, int32_t x, int32_t y);

typedef uint32_t (*getpixelfunc)(uint8_t* p);

getpixelfunc getpixelfuncfactory(int32_t bpp);

#endif // IMAGE_H_INCLUDED
