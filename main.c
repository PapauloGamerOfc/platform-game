#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "SDL.h"
#include "SDL_image.h"
#define SDL_MAIN_HANDLED
#include "game.h"
#include "types.h"
#include "mathutils.h"
#include "image.h"
#include "windpi.h"

int main(int argc, char*argv[])
{
    GameState game;
    SDL_Window *window;
    SDL_Renderer *renderer;

    int running = 1;
    int exit = 0;
    int width, height;
    int loadResult;

    windpi_setaware();
    TTF_Init();

    loadResult = loadGame(&game);
    if(loadResult != 0)
    {
        running = 0;
        exit = loadResult;
    }

    width = game.world.width * TILE_WIDTH;
    height = game.world.height * TILE_HEIGHT;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Window Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    loadResult = loadAssets(&game, renderer);
    if(loadResult != 0)
    {
        running = 0;
        exit = loadResult;
    }

    while(running)
    {
        running = processEvents(window, &game);

        doUpdate(&game);
        doRender(renderer, &game);

        game.lastUpdate = game.now;

        SDL_Delay(1);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    destroyGame(&game);

    TTF_Quit();
    SDL_Quit();

    return exit;
}