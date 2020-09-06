#include "game.h"

int32_t loadGame(GameState *game)
{
    int32_t x, y, i, w, h;
    Man* man = &game->man;
    World* world = &game->world;

    SDL_Surface *mapSurface = NULL;
    SDL_PixelFormat *mapFormat = NULL;
    int32_t rMask, rShift, gMask, gShift, bMask, bShift;
    int32_t bpp;
    uint8_t *p;
    getpixelfunc getpixel = NULL;
    uchar *tiles;

    int32_t pixel, rgb;

    memset(game, 0, sizeof(GameState));

    game->font = TTF_OpenFont("arial.ttf", 40);
    if(game->font == NULL)
    {
        printf("arial.ttf not found!");
        return -1;
    }

    game->isFirstUpdate = 1;

    mapSurface = IMG_Load("map.png");
    if(mapSurface == NULL)
    {
        printf("map.png not found!");
        return -1;
    }
    mapFormat = mapSurface->format;

    rMask = mapFormat->Rmask;
    rShift = mapFormat->Rshift;
    gMask = mapFormat->Gmask;
    gShift = mapFormat->Gshift;
    bMask = mapFormat->Bmask;
    bShift = mapFormat->Bshift;

    bpp = mapFormat->BytesPerPixel;
    getpixel = getpixelfuncfactory(bpp);

    w = mapSurface->w;
    h = mapSurface->h;
    world->width = w;
    world->height = h;

    world->tiles = malloc(w * h);

    bpp = mapFormat->BytesPerPixel;
    getpixel = getpixelfuncfactory(bpp);

    w = mapSurface->w;
    h = mapSurface->h;

    world->width = mapSurface->w;
    world->height = mapSurface->h;
    world->tiles = malloc(w * h);
    tiles = world->tiles;

    for(x = 0; x < w; x++)
    {
        for(y = 0; y < h; y++)
        {
            i = x + y * w;
            p = (uint8_t*)mapSurface->pixels + i * bpp;
            pixel = getpixel(p);
            rgb = (((pixel & rMask) >> rShift) << 16) | (((pixel & gMask) >> gShift) << 8) | ((pixel & bMask) >> bShift);
            tiles[i] = SKY_TILE;
            switch(rgb)
            {
            case COIN_HEX:
                tiles[i] = COIN_TILE;
                world->totalCoins++;
                break;
            case HIDEN_COIN_HEX:
                tiles[i] = HIDEN_COIN_TILE;
                world->totalCoins++;
                break;
            case WALL_HEX:
                tiles[i] = WALL_TILE;
                break;
            case PLAYER_HEX:
                man->x = x * TILE_WIDTH;
                man->y = y * TILE_HEIGHT;
                break;
            }
        }
    }
    SDL_FreeSurface(mapSurface);
    world->numCoins = world->totalCoins;

    return 0;
}

int32_t loadAssets(GameState *game, SDL_Renderer *renderer)
{
    const World* world = &game->world;
    char buf[64];
    game->labeledCoins = world->numCoins;
    sprintf(buf, "Coins: %d/%d", world->totalCoins - world->numCoins, world->totalCoins);
    loadImageFont(renderer, game->font, buf, 255, 255, 255, 255, &game->label);
    return 0;
}

bool processEvents(SDL_Window *window, GameState *game)
{
    SDL_Event event;
    bool running = 1;
    int32_t key;
    bool *keyboard = game->keyboard;
    bool *pressed = game->pressed;
    int32_t width, height;

    memset(pressed, 0, KEYBOARD_SIZE);

    while(running && SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_WINDOWEVENT:
            switch(event.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                running = false;
                break;
            case SDL_WINDOWEVENT_RESIZED:
                SDL_GetWindowSize(window, &width, &height);
                printf("window resized. width: %d, height: %d.\n", width, height);
                break;
            }
            break;
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            key = event.key.keysym.scancode;
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                running = false;
                break;
            }
            if(key >= 0 && key < KEYBOARD_SIZE)
            {
                if(!keyboard[key])
                {
                    keyboard[key] = true;
                    pressed[key] = true;
                }
            }
            break;
        case SDL_KEYUP:
            key = event.key.keysym.scancode;
            if(key >= 0 && key < KEYBOARD_SIZE)
            {
                keyboard[key] = false;
            }
            break;
        }
    }
    return running;
}

int32_t isFree(const World *world, int64_t x, int64_t y, int32_t width, int32_t height)
{
    int64_t endX = x + width - 1;
    int64_t endY = y + height - 1;
    if(x < 0 || y < 0 || endX > world->width * TILE_WIDTH || endY > world->height * TILE_HEIGHT)
    {
        return 0;
    }

    int32_t xMin, xMax, yMin, yMax, curX, curY;
    xMin = x / TILE_WIDTH;
    xMax = endX / TILE_WIDTH;
    yMin = y / TILE_HEIGHT;
    yMax = endY / TILE_HEIGHT;

    for(curX = xMin; curX <= xMax; curX++)
    {
        for(curY = yMin; curY <= yMax; curY++)
        {
            if(world->tiles[curX + curY * world->width] == WALL_TILE)
                return 0;
        }
    }
    return 1;
}

