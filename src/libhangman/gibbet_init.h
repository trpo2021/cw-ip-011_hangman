#pragma once

#include <SDL2/SDL.h>

int initialize(SDL_Renderer** renderer, SDL_Window** window);
void close(SDL_Renderer** renderer, SDL_Window** window, int code);