#pragma once

#include <SDL2/SDL.h>

typedef struct rectangle_sizes {
    int x_1;
    int y_1;
    int x_2;
    int y_2;
    int h;
    int w;
} rect;

typedef struct circle_sizes {
    int x;
    int y;
    int rad;
} cir;

typedef struct ellipse_sizes {
    int x;
    int y;
    int rad_x;
    int rad_y;
} ell;

typedef struct line_sizes {
    int x_1;
    int y_1;
    int x_2;
    int y_2;
} line;

void build_gibbet(SDL_Renderer* renderer, rect* post, rect* plank, cir* head);
void add_head(SDL_Renderer* renderer, cir* head);
void add_body(SDL_Renderer* renderer, ell* body);
void add_hand1(SDL_Renderer* renderer, line* hand1);
void add_hand2(SDL_Renderer* renderer, line* hand2);
void add_leg1(SDL_Renderer* renderer, line* leg1);
void add_leg2(SDL_Renderer* renderer, line* leg2);