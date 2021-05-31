#include <libhangman/constants.h>
#include <libhangman/game.h>
#include <libhangman/readingfile.h>

#include <SDL2/SDL.h>
#include <ctest.h>
#include <time.h>

CTEST(GAME, NOT_LETTERS)
{
    const char symbols_example[] = ";'.[)*&$123465789";
    int real_return;
    char word[MAX_WORD_SIZE] = "АЭтоСимвол";
    char symbols[MAX_WORD_SIZE] = "\0";

    int i, symb_exmpl_len = (int)strlen(symbols_example);

    srand(time(NULL));

    for (i = 0; i < MAX_WORD_SIZE - 1; i++) {
        symbols[i] = symbols_example[rand() % symb_exmpl_len];
    }

    symbols[MAX_WORD_SIZE - 1] = EXIT_SYMBOL;

    real_return = game(NULL, NULL, word, symbols);

    ASSERT_EQUAL(EXIT, real_return);
}

CTEST(GAME, WRONG_WORD)
{
    int real_return;
    char word[MAX_WORD_SIZE] = "Яблоко";
    char symbols[MAX_WORD_SIZE] = "ТочноНеТоСловоДа";

    real_return = game(NULL, NULL, word, symbols);

    ASSERT_EQUAL(LOSE, real_return);
}

CTEST(GAME_RIGHT_WORD, LOWERCASE)
{
    int real_return;
    char word[MAX_WORD_SIZE] = "Банан";
    char symbols[MAX_WORD_SIZE] = "банан";

    real_return = game(NULL, NULL, word, symbols);

    ASSERT_EQUAL(WIN, real_return);
}

CTEST(GAME_RIGHT_WORD, UPPERCASE)
{
    int real_return;
    char word[MAX_WORD_SIZE] = "Виноград";
    char symbols[MAX_WORD_SIZE] = "ВИНОГРАД";

    real_return = game(NULL, NULL, word, symbols);

    ASSERT_EQUAL(WIN, real_return);
}

CTEST(GAME_RIGHT_WORD, RANDCASE)
{
    int real_return;
    char word[MAX_WORD_SIZE] = "Гранат";
    char symbols[MAX_WORD_SIZE] = "гранат";

    int i, word_len = (int)(strlen(word));

    int change_case = 0;

    srand(time(NULL));

    for (i = 0; i < word_len; i += CYR_BYTE_COUNT) {
        change_case = (rand() % 2);
        if (symbols[i] == (char)CYR_FIRST_BYTE_0)
            symbols[i + 1] -= change_case * CYR_CAPS_DISLOC_0;
        else {
            if (change_case)
                symbols[i] = CYR_FIRST_BYTE_0;
            symbols[i + 1] -= change_case * CYR_CAPS_DISLOC_1;
        }
    }

    real_return = game(NULL, NULL, word, symbols);

    ASSERT_EQUAL(WIN, real_return);
}

CTEST(GAME_RIGHT_WORD, LETTERS_NOT_IN_ORDER)
{
    int real_return;
    char word[MAX_WORD_SIZE] = "Убийство";
    char symbols[MAX_WORD_SIZE] = "овтсйибУ";

    real_return = game(NULL, NULL, word, symbols);

    ASSERT_EQUAL(WIN, real_return);
}