#include <libhangman/constants.h>
#include <libhangman/game.h>
#include <libhangman/gibbet.h>
#include <libhangman/readingfile.h>

#include <SDL2/SDL.h>

#include <unistd.h>

int main()
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    char word[MAX_WORD_SIZE] = "\0";

#ifdef DIRECTORY

    /**
     * Изменение рабочего каталога для возможности запуска
     * программы из любого каталога.
     */
    chdir(DIRECTORY);

#endif

    gibbet(START_COMMAND, &renderer, &window);
    readingfile(word);

    game(&renderer, &window, word);

    gibbet(CLOSE_COMMAND, &renderer, &window);

    return 0;
}