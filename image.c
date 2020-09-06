#include "image.h"

int loadImageFont(SDL_Renderer *renderer, TTF_Font *font, const char *text, uchar a, uchar r, uchar g, uchar b, Image *dest)
{
    SDL_Color color;
    color.a = a;
    color.r = r;
    color.g = g;
    color.b = b;
    return loadImageSurface(renderer, TTF_RenderText_Blended(font, text, color), dest);
}

int loadImageFile(SDL_Renderer *renderer, const char *file, Image *dest)
{
    return loadImageSurface(renderer, IMG_Load(file), dest);
}

int loadImageSurface(SDL_Renderer *renderer, SDL_Surface *source, Image *dest)
{
    if(source == NULL)
    {
        return -1;
    }

    dest->w = source->w;
    dest->h = source->h;
    dest->texture = SDL_CreateTextureFromSurface(renderer, source);
    SDL_FreeSurface(source);

    return 0;
}

void destroyImage(Image *image)
{
    if(image->texture != NULL)
    {
        SDL_DestroyTexture(image->texture);
    }
}

void doRenderImage(SDL_Renderer *renderer, const Image *image, int32_t x, int32_t y)
{
    SDL_Rect rect = {x, y, image->w, image->h};
    SDL_RenderCopy(renderer, image->texture, NULL, &rect);
}

uint32_t getpixelbpp0(uint8_t* p)
{
    return 0;
}

uint32_t getpixelbpp1(uint8_t* p)
{
    return *p;
}

uint32_t getpixelbpp2(uint8_t* p)
{
    return *(Uint16 *)p;
}

uint32_t getpixelbpp3bigendian(uint8_t* p)
{
    return p[0] << 16 | p[1] << 8 | p[2];
}

uint32_t getpixelbpp3notbigendian(uint8_t* p)
{
    return p[0] | p[1] << 8 | p[2] << 16;
}

uint32_t getpixelbpp4(uint8_t* p)
{
    return *(Uint32 *)p;
}

getpixelfunc getpixelfuncfactory(int bpp)
{
    switch(bpp)
    {
        case 1:
            return &getpixelbpp1;
            break;
        case 2:
            return &getpixelbpp2;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return getpixelbpp3bigendian;
            else
                return getpixelbpp3notbigendian;
        case 4:
            return getpixelbpp4;
            break;
        default:
            return getpixelbpp0;
            break;
    }
}
