#include "bodyparts.h"

#include "constants.h"

#include <SDL2/SDL2_gfxPrimitives.h>

void build_gibbet(SDL_Renderer* renderer)
{
    int i;
    SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, ALPHA);
    // Опорная доска.
    for (i = 0; i < VIRTUAL_RES_Y; i++) {
        SDL_RenderDrawLine(
                renderer,
                POST_X2,
                POST_Y1 + POST_H / (VIRTUAL_RES_Y / 2) + i,
                PLANK_X1 + PLANK_W / (VIRTUAL_RES_X / 2) + i,
                PLANK_Y2);
    }
    boxRGBA(renderer,
            POST_X1,
            POST_Y1,
            POST_X2,
            POST_Y2,
            RED,
            GREEN,
            BLUE,
            ALPHA);
    boxRGBA(renderer,
            PLANK_X1,
            PLANK_Y1,
            PLANK_X2,
            PLANK_Y2,
            RED,
            GREEN,
            BLUE,
            ALPHA);
    // Верёвка.
    SDL_RenderDrawLine(renderer, HEAD_X, PLANK_Y2, HEAD_X, HEAD_Y);
    SDL_Delay(100);
    SDL_RenderPresent(renderer);
}

void add_head(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(
            renderer, RED_BACK, GREEN_BACK, BLUE_BACK, ALPHA_BACK);
    filledCircleRGBA(
            renderer, HEAD_X, HEAD_Y, HEAD_RAD, RED, GREEN, BLUE, ALPHA);
    SDL_Delay(100);
    SDL_RenderPresent(renderer);
}

void add_body(SDL_Renderer* renderer)
{
    filledEllipseRGBA(
            renderer,
            BODY_X,
            BODY_Y,
            BODY_RAD_X,
            BODY_RAD_Y,
            RED,
            GREEN,
            BLUE,
            ALPHA);
    SDL_Delay(100);
    SDL_RenderPresent(renderer);
}

void add_hand1(SDL_Renderer* renderer)
{
    int handX1, handY1, handX2, handY2;
    handX1 = BODY_X;
    handY1 = BODY_Y - BODY_RAD_Y;
    handX2 = handX1 - 2 * HEAD_RAD;
    handY2 = handY1 + 2 * HEAD_RAD;
    SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, ALPHA);
    SDL_RenderDrawLine(renderer, handX1, handY1, handX2, handY2);
    SDL_Delay(100);
    SDL_RenderPresent(renderer);
}

void add_hand2(SDL_Renderer* renderer)
{
    int handX1, handY1, handX2, handY2;
    handX1 = BODY_X;
    handY1 = BODY_Y - BODY_RAD_Y;
    handX2 = handX1 + 2 * HEAD_RAD;
    handY2 = handY1 + 2 * HEAD_RAD;
    SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, ALPHA);
    SDL_RenderDrawLine(renderer, handX1, handY1, handX2, handY2);
    SDL_Delay(100);
    SDL_RenderPresent(renderer);
}

void add_leg1(SDL_Renderer* renderer)
{
    int legX1, legY1, legX2, legY2;
    legX1 = BODY_X;
    legY1 = BODY_Y + 3 * BODY_RAD_Y / 4;
    legX2 = legX1 - 2 * HEAD_RAD;
    legY2 = legY1 + BODY_RAD_Y;
    SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, ALPHA);
    SDL_RenderDrawLine(renderer, legX1, legY1, legX2, legY2);
    SDL_Delay(100);
    SDL_RenderPresent(renderer);
}

void add_leg2(SDL_Renderer* renderer)
{
    int legX1, legY1, legX2, legY2;
    legX1 = BODY_X;
    legY1 = BODY_Y + 3 * BODY_RAD_Y / 4;
    legX2 = legX1 + 2 * HEAD_RAD;
    legY2 = legY1 + BODY_RAD_Y;
    SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, ALPHA);
    SDL_RenderDrawLine(renderer, legX1, legY1, legX2, legY2);
    SDL_Delay(100);
    SDL_RenderPresent(renderer);
}