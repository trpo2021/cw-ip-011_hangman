#include "readingfile.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

void readingfile()
{
    FILE* p;
    p = fopen(FILE_PATH, "r");
    char a;
    int num = 0, i;
    while ((a = getc(p)) != EOF) {
        if (a == ' ')
            num++;
    }
    num++;
    char** Words;
    Words = (char**)malloc(num * sizeof(char*));
    for (i = 0; i < num; i++) {
        Words[i] = (char*)malloc(MAX_WORD_SIZE * sizeof(char));
    }
    fclose(p);
}