int32_t checkCoinsCollision(World *world, int64_t x, int64_t y, int32_t width, int32_t height)
{
    int64_t endX = x + width - 1;
    int64_t endY = y + height - 1;
    if(endX < 0 || endY < 0 || x >= world->width * TILE_WIDTH || y >= world->height * TILE_HEIGHT)
    {
        return 0;
    }

    int32_t xMin, xMax, yMin, yMax, curX, curY;
    int32_t curIndex;
    xMin = imini(world->width - 1, x / TILE_WIDTH);
    xMax = imaxi(0, endX / TILE_WIDTH);
    yMin = imini(world->height - 1, y / TILE_HEIGHT);
    yMax = imaxi(0, endY / TILE_HEIGHT);

    for(curX = xMin; curX <= xMax; curX++)
    {
        for(curY = yMin; curY <= yMax; curY++)
        {
            curIndex = curX + curY * world->width;
            if(world->tiles[curIndex] == COIN_TILE)
            {
                world->tiles[curIndex] = SKY_TILE;
                world->numCoins--;
            }
        }
    }
    return 1;
}

int32_t move(GameState *game, int64_t *x, int64_t *y, int32_t width, int32_t height, int64_t *attr, float rest, int64_t longRest)
{
    World *world = &game->world;
    int64_t curMove;
    int32_t moveFactor = 1;
    int32_t labelX;
    if(longRest != 0)
    {
        labelX = (world->width * TILE_WIDTH - game->label.w) >> 1;
        if(longRest < 0)
        {
            moveFactor = -1;
            if(-longRest == longRest)
            {
                longRest++;
            }
            longRest = -longRest;
        }
        while(longRest > 0)
        {
            curMove = lminl(longRest, TILE_WIDTH);
            *attr += curMove * moveFactor;
            if(isFree(world, *x, *y, width, height))
            {

                longRest -= curMove;
                checkCoinsCollision(world, *x, *y, width, height);

                if(world->numCoins <= 1 && attr == y && *y == TILE_HEIGHT && *x + width > labelX && *x < labelX + game->label.w)
                {
                    game->labelint32_tersectCount++;
                }
            }
            else
            {
                *attr -= curMove * moveFactor;
                if(moveFactor < 0)
                {
                    int32_t tileSize = attr == x ? TILE_WIDTH : TILE_HEIGHT;
                    *attr = *attr / tileSize * tileSize;
                    if(world->numCoins <= 1 && attr == y && *attr == tileSize && *x + width > labelX && *x < labelX + game->label.w)
                    {
                        game->labelint32_tersectCount++;
                    }
                }
                else
                {
                    int32_t tileSize = attr == x ? TILE_WIDTH : TILE_HEIGHT;
                    int32_t maxIndex = (attr == x ? width : height) - 1;
                    *attr = ((*attr + maxIndex) / tileSize * tileSize) + (tileSize - 1) - maxIndex;
                }
                return 1;
            }
        }
        *attr += moveFactor;
        if(!isFree(world, *x, *y, width, height))
        {
            *attr -= moveFactor;
            return 1;
        }
        *attr -= moveFactor;
    }
    else
    {
        if(rest < 0.0)
        {
            rest = -rest;
            moveFactor = -1;
        }
        *attr += moveFactor;
        if(!isFree(world, *x, *y, width, height))
        {
            *attr -= moveFactor;
            return 1;
        }
        *attr -= moveFactor;
    }
    return 0;
}

