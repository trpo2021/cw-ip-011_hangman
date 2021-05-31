#include <libhangman/constants.h>
#include <libhangman/readingfile.h>

#include <ctest.h>

CTEST(FILE, READING)
{
    int code;
    char word[MAX_WORD_SIZE] = "\0";
    char word_not_exp[MAX_WORD_SIZE] = "\0";
    code = read_random_word(word);
    ASSERT_EQUAL(code, SUCCESS);
    ASSERT_NOT_EQUAL(word_not_exp[0], word[0]);
}