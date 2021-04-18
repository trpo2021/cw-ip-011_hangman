#include "bodyparts.h"

#include "constants.h"

#include <SDL2/SDL2_gfxPrimitives.h>

void build_gibbet(SDL_Renderer* renderer)
{
    SDL_Rect post, plank;
    int i;
    /**
     * Условно делим окно на 16*10 (VIRTUAL_RES_Y*VIRTUAL_RES_X)
     * частей, по ним строим виселицу и части тела.
     */
    post.x = WINDOW_WIDTH / VIRTUAL_RES_X;
    post.y = WINDOW_HEIGHT / (VIRTUAL_RES_Y / 2);
    post.w = GIB_RESIZE_MORE * WINDOW_WIDTH / (VIRTUAL_RES_X * GIB_RESIZE_LESS);
    post.h = 7 * WINDOW_HEIGHT / (VIRTUAL_RES_Y / 2);
    plank.x = post.x + post.w;
    plank.y = post.y;
    plank.w = 3 * WINDOW_WIDTH / (VIRTUAL_RES_X / 2)
            + (WINDOW_WIDTH / VIRTUAL_RES_X - post.w);
    plank.h = GIB_RESIZE_MORE * WINDOW_HEIGHT
            / (VIRTUAL_RES_Y * GIB_RESIZE_LESS);
    SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, ALPHA);
    // Опорная доска.
    for (i = 0; i < VIRTUAL_RES_Y; i++) {
        SDL_RenderDrawLine(
                renderer,
                post.x + post.w,
                post.y + post.h / (VIRTUAL_RES_Y / 2) + i,
                plank.x + plank.w / (VIRTUAL_RES_X / 2) + i,
                plank.y + plank.h);
    }
    SDL_RenderFillRect(renderer, &post);
    SDL_RenderFillRect(renderer, &plank);
    // Верёвка.
    SDL_RenderDrawLine(
            renderer,
            plank.x + 2 * plank.w / 3,
            plank.y + plank.h,
            plank.x + 2 * plank.w / 3,
            plank.y + plank.h + 4 * WINDOW_HEIGHT / VIRTUAL_RES_Y);
    SDL_Delay(100);
    SDL_RenderPresent(renderer);
}

void add_head(SDL_Renderer* renderer)
{
    int headX, headY, head_rad;
    /**
     * headX = plank.x + 2 * plank.w / 3
     * headY = plank.y + plank.h + 4 * WINDOW_HEIGHT / VIRTUAL_RES_Y
     * head_rad = WINDOW_HEIGHT / (VIRTUAL_RES_Y / 2) / 2
     */
    headX = WINDOW_WIDTH / VIRTUAL_RES_X
            + GIB_RESIZE_MORE * WINDOW_WIDTH / (VIRTUAL_RES_X * GIB_RESIZE_LESS)
            + 2
                    * (3 * WINDOW_WIDTH / (VIRTUAL_RES_X / 2)
                       + (WINDOW_WIDTH / VIRTUAL_RES_X
                          - GIB_RESIZE_MORE * WINDOW_WIDTH
                                  / (VIRTUAL_RES_X * GIB_RESIZE_LESS)))
                    / 3;
    headY = WINDOW_HEIGHT / (VIRTUAL_RES_Y / 2)
            + GIB_RESIZE_MORE * WINDOW_HEIGHT
                    / (VIRTUAL_RES_Y * GIB_RESIZE_LESS)
            + 3 * WINDOW_HEIGHT / VIRTUAL_RES_Y;
    head_rad = WINDOW_HEIGHT / VIRTUAL_RES_Y;
    SDL_SetRenderDrawColor(
            renderer, RED_BACK, GREEN_BACK, BLUE_BACK, ALPHA_BACK);
    filledCircleRGBA(renderer, headX, headY, head_rad, RED, GREEN, BLUE, ALPHA);
    SDL_Delay(10);
    SDL_RenderPresent(renderer);
}