void doUpdate(GameState *game)
{
    int64_t delta;
    float seconds;
    int64_t longRestX = 0, longRestY = 0;
    int64_t decreasingTimes;
    float dAdder, xMove, yMove;
    float dxAvg, dyAvg;
    Man* man = &game->man;
    World* world = &game->world;
    bool right, left, down;
    bool *keyboard = game->keyboard;
    bool *pressed = game->pressed;
    int32_t size;

    getCurrentTime(&game->now);

    delta = game->isFirstUpdate ? 0 : getDelta(&game->lastUpdate, &game->now);
    seconds = delta / 1000000000.0;
    if(delta != 0)
    {
        right = keyboard[SDL_SCANCODE_RIGHT] || keyboard[SDL_SCANCODE_D];
        left  = keyboard[SDL_SCANCODE_LEFT]  || keyboard[SDL_SCANCODE_A];
        down  = keyboard[SDL_SCANCODE_DOWN]  || keyboard[SDL_SCANCODE_S];

        dAdder = ADDER_SPEED_PER_SECOND * seconds;
        if(right ^ left)
        {
            man->dx += (dAdder * (right - left));
            clamp(&man->dx, -MAX_SPEED_PER_SECOND, MAX_SPEED_PER_SECOND);
            man->restDecreasingX = 0;
        }
        else
        {
            man->restDecreasingX += delta;
            decreasingTimes = man->restDecreasingX / SPEED_DECREASING_DELTA;
            man->restDecreasingX %= SPEED_DECREASING_DELTA;
            for(register int64_t i = 0; i < decreasingTimes; i++)
            {
                man->dx *= SPEED_DECREASING_FACTOR;
                if(fabsf(man->dx) < MIN_SPEED)
                {
                    man->dx = 0.0;
                    man->restDecreasingX = 0;
                    break;
                }
            }
        }

        dxAvg = (man->dx + man->lastDx) / 2.0;
        xMove = seconds * dxAvg;

        man->xRest += xMove;
        longRestX = (int64_t) man->xRest;
        man->xRest -= longRestX;

        if(move(game, &man->x, &man->y, RECT_WIDTH, RECT_HEIGHT, &man->x, man->xRest, longRestX))
        {
            man->xRest = 0.0;
            man->dx = 0.0;
        }

        if(man->isFalling)
        {
            dyAvg = (getDelta(&man->fall, &game->now) + getDelta(&man->fall, &game->now)) / 2000000000.0 * GRAVITY_PER_SECOND;
            if(dyAvg < 0.0 && (keyboard[SDL_SCANCODE_SPACE] || keyboard[SDL_SCANCODE_W] || keyboard[SDL_SCANCODE_UP]))
            {
                dyAvg *= SMOOTH_FACTOR;
            }
            if(down)
            {
                addSeconds(&man->fall, -seconds * 1.5);
            }
            yMove = seconds * dyAvg;

            man->yRest += yMove;
            longRestY = (int64_t) man->yRest;
            man->yRest -= longRestY;
            if(move(game, &man->x, &man->y, RECT_WIDTH, RECT_HEIGHT, &man->y, man->yRest, longRestY))
            {
                man->yRest = 0.0;
                man->isFalling = false;
            }
        }
        else
        {
            if(isFree(world, man->x, man->y + 1, RECT_WIDTH, RECT_HEIGHT))
            {
                man->isFalling = true;
                man->fall = game->now;
                man->yRest = 0.0;
            }
            else if(!down && (pressed[SDL_SCANCODE_SPACE] || pressed[SDL_SCANCODE_W] || pressed[SDL_SCANCODE_UP]))
            {
                man->isFalling = true;
                man->fall = game->now;
                addSeconds(&man->fall, JUMP_SECONDS);
            }
        }
        if(!game->showedHidenCoins && game->labelint32_tersectCount >= 3)
        {
            game->showedHidenCoins = true;
            size = world->width * world->height;
            for(register int32_t i = 0; i < size; i++)
            {
                if(world->tiles[i] == HIDEN_COIN_TILE)
                {
                    world->tiles[i] = COIN_TILE;
                }
            }
        }
    }
    game->isFirstUpdate = false;
    man->lastDx = man->dx;
}

void doRender(SDL_Renderer *renderer, GameState *game)
{
    const Man *man = &game->man;
    const World *world = &game->world;
    int32_t x, y;
    SDL_Rect tileRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};

    if(world->numCoins != game->labeledCoins)
    {
        char buf[64];
        destroyImage(&game->label);
        game->labeledCoins = world->numCoins;
        sprintf(buf, "Coins: %d/%d", world->totalCoins - world->numCoins, world->totalCoins);
        loadImageFont(renderer, game->font, buf, 255, 255, 255, 255, &game->label);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 170, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for(x = 0; x < world->width; x++)
    {
        tileRect.x = x * TILE_WIDTH;
        for(y = 0; y < world->height; y++)
        {
            tileRect.y = y * TILE_HEIGHT;
            switch(world->tiles[x + y * world->width])
            {
            case WALL_TILE:
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &tileRect);
                break;
            case COIN_TILE:
                SDL_SetRenderDrawColor(renderer, (COIN_HEX >> 16) & 0xFF, (COIN_HEX >> 8) & 0xFF, COIN_HEX & 0xFF, 255);
                SDL_RenderFillOval(renderer, tileRect.x, tileRect.y, tileRect.w, tileRect.h);
                break;
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 170, 170, 170, 255);
    SDL_Rect playerRect = {man->x, man->y, RECT_WIDTH, RECT_HEIGHT};
    SDL_RenderFillRect(renderer, &playerRect);

    doRenderImage(renderer, &game->label, (world->width * TILE_WIDTH - game->label.w) >> 1, 0);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderPresent(renderer);
}

void destroyGame(GameState *game)
{
    destroyImage(&game->label);
    if(game->font != NULL)
    {
        TTF_CloseFont(game->font);
    }
}
