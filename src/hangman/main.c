#include <SDL2/SDL.h>
#include <libhangman/constants.h>
#include <libhangman/gibbet.h>
#include <libhangman/readingfile.h>
#include <stdio.h>

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
    char s[MAX_WORD_SIZE] = "\0";
    readingfile(s);

    printf("\n%s\n", s);
    for (attempt = START_COMMAND; attempt <= 7; attempt++) {
        if (attempt == 7)
            attempt = CLOSE_COMMAND;
        code = gibbet(attempt, &renderer, &window);
        SDL_Delay(1000);
    }

    return code;
}