#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "image.h"
#include "game.h"
#include "timeutils.h"
#include "mathutils.h"
#include "circle.h"
#include "image.h"

#define ADDER_SPEED_PER_SECOND TILE_WIDTH * 12.0
#define MAX_SPEED_PER_SECOND TILE_WIDTH * 12.0
#define GRAVITY_PER_SECOND TILE_HEIGHT * 25.0
#define JUMP_SECONDS 0.4
#define SMOOTH_FACTOR 2.4
#define SPEED_DECREASING_FACTOR 0.995
#define SPEED_DECREASING_DELTA 1000000
#define MIN_SPEED 8.0

#define RECT_WIDTH TILE_WIDTH - (TILE_WIDTH / 4)
#define RECT_HEIGHT TILE_HEIGHT - (TILE_HEIGHT / 4)

#define WALL_HEX 0x000000
#define PLAYER_HEX 0x0026FF
#define COIN_HEX 0xFFD800
#define HIDEN_COIN_HEX 0xFF6A00
#define HIDEN_COIN_TILE 3
#define COIN_TILE 2
#define WALL_TILE 1
#define SKY_TILE 0

#define KEYBOARD_SIZE 256

#define TILE_WIDTH 40
#define TILE_HEIGHT 40

typedef struct
{
    long long x, y;
    long double xRest, yRest;
    long double dx, lastDx;
    long long restDecreasingX;
    bool isFalling;
    struct timespec fall;
} Man;

typedef struct
{
    int width;
    int height;
    uchar* tiles;
    int totalCoins;
    int numCoins;
} World;

typedef struct
{
    Man man;
    World world;

    struct timespec now;
    struct timespec lastUpdate;
    bool isFirstUpdate;
    bool keyboard[KEYBOARD_SIZE];
    bool pressed[KEYBOARD_SIZE];

    Image label;
    int labeledCoins;
    int labelIntersectCount;
    bool showedHidenCoins;
    TTF_Font *font;
} GameState;

int loadGame(GameState *game);

int loadAssets(GameState *game, SDL_Renderer *renderer);

bool processEvents(SDL_Window *window, GameState *game);

void doUpdate(GameState *game);

void doRender(SDL_Renderer *renderer, GameState *game);

void destroyGame(GameState *game);

#endif // GAME_H_INCLUDED
