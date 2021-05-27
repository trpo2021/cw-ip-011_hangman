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

    int game_state = LOSE;

#ifdef DIRECTORY

    /**
     * Изменение рабочего каталога для возможности запуска
     * программы из любого каталога.
     */
    chdir(DIRECTORY);

#endif

    gibbet(START_COMMAND, &renderer, &window);
    read_random_word(word);

    game_state = game(&renderer, &window, word, NULL);

    system("clear");
    if (game_state == WIN)
        printf("Вы победили.\n");
    else if (game_state == LOSE)
        printf("Вы проиграли.\n");
    else {
        printf("ОШИБКА: Получен неверный код статуса игры: %d", game_state);
        return game_state;
    }
    printf("Слово: %s\n\n", word);

    gibbet(CLOSE_COMMAND, &renderer, &window);

    return 0;
}