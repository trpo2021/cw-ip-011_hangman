#include "game.h"

#include "constants.h"
#include "gibbet.h"

#include <stdio.h>

int cyr_strcmp(char word[MAX_WORD_SIZE], char word_hidden[MAX_WORD_SIZE][2])
{
    int i, j;
    for (i = 0, j = 0; i < (int)(strlen(word)); i += 2, j++) {
        if ((word[i] != word_hidden[j][0])
            && (word[i + 1] != word_hidden[j][1]))
            return LOSE;
    }
    return WIN;
}

int game(
        SDL_Renderer** renderer, SDL_Window** window, char* word, char* symbols)
{
    int attempt = 0, i, symbol_found = 0, symbol_repeat = 0;
    int str_equal;

    char word_hidden[MAX_WORD_SIZE][2];
    char symbol[2];

    // char alphabet[ALPHABET_SIZE];
    // int alphabet_loc;

    int symbol_n = 0;

    // Пишем слово в маленьком регистре.
    for (i = 0; i < (int)strlen(word); i += 2) {
        if ((word[i + 1] >= CYR_START_0 - BYTE_SIZE)
            && (word[i + 1] <= CYR_END_0 - BYTE_SIZE)) {
            word[i + 1] += CYR_CAPS_DISLOC_0;
        }

        if ((word[i + 1] >= CYR_START_1 - BYTE_SIZE)
            && (word[i + 1] <= CYR_END_UPPERCASE - BYTE_SIZE)) {
            word[i] = CYR_FIRST_BYTE_1;
            word[i + 1] += CYR_CAPS_DISLOC_1;
        }

        if ((word[i] == CYR_FIRST_BYTE_0 - BYTE_SIZE)
            && word[i + 1] == CYR_YO_UPPERCASE - BYTE_SIZE) {
            word[i] = CYR_FIRST_BYTE_1;
            word[i + 1] = CYR_YO_LOWERCASE;
        }
    }

    // Инициализация "пустого" алфавита для проверки повтора.
    for (i = 0; i < (int)strlen(word) / 2; i++)
        word_hidden[i][0] = HIDDEN_SYMBOL;
    word_hidden[i][0] = '\0';

    // Инициализация маски слова.
    // for (i = 0; i < ALPHABET_SIZE; i++)
    //    alphabet[i] = HIDDEN_SYMBOL;
    // alphabet[i] = '\0';

    while (attempt != MAX_FAIL) {
        /**
         * При symbols == NULL выполнять обычную игру.
         * При symbols != NULL выполнять тест.
         */

        if (symbols == NULL) {
            system("clear");

            printf("Угадайте слово: ");
            for (i = 0; i < MAX_WORD_SIZE; i++) {
                if (word_hidden[i][0] == HIDDEN_SYMBOL) {
                    printf("%c", HIDDEN_SYMBOL);
                } else if (
                        (word_hidden[i][0] == CYR_FIRST_BYTE_0 - BYTE_SIZE)
                        || (word_hidden[i][0]
                            == CYR_FIRST_BYTE_1 - BYTE_SIZE)) {
                    printf("%c%c", word_hidden[i][0], word_hidden[i][1]);
                }
            }
            printf("\n\n");
            printf("Введите букву английского алфавита.\n");
            printf("Вы можете написать сразу часть слова.\n\n");
            printf("Неверных попыток: %d\n", attempt);
            printf("Осталось попыток: %d\n\n", MAX_FAIL - attempt);

            if (symbol_repeat) {
                printf("Вы уже вводили эту букву.\n\n");
                symbol_repeat = 0;
            }
        }

        // Проверка правильности буквы.
        while (1) {
            if (symbols == NULL) {
                while ((symbol[0] = getchar()) == '\n')
                    ;

            } else {
                if (symbol_n < (int)strlen(symbols))
                    symbol[0] = symbols[symbol_n++];
                /**
                 * Использовать "спрятанный символ"
                 * для преждевременного прекращения теста.
                 */
                if (symbol[0] == HIDDEN_SYMBOL)
                    return EXIT;
            }

            if (symbol[0] == CYR_FIRST_BYTE_0 - BYTE_SIZE) {
                symbol[1] = getchar();
                if (symbol[1] == CYR_YO_UPPERCASE - BYTE_SIZE)
                    break;
                if ((symbol[1] >= CYR_START_0 - BYTE_SIZE)
                    || (symbol[1] <= CYR_END_0 + CYR_CAPS_DISLOC_0 - BYTE_SIZE))
                    break;
            }
            if (symbol[0] == CYR_FIRST_BYTE_1 - BYTE_SIZE) {
                symbol[1] = getchar();
                if (symbol[1] == CYR_YO_LOWERCASE - BYTE_SIZE)
                    break;
                if ((symbol[1] >= CYR_START_1 + CYR_CAPS_DISLOC_1 - BYTE_SIZE)
                    || (symbol[1]
                        <= CYR_END_UPPERCASE + CYR_CAPS_DISLOC_1 - BYTE_SIZE))
                    break;
            }
        }

        // Запись буквы в маленьком регистре.
        if (symbol[0] == CYR_FIRST_BYTE_0 - BYTE_SIZE) {
            if (symbol[1] == CYR_YO_UPPERCASE - BYTE_SIZE) {
                symbol[0] = CYR_FIRST_BYTE_1;
                symbol[1] = CYR_YO_LOWERCASE;
            } else if (
                    (symbol[1] >= CYR_START_0 - BYTE_SIZE)
                    && (symbol[1] <= CYR_END_UPPERCASE - BYTE_SIZE)) {
                if (symbol[1] >= CYR_START_1 - BYTE_SIZE) {
                    symbol[0] = CYR_FIRST_BYTE_1;
                    symbol[1] += CYR_CAPS_DISLOC_1;
                } else
                    symbol[1] += CYR_CAPS_DISLOC_0;
            }
        }
        // Проверка буквы на правильность.
        for (i = 0; i < (int)strlen(word); i += 2) {
            if ((word[i] == symbol[0]) && (word[i + 1] == symbol[1])
                && (word_hidden[i / 2][0] == HIDDEN_SYMBOL)) {
                symbol_found = 1;
                word_hidden[i / 2][0] = symbol[0];
                word_hidden[i / 2][1] = symbol[1];
            }
        }
        /*
                // Проверка на повтор буквы.
                alphabet_loc = (int)(symbol[0] - (ASCII_START +
           ASCII_CAPS_DISLOC)); if (symbol[0] == alphabet[alphabet_loc])
                    symbol_repeat = 1;
                else
                    alphabet[alphabet_loc] = symbol[0];
        */
        // Проверка на верность введённого символа и повтор.
        if (!symbol_found) { // && !symbol_repeat) {
            attempt++;

            if (symbols == NULL)

                gibbet(attempt, renderer, window);
        }

        symbol_found = 0;
        str_equal = cyr_strcmp(word, word_hidden);
        if (str_equal == WIN)
            break;
    }

    if (str_equal == WIN)
        return WIN;
    return LOSE;
}