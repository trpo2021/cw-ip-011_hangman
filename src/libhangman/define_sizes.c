#include "define_sizes.h"

#include "constants.h"

void define_size_post(rect* post)
{
    post->x_1 = WINDOW_WIDTH / VIRTUAL_RES_X;
    post->y_1 = WINDOW_HEIGHT / (VIRTUAL_RES_Y / 2);

    post->w = GIB_RESIZE_MORE * WINDOW_WIDTH
            / (VIRTUAL_RES_X * GIB_RESIZE_LESS);
    post->h = 7 * WINDOW_HEIGHT / (VIRTUAL_RES_Y / 2);

    post->x_2 = post->x_1 + post->w;
    post->y_2 = post->y_1 + post->h;
}

void define_size_plank(rect* plank, rect* post)
{
    plank->x_1 = post->x_2;
    plank->y_1 = post->y_1;

    plank->w = 3 * WINDOW_WIDTH / (VIRTUAL_RES_X / 2)
            + (WINDOW_WIDTH / VIRTUAL_RES_X - post->w);
    plank->h = GIB_RESIZE_MORE * WINDOW_HEIGHT
            / (VIRTUAL_RES_Y * GIB_RESIZE_LESS);

    plank->x_2 = plank->x_1 + plank->w;
    plank->y_2 = plank->y_1 + plank->h;
}

void define_size_head(cir* head, rect* plank)
{
    head->x = plank->x_1 + GIB_RESIZE_MORE * plank->w / GIB_RESIZE_LESS;

    head->y = plank->y_2 + 4 * WINDOW_HEIGHT / VIRTUAL_RES_Y;

    head->rad = WINDOW_HEIGHT / VIRTUAL_RES_Y;
}

void define_size_body(ell* body, cir* head)
{
    body->x = head->x;

    body->rad_x = GIB_RESIZE_MORE * head->rad / GIB_RESIZE_LESS;
    body->rad_y = GIB_RESIZE_MORE * head->rad;

    body->y = head->y + head->rad + body->rad_y;
}

void define_size_hands(line* hand1, line* hand2, ell* body, cir* head)
{
    hand1->x_1 = body->x;
    hand1->y_1 = body->y - body->rad_y;
    hand1->x_2 = hand1->x_1 - 2 * head->rad;
    hand1->y_2 = hand1->y_1 + 2 * head->rad;

    hand2->x_1 = body->x;
    hand2->y_1 = body->y - body->rad_y;
    hand2->x_2 = hand2->x_1 + 2 * head->rad;
    hand2->y_2 = hand1->y_1 + 2 * head->rad;
}

void define_size_legs(line* leg1, line* leg2, ell* body, cir* head)
{
    leg1->x_1 = body->x;
    leg1->y_1 = body->y + 3 * body->rad_y / 4;
    leg1->x_2 = leg1->x_1 - 2 * head->rad;
    leg1->y_2 = leg1->y_1 + body->rad_y;

    leg2->x_1 = body->x;
    leg2->y_1 = body->y + 3 * body->rad_y / 4;
    leg2->x_2 = leg2->x_1 + 2 * head->rad;
    leg2->y_2 = leg1->y_1 + body->rad_y;
}

void define_sizes(
        rect* post,
        rect* plank,
        cir* head,
        ell* body,
        line* hand1,
        line* hand2,
        line* leg1,
        line* leg2)
{
    define_size_post(post);

    define_size_plank(plank, post);

    define_size_head(head, plank);

    define_size_body(body, head);

    define_size_hands(hand1, hand2, body, head);

    define_size_legs(leg1, leg2, body, head);
}
