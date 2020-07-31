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

void doRenderImage(SDL_Renderer *renderer, const Image *image, int x, int y);

typedef uint32_t (*getpixelfunc)(uint8_t* p);

uint32_t getpixelbpp0(uint8_t* p);
uint32_t getpixelbpp1(uint8_t* p);
uint32_t getpixelbpp2(uint8_t* p);
uint32_t getpixelbpp3bigendian(uint8_t* p);
uint32_t getpixelbpp3notbigendian(uint8_t* p);
uint32_t getpixelbpp4(uint8_t* p);

getpixelfunc getpixelfuncfactory(int bpp);

#endif // IMAGE_H_INCLUDED
