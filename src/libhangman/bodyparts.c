#include "bodyparts.h"

#include "constants.h"

#include <SDL2/SDL2_gfxPrimitives.h>

void build_gibbet(SDL_Renderer* renderer, rect* post, rect* plank, cir* head)
{
    int i;
    SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, ALPHA);
    // Опорная доска.
    for (i = 0; i < VIRTUAL_RES_Y; i++) {
        SDL_RenderDrawLine(
                renderer,
                post->x_2,
                post->y_1 + post->h / (VIRTUAL_RES_Y / 2) + i,
                post->x_1 + post->w / (VIRTUAL_RES_X / 2) + i,
                post->y_2);
    }
    boxRGBA(renderer,
            post->x_1,
            post->y_1,
            post->x_2,
            post->y_2,
            RED,
            GREEN,
            BLUE,
            ALPHA);
    boxRGBA(renderer,
            plank->x_1,
            plank->y_1,
            plank->x_2,
            plank->y_2,
            RED,
            GREEN,
            BLUE,
            ALPHA);
    // Верёвка.
    SDL_RenderDrawLine(renderer, head->x, plank->y_2, head->x, head->y);
}

void add_head(SDL_Renderer* renderer, cir* head)
{
    filledCircleRGBA(
            renderer, head->x, head->y, head->rad, RED, GREEN, BLUE, ALPHA);
}

void add_body(SDL_Renderer* renderer, ell* body)
{
    filledEllipseRGBA(
            renderer,
            body->x,
            body->y,
            body->rad_x,
            body->rad_y,
            RED,
            GREEN,
            BLUE,
            ALPHA);
}

void add_hand1(SDL_Renderer* renderer, line* hand1)
{
    SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, ALPHA);
    SDL_RenderDrawLine(
            renderer, hand1->x_1, hand1->y_1, hand1->x_2, hand1->y_2);
}

void add_hand2(SDL_Renderer* renderer, line* hand2)
{
    SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, ALPHA);
    SDL_RenderDrawLine(
            renderer, hand2->x_1, hand2->y_1, hand2->x_2, hand2->y_2);
}

void add_leg1(SDL_Renderer* renderer, line* leg1)
{
    SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, ALPHA);
    SDL_RenderDrawLine(renderer, leg1->x_1, leg1->y_1, leg1->x_2, leg1->y_2);
}

void add_leg2(SDL_Renderer* renderer, line* leg2)
{
    SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, ALPHA);
    SDL_RenderDrawLine(renderer, leg2->x_1, leg2->y_1, leg2->x_2, leg2->y_2);
}