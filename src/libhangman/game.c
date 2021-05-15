#include "game.h"

#include "constants.h"
#include "gibbet.h"

#include <string.h>

#ifndef TEST

int game(SDL_Renderer** renderer, SDL_Window** window, char* word)

#else

#include <../test/test_constants.h>

int game(char* word, char* symbols)

#endif

{
    int attempt = 0, i, symbol_found = 0, symbol_repeat = 0;
    int str_equal;

    char word_hidden[MAX_WORD_SIZE];
    char symbol;

    char alphabet[ALPHABET_SIZE];
    int alphabet_loc;

#ifdef TEST

    int symbol_n = 0;

#endif

    // Пишем слово в маленьком регистре.
    for (i = 0; i < (int)strlen(word); i++)
        if ((word[i] <= ASCII_END) && (word[i] >= ASCII_START))
            word[i] = word[i] + ASCII_CAPS_DISLOC;

    // Инициализация "пустого" алфавита для проверки повтора.
    for (i = 0; i < (int)strlen(word); i++)
        word_hidden[i] = HIDDEN_SYMBOL;
    word_hidden[i] = '\0';

    // Инициализация маски слова.
    for (i = 0; i < ALPHABET_SIZE; i++)
        alphabet[i] = HIDDEN_SYMBOL;
    alphabet[i] = '\0';

    while (attempt != MAX_FAIL) {
#ifndef TEST

        system("clear");

        printf("Угадайте слово: %s\n\n", word_hidden);
        printf("Введите букву английского алфавита.\n\n");
        printf("Неверных попыток: %d\n", attempt);
        printf("Осталось попыток: %d\n\n", MAX_FAIL - attempt);

        if (symbol_repeat) {
            printf("Вы уже вводили эту букву.\n\n");
            symbol_repeat = 0;
        }

#endif

        // Проверка правильности буквы.
        while (1) {
#ifndef TEST

            while ((symbol = getchar()) == '\n')
                ;

#else

            if (symbol_n < (int)strlen(symbols))
                symbol = symbols[symbol_n++];
            /**
             * Использовать "спрятанный символ"
             * для преждевременного прекращения теста.
             */
            if (symbol == HIDDEN_SYMBOL)
                return EXIT;

#endif

            if (((symbol <= ASCII_END) && (symbol >= ASCII_START))
                || ((symbol <= ASCII_END + ASCII_CAPS_DISLOC)
                    && (symbol >= ASCII_START + ASCII_CAPS_DISLOC)))
                break;
        }

        // Запись буквы в маленьком регистре.
        if ((symbol <= ASCII_END) && (symbol >= ASCII_START))
            symbol = symbol + ASCII_CAPS_DISLOC;

        // Проверка буквы на правильность.
        for (i = 0; i < (int)strlen(word); i++) {
            if (word[i] == symbol && word_hidden[i] == HIDDEN_SYMBOL) {
                symbol_found = 1;
                word_hidden[i] = symbol;
            }
        }

        // Проверка на повтор буквы.
        alphabet_loc = (int)(symbol - (ASCII_START + ASCII_CAPS_DISLOC));
        if (symbol == alphabet[alphabet_loc])
            symbol_repeat = 1;
        else
            alphabet[alphabet_loc] = symbol;

        // Проверка на верность введённого символа и повтор.
        if (!symbol_found && !symbol_repeat) {
            attempt++;

#ifndef TEST

            gibbet(attempt, renderer, window);

#endif
        }

        symbol_found = 0;
        str_equal = !strcmp(word, word_hidden);
        if (str_equal)
            break;
    }

#ifndef TEST

    system("clear");
    if (str_equal)
        printf("Вы победили.\n");
    else
        printf("Вы проиграли.\n");
    printf("Слово: %s\n", word);

    return SUCCESS_GAME;

#else

    if (str_equal)
        return WIN;
    return LOSE;

#endif
}