#include <libhangman/constants.h>
#include <libhangman/gibbet.h>

#include <SDL2/SDL.h>
#include <ctest.h>

CTEST(GRAPHIC, INIT_DRAW_CLOSE)
{
    int attempt, code = STATE_OK;
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;
    for (attempt = START_COMMAND; attempt <= 7; attempt++) {
        if (attempt == 7)
            attempt = CLOSE_COMMAND;
        code = gibbet(attempt, &renderer, &window);
        ASSERT_EQUAL(code, STATE_OK);
    }
    ASSERT_NULL(renderer);
    ASSERT_NULL(window);
}