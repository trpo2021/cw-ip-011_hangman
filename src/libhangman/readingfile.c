#include "readingfile.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int readingfile(char* s)
{
    FILE* p;
    srand(time(NULL));
    p = fopen(FILE_PATH, "r");
    if (p == NULL)
        return FILE_NOT_FOUND;
    char a;
    int num = 0, i, j;
    while ((a = getc(p)) != EOF)
        if (a == ' ')
            num++;
    num++;
    char** words;
    words = (char**)malloc(num * sizeof(char*));
    for (i = 0; i < num; i++)
        words[i] = (char*)malloc(MAX_WORD_SIZE * sizeof(char));
    rewind(p);
    i = j = 0;
    while ((a = getc(p)) != EOF) {
        if (a == ' ') {
            words[i][j] = '\0';
            i++;
            j = 0;
            (a = getc(p));
        }
        if (a == '\n')
            (a = getc(p));
        words[i][j] = a;
        j++;
    }
    words[i][j] = '\0';
    fclose(p);
    strcpy(s, words[rand() % num]);
    for (i = 0; i < num; i++)
        free(words[i]);
    free(words);
    return SUCCES_RF;
}