void add_body(SDL_Renderer* renderer)
{
    int bodyX, body_radX, bodyY, body_radY;
    /**
     * bodyX = headX
     * body_radX = 2 * head_rad / 3
     * body_radY = 2 * head_rad
     * bodyY = headY + head_rad + body_radY
     */
    bodyX = WINDOW_WIDTH / VIRTUAL_RES_X
            + GIB_RESIZE_MORE * WINDOW_WIDTH / (VIRTUAL_RES_X * GIB_RESIZE_LESS)
            + 2
                    * (3 * WINDOW_WIDTH / (VIRTUAL_RES_X / 2)
                       + (WINDOW_WIDTH / VIRTUAL_RES_X
                          - GIB_RESIZE_MORE * WINDOW_WIDTH
                                  / (VIRTUAL_RES_X * GIB_RESIZE_LESS)))
                    / 3;
    body_radX = 2 * WINDOW_HEIGHT / VIRTUAL_RES_Y / 3;
    body_radY = 2 * WINDOW_HEIGHT / VIRTUAL_RES_Y;
    bodyY = WINDOW_HEIGHT / (VIRTUAL_RES_Y / 2)
            + GIB_RESIZE_MORE * WINDOW_HEIGHT
                    / (VIRTUAL_RES_Y * GIB_RESIZE_LESS)
            + 3 * WINDOW_HEIGHT / VIRTUAL_RES_Y + 3 * body_radY / 2;
    filledEllipseRGBA(
            renderer,
            bodyX,
            bodyY,
            body_radX,
            body_radY,
            RED,
            GREEN,
            BLUE,
            ALPHA);
    SDL_Delay(10);
    SDL_RenderPresent(renderer);
}

void add_hand1(SDL_Renderer* renderer)
{
    int handX1, handY1, handX2, handY2;
    /**
     * handX1 = bodyX
     * handY1 = bodyY - body_radY
     * handX2 = handX1 - 2 * head_rad
     * handY2 = handY1 + body_radY
     */
    handX1 = WINDOW_WIDTH / VIRTUAL_RES_X
            + GIB_RESIZE_MORE * WINDOW_WIDTH / (VIRTUAL_RES_X * GIB_RESIZE_LESS)
            + 2
                    * (3 * WINDOW_WIDTH / (VIRTUAL_RES_X / 2)
                       + (WINDOW_WIDTH / VIRTUAL_RES_X
                          - GIB_RESIZE_MORE * WINDOW_WIDTH
                                  / (VIRTUAL_RES_X * GIB_RESIZE_LESS)))
                    / 3;
    handY1 = WINDOW_HEIGHT / (VIRTUAL_RES_Y / 2)
            + GIB_RESIZE_MORE * WINDOW_HEIGHT
                    / (VIRTUAL_RES_Y * GIB_RESIZE_LESS)
            + 4 * WINDOW_HEIGHT / VIRTUAL_RES_Y;
    handX2 = handX1 - 2 * WINDOW_HEIGHT / VIRTUAL_RES_Y;
    handY2 = handY1 + 2 * WINDOW_HEIGHT / VIRTUAL_RES_Y;
    SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, ALPHA);
    SDL_RenderDrawLine(renderer, handX1, handY1, handX2, handY2);
    SDL_Delay(10);
    SDL_RenderPresent(renderer);
}

void add_hand2(SDL_Renderer* renderer)
{
    int handX1, handY1, handX2, handY2;
    /**
     * handX1 = bodyX
     * handY1 = bodyY - body_radY
     * handX2 = handX1 + 2 * head_rad
     * handY2 = handY1 + body_radY
     */
    handX1 = WINDOW_WIDTH / VIRTUAL_RES_X
            + GIB_RESIZE_MORE * WINDOW_WIDTH / (VIRTUAL_RES_X * GIB_RESIZE_LESS)
            + 2
                    * (3 * WINDOW_WIDTH / (VIRTUAL_RES_X / 2)
                       + (WINDOW_WIDTH / VIRTUAL_RES_X
                          - GIB_RESIZE_MORE * WINDOW_WIDTH
                                  / (VIRTUAL_RES_X * GIB_RESIZE_LESS)))
                    / 3;
    handY1 = WINDOW_HEIGHT / (VIRTUAL_RES_Y / 2)
            + GIB_RESIZE_MORE * WINDOW_HEIGHT
                    / (VIRTUAL_RES_Y * GIB_RESIZE_LESS)
            + 4 * WINDOW_HEIGHT / VIRTUAL_RES_Y;
    handX2 = handX1 + 2 * WINDOW_HEIGHT / VIRTUAL_RES_Y;
    handY2 = handY1 + 2 * WINDOW_HEIGHT / VIRTUAL_RES_Y;
    SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, ALPHA);
    SDL_RenderDrawLine(renderer, handX1, handY1, handX2, handY2);
    SDL_Delay(10);
    SDL_RenderPresent(renderer);
}

void add_leg1(SDL_Renderer* renderer)
{
    int legX1, legY1, legX2, legY2;
    /**
     * legX1 = bodyX
     * legY1 = bodyY + 3 * body_radY / 4
     * legX2 = legX1 - 2 * head_rad
     * legY2 = legY1 + body_radY
     */
    legX1 = WINDOW_WIDTH / VIRTUAL_RES_X
            + GIB_RESIZE_MORE * WINDOW_WIDTH / (VIRTUAL_RES_X * GIB_RESIZE_LESS)
            + 2
                    * (3 * WINDOW_WIDTH / (VIRTUAL_RES_X / 2)
                       + (WINDOW_WIDTH / VIRTUAL_RES_X
                          - GIB_RESIZE_MORE * WINDOW_WIDTH
                                  / (VIRTUAL_RES_X * GIB_RESIZE_LESS)))
                    / 3;
    legY1 = WINDOW_HEIGHT / (VIRTUAL_RES_Y / 2)
            + GIB_RESIZE_MORE * WINDOW_HEIGHT
                    / (VIRTUAL_RES_Y * GIB_RESIZE_LESS)
            + 6 * WINDOW_HEIGHT / VIRTUAL_RES_Y
            + 3 * WINDOW_HEIGHT / VIRTUAL_RES_Y / 2;
    legX2 = legX1 - 2 * WINDOW_HEIGHT / VIRTUAL_RES_Y;
    legY2 = legY1 + 2 * WINDOW_HEIGHT / VIRTUAL_RES_Y;
    SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, ALPHA);
    SDL_RenderDrawLine(renderer, legX1, legY1, legX2, legY2);
    SDL_Delay(10);
    SDL_RenderPresent(renderer);
}

void add_leg2(SDL_Renderer* renderer)
{
    int legX1, legY1, legX2, legY2;
    /**
     * legX1 = bodyX
     * legY1 = bodyY + 3 * body_radY / 4
     * legX2 = legX1 + 2 * head_rad
     * legY2 = legY1 + body_radY
     */
    legX1 = WINDOW_WIDTH / VIRTUAL_RES_X
            + GIB_RESIZE_MORE * WINDOW_WIDTH / (VIRTUAL_RES_X * GIB_RESIZE_LESS)
            + 2
                    * (3 * WINDOW_WIDTH / (VIRTUAL_RES_X / 2)
                       + (WINDOW_WIDTH / VIRTUAL_RES_X
                          - GIB_RESIZE_MORE * WINDOW_WIDTH
                                  / (VIRTUAL_RES_X * GIB_RESIZE_LESS)))
                    / 3;
    legY1 = WINDOW_HEIGHT / (VIRTUAL_RES_Y / 2)
            + GIB_RESIZE_MORE * WINDOW_HEIGHT
                    / (VIRTUAL_RES_Y * GIB_RESIZE_LESS)
            + 6 * WINDOW_HEIGHT / VIRTUAL_RES_Y
            + 3 * WINDOW_HEIGHT / VIRTUAL_RES_Y / 2;
    legX2 = legX1 + 2 * WINDOW_HEIGHT / VIRTUAL_RES_Y;
    legY2 = legY1 + 2 * WINDOW_HEIGHT / VIRTUAL_RES_Y;
    SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, ALPHA);
    SDL_RenderDrawLine(renderer, legX1, legY1, legX2, legY2);
    SDL_Delay(10);
    SDL_RenderPresent(renderer);
}