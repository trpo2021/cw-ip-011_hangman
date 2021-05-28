#include "readingfile.h"
#include "constants.h"
#include "filecheck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int count_words(FILE* p)
{
    char a;
    int count = 1;
    rewind(p);
    while ((a = getc(p)) != EOF)
        if (a == ' ')
            count++;
    return count;
}

void read_nth_word(FILE* p, char* s, int n)
{
    char a;
    char word[MAX_WORD_SIZE];
    int i = 1;
    rewind(p);
    while (i != n) {
        a = getc(p);
        if (a == ' ')
            i++;
    }
    i = 0;
    while ((a = getc(p)) != EOF) {
        if (a == ' ')
            break;
        word[i] = a;
        i++;
    }
    word[i] = '\0';
    strcpy(s, word);
}

int read_random_word(char* s)
{
    FILE* p;
    int count, n, code;
    p = fopen(FILE_PATH, "r");
    code = check(p);
    if (code != SUCCESS)
        return code;
    srand(time(NULL));
    if (p == NULL)
        return FILE_NOT_FOUND;
    count = count_words(p);
    n = 1 + rand() % count;
    read_nth_word(p, s, n);
    fclose(p);
    return SUCCESS;
}