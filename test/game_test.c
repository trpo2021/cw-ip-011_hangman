#include "test_constants.h"

#include <libhangman/constants.h>
#include <libhangman/game.h>
#include <libhangman/readingfile.h>

#include <SDL2/SDL.h>
#include <ctest.h>
#include <time.h>

CTEST(GAME, WRONG_WORD)
{
    int real_return;
    char word[MAX_WORD_SIZE] = "Apple";
    char symbols[MAX_WORD_SIZE] = "QwErtYuIopAsd";

    srand(time(NULL));
    real_return = game(word, symbols);

    ASSERT_EQUAL(LOSE, real_return);
}

CTEST(GAME, RIGHT_WORD)
{
    int real_return;
    char word[MAX_WORD_SIZE] = "Banana";
    char symbols[MAX_WORD_SIZE] = "bAnANa";

    real_return = game(word, symbols);

    ASSERT_EQUAL(WIN, real_return);
}

CTEST(GAME, NOT_LETTERS)
{
    const char symbols_example[] = ";'.[)*&$123465789";
    int i, real_return;
    char word[MAX_WORD_SIZE] = "IsThisASymbol";
    char symbols[MAX_WORD_SIZE] = "\0";

    srand(time(NULL));

    for (i = 0; i < MAX_WORD_SIZE - 1; i++) {
        symbols[i] = symbols_example[rand() % (int)strlen(symbols_example)];
    }

    symbols[MAX_WORD_SIZE - 1] = HIDDEN_SYMBOL;

    real_return = game(word, symbols);

    ASSERT_EQUAL(EXIT, real_return);
}