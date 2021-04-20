#include <libhangman/constants.h>
#include <libhangman/gibbet.h>

#include <SDL2/SDL.h>

int main()
{
    int attempt = 0;
    int code = STATE_OK;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    /**
     * Инициализируются переменные для окна
     * и рендера здесь, чтобы была возможность
     * свободно передавать их другим функциям
     * без риска потери.
     */

    // Проверка успешного открытия и рисунка.
    for (attempt = START_COMMAND; attempt <= 7; attempt++) {
        if (attempt == 7)
            attempt = CLOSE_COMMAND;
        code = gibbet(attempt, &renderer, &window);
        SDL_Delay(1000);
    }
    return code;
}