#include "game.h"

#include "constants.h"
#include "gibbet.h"

#include <stdio.h>

void word_in_lowercase(char* word)
{
    int i;
    for (i = 0; i < (int)strlen(word); i += CYR_BYTE_COUNT) {
        if ((word[i + 1] >= (char)CYR_START_0)
            && (word[i + 1] <= (char)CYR_END_0)) {
            word[i + 1] += CYR_CAPS_DISLOC_0;
        }

        if ((word[i + 1] >= (char)CYR_START_1)
            && (word[i + 1] <= (char)CYR_END_UPPERCASE)) {
            word[i] = CYR_FIRST_BYTE_1;
            word[i + 1] += CYR_CAPS_DISLOC_1;
        }

        if ((word[i] == (char)CYR_FIRST_BYTE_0)
            && word[i + 1] == (char)CYR_YO_UPPERCASE) {
            word[i] = CYR_FIRST_BYTE_1;
            word[i + 1] = CYR_YO_LOWERCASE;
        }
    }
}

void print_word_h(char word_hidden[][CYR_BYTE_COUNT])
{
    int i;
    for (i = 0; i < MAX_WORD_SIZE; i++) {
        if (word_hidden[i][0] == HIDDEN_SYMBOL) {
            printf("%c", HIDDEN_SYMBOL);
        } else if (
                (word_hidden[i][0] == (char)CYR_FIRST_BYTE_0)
                || (word_hidden[i][0] == (char)CYR_FIRST_BYTE_1)) {
            printf("%c%c", word_hidden[i][0], word_hidden[i][1]);
        }
    }
}

int check_input(char* symbol)
{
    if (symbol[0] == (char)CYR_FIRST_BYTE_0) {
        symbol[1] = getchar();
        if (symbol[1] == (char)CYR_YO_UPPERCASE)
            return 1;
        if ((symbol[1] >= (char)CYR_START_0)
            || (symbol[1] <= (char)(CYR_END_0 + CYR_CAPS_DISLOC_0)))
            return 1;
    }
    if (symbol[0] == (char)CYR_FIRST_BYTE_1) {
        symbol[1] = getchar();
        if (symbol[1] == (char)CYR_YO_LOWERCASE)
            return 1;
        if ((symbol[1] >= (char)(CYR_START_1 + CYR_CAPS_DISLOC_1))
            || (symbol[1] <= (char)(CYR_END_UPPERCASE + CYR_CAPS_DISLOC_1)))
            return 1;
    }
    return 0;
}

void letter_in_lowercase(char* symbol)
{
    if (symbol[0] == (char)CYR_FIRST_BYTE_0) {
        if (symbol[1] == (char)CYR_YO_UPPERCASE) {
            symbol[0] = CYR_FIRST_BYTE_1;
            symbol[1] = CYR_YO_LOWERCASE;
        } else if (
                (symbol[1] >= (char)CYR_START_0)
                && (symbol[1] <= (char)CYR_END_UPPERCASE)) {
            if (symbol[1] >= (char)CYR_START_1) {
                symbol[0] = CYR_FIRST_BYTE_1;
                symbol[1] += CYR_CAPS_DISLOC_1;
            } else
                symbol[1] += CYR_CAPS_DISLOC_0;
        }
    }
}

void check_correct(
        char* word,
        char word_hidden[][CYR_BYTE_COUNT],
        char* symbol,
        int* symbol_found)
{
    int i;
    *symbol_found = 0;

    for (i = 0; i < (int)strlen(word); i += CYR_BYTE_COUNT) {
        if ((word[i] == symbol[0]) && (word[i + 1] == symbol[1])
            && (word_hidden[i / CYR_BYTE_COUNT][0] == HIDDEN_SYMBOL)) {
            *symbol_found = 1;
            word_hidden[i / CYR_BYTE_COUNT][0] = symbol[0];
            word_hidden[i / CYR_BYTE_COUNT][1] = symbol[1];
        }
    }
}

void check_repeat(char* alphabet, char* symbol, int* symbol_repeat)
{
    int alphabet_loc;
    *symbol_repeat = 0;

    if (symbol[0] == (char)CYR_FIRST_BYTE_0) {
        alphabet_loc = (unsigned char)symbol[1] - ALPHABET_D0_DISLOC;
        if (alphabet[alphabet_loc] != HIDDEN_SYMBOL)
            *symbol_repeat = 1;
        else
            alphabet[alphabet_loc] = 1;
    } else {
        if (symbol[1] == (char)CYR_YO_LOWERCASE) {
            alphabet_loc = CYR_YO_LOWERCASE - ALPHABET_YO_DISLOC;
        } else {
            alphabet_loc = (unsigned char)symbol[1] - ALPHABET_D1_DISLOC;
        }
        if (alphabet[alphabet_loc] != HIDDEN_SYMBOL)
            *symbol_repeat = 1;
        else
            alphabet[alphabet_loc] = 1;
    }
}

int cyr_strcmp(char* word, char word_hidden[][CYR_BYTE_COUNT])
{
    int i, j;
    for (i = 0, j = 0; i < (int)(strlen(word)); i += CYR_BYTE_COUNT, j++) {
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

    char word_hidden[MAX_WORD_SIZE][CYR_BYTE_COUNT];
    char symbol[CYR_BYTE_COUNT];

    char alphabet[ALPHABET_SIZE];

    int symbol_n = 0;

    // Пишем слово в маленьком регистре.
    word_in_lowercase(word);

    // Инициализация маски слова.
    for (i = 0; i < (int)strlen(word) / CYR_BYTE_COUNT; i++)
        word_hidden[i][0] = HIDDEN_SYMBOL;
    word_hidden[i][0] = '\0';

    // Инициализация "пустого" алфавита для проверки повтора.
    for (i = 0; i < ALPHABET_SIZE; i++)
        alphabet[i] = HIDDEN_SYMBOL;

    while (attempt != MAX_FAIL) {
        /**
         * При symbols == NULL выполнять обычную игру.
         * При symbols != NULL выполнять тест.
         */

        if (symbols == NULL) {
            system("clear");

            printf("Угадайте слово: ");
            print_word_h(word_hidden);
            printf("\n\n");
            printf("Введите букву английского алфавита.\n");
            printf("Вы можете написать сразу часть слова.\n\n");
            printf("Неверных попыток: %d\n", attempt);
            printf("Осталось попыток: %d\n\n", MAX_FAIL - attempt);

            if (symbol_repeat)
                printf("Вы уже вводили эту букву.\n\n");
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

            if (check_input(symbol))
                break;
        }

        // Запись буквы в маленьком регистре.
        letter_in_lowercase(symbol);

        // Проверка буквы на правильность.
        check_correct(word, word_hidden, symbol, &symbol_found);

        // Проверка на повтор буквы.
        check_repeat(alphabet, symbol, &symbol_repeat);

        if (!symbol_found && !symbol_repeat) {
            attempt++;
            if (symbols == NULL)
                gibbet(attempt, renderer, window);
        }

        str_equal = cyr_strcmp(word, word_hidden);

        if (str_equal == WIN)
            break;
    }

    if (str_equal == WIN)
        return WIN;
    return LOSE;
}