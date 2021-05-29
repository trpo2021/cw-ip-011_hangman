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

    int status_code = SUCCESS;

#ifdef DIRECTORY

    /**
     * Изменение рабочего каталога для возможности запуска
     * программы из любого каталога.
     */
    chdir(DIRECTORY);

#endif

    status_code = read_random_word(word);
    if (status_code != SUCCESS) {
        printf("Обнаружена ошибка.\n\n");
        printf("Код = %d\n", status_code);
        if (status_code == FILE_NOT_FOUND)
            printf("Не обнаружен файл words.txt");
        else if (status_code == EMPTY_FILE)
            printf("Пустой файл.");
        else if (
                status_code == SPACE_IN_BEGIN || status_code == DOUBLE_SPACE
                || status_code == SPACE_IN_END)
            printf("Лишний пробел.");
        else if (status_code == FOUND_WRONG_CHAR)
            printf("Обнаружен неверный символ.");
        else if (status_code == WORD_IS_TOO_BIG)
            printf("Обнаружено слово размером 20 или больше.");
        printf("\n\n");
#ifdef DIRECTORY
        printf("Убедитесь, что существует словарь по адресу\n%s/%s\n\n",
               DIRECTORY,
               FILE_PATH);
#endif
        printf("Словарь не должен быть пустым, не должен содержать\n"
               "пробелов в начале, конце, повторяющихся пробелов и символов,\n"
               "кроме букв русского алфавита. Слова не должны содержать\n"
               "в себе больше 20 букв.\n\n");
        return status_code;
    }

    gibbet(START_COMMAND, &renderer, &window);

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

    gibbet(CLOSE_COMMAND, &renderer, &window);

    return 0;
}