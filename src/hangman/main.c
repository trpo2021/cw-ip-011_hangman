#include <libhangman/constants.h>
#include <libhangman/game.h>
#include <libhangman/gibbet.h>
#include <libhangman/readingfile.h>

#include <SDL2/SDL.h>

#ifdef DIRECTORY

// Используется только для chdir
#include <unistd.h>

#endif

int main()
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    char word[MAX_WORD_SIZE] = "\0";

    int game_state = EXIT;

    int status_code = SUCCESS;

#ifdef DIRECTORY

    /**
     * Изменение рабочего каталога для возможности запуска
     * программы из любого каталога.
     */
    chdir(DIRECTORY);

#endif

    status_code = read_random_word(word);
    print_check_res(status_code);
    if (status_code != SUCCESS)
        return status_code;

    gibbet(START_COMMAND, &renderer, &window);

    game_state = game(&renderer, &window, word, NULL);

    system("clear");
    if (game_state == WIN)
        printf("Вы победили.");
    else if (game_state == LOSE)
        printf("Вы проиграли.");
    else if (game_state == EXIT)
        printf("Выходим...\n\n");
    else {
        printf("ОШИБКА: Получен неизвестный код статуса игры: %d\n",
               game_state);
        return game_state;
    }
    if (game_state != EXIT)
        printf("\n\nСлово: %s\n\n", word);

    printf("Нажмите ENTER для продолжения...");

    // Избавление от \n, оставленного предыдущим getchar'ом.
    getchar();
    getchar();

    gibbet(CLOSE_COMMAND, &renderer, &window);

    return 0;
}