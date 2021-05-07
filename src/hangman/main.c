#include <SDL2/SDL.h>
#include <libhangman/constants.h>
#include <libhangman/gibbet.h>
#include <libhangman/readingfile.h>
#include <stdio.h>

int main()
{
    int attempt = 0, i = 0, symbol_found = 0, symbol_repeat = 0;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    char word[MAX_WORD_SIZE] = "\0";
    char word_hidden[MAX_WORD_SIZE];
    char symbol;

    gibbet(attempt, &renderer, &window);
    readingfile(word);

    // Инициализация маски слова.
    for (i = 0; i < (int)strlen(word); i++)
        word_hidden[i] = HIDDEN_SYMBOL;
    word_hidden[i] = '\0';

    while (attempt != MAX_FAIL) {
        system("clear");
        printf("Угадайте слово: %s\n\n", word_hidden);

        if (symbol_repeat) {
            printf("Вы уже вводили эту букву.\n\n");
            symbol_repeat = 0;
        }

        while ((symbol = getchar()) == '\n')
            ;

        for (i = 0; i < (int)strlen(word); i++) {
            // Пользователь ввёл отгаданную букву вновь.
            if (word[i] == symbol && word_hidden[i] == symbol)
                symbol_repeat = 1;

            // Пользователь ввёл неверную букву.
            if (word[i] == symbol && word_hidden[i] == HIDDEN_SYMBOL) {
                symbol_found = 1;
                word_hidden[i] = symbol;
            }
        }

        // Проверка на верность введённого символа и повтор.
        if (!symbol_found && !symbol_repeat) {
            attempt++;
            gibbet(attempt, &renderer, &window);
        }

        symbol_found = 0;

        if (!strcmp(word, word_hidden))
            break;
    }

    gibbet(CLOSE_COMMAND, &renderer, &window);

    system("clear");
    if (!strcmp(word, word_hidden))
        printf("Вы победили.\n");
    else
        printf("Вы проиграли.\n");
    printf("Слово: %s\n", word);
    return 0;
}