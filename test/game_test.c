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
    char word[MAX_WORD_SIZE] = "IsThisASymbol";
    char symbols[MAX_WORD_SIZE] = "\0";

    int i, symb_exmpl_len = (int)strlen(symbols_example);

    srand(time(NULL));

    for (i = 0; i < MAX_WORD_SIZE - 1; i++) {
        symbols[i] = symbols_example[rand() % symb_exmpl_len];
    }

    symbols[MAX_WORD_SIZE - 1] = HIDDEN_SYMBOL;

    real_return = game(NULL, NULL, word, symbols);

    ASSERT_EQUAL(EXIT, real_return);
}

CTEST(GAME, WRONG_WORD)
{
    int real_return;
    char word[MAX_WORD_SIZE] = "Apple";
    char symbols[MAX_WORD_SIZE] = "QwErtYuIopAsd";

    real_return = game(NULL, NULL, word, symbols);

    ASSERT_EQUAL(LOSE, real_return);
}

CTEST(GAME_RIGHT_WORD, LOWERCASE)
{
    int real_return;
    char word[MAX_WORD_SIZE] = "Banana";
    char symbols[MAX_WORD_SIZE] = "banana";

    real_return = game(NULL, NULL, word, symbols);

    ASSERT_EQUAL(WIN, real_return);
}

CTEST(GAME_RIGHT_WORD, UPPERCASE)
{
    int real_return;
    char word[MAX_WORD_SIZE] = "Grapes";
    char symbols[MAX_WORD_SIZE] = "GRAPES";

    real_return = game(NULL, NULL, word, symbols);

    ASSERT_EQUAL(WIN, real_return);
}

CTEST(GAME_RIGHT_WORD, RANDCASE)
{
    int real_return;
    char word[MAX_WORD_SIZE] = "Pomegranate";
    char symbols[MAX_WORD_SIZE] = "pomegranate";

    int i, word_len = (int)(strlen(word));

    srand(time(NULL));

    for (i = 0; i < word_len; i++) {
        symbols[i] -= (rand() % 2) * ASCII_CAPS_DISLOC;
    }

    real_return = game(NULL, NULL, word, symbols);

    ASSERT_EQUAL(WIN, real_return);
}

CTEST(GAME_RIGHT_WORD, LETTERS_NOT_IN_ORDER)
{
    int real_return;
    char word[MAX_WORD_SIZE] = "Murder";
    char symbols[MAX_WORD_SIZE] = "redruM";

    real_return = game(NULL, NULL, word, symbols);

    ASSERT_EQUAL(WIN, real_return);
}