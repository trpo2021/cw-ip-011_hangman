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

int print_check_res(int check_code)
{
    if (check_code != SUCCESS) {
        printf("Обнаружена ошибка.\n\n");
        printf("Код = %d\n", check_code);
        if (check_code == FILE_NOT_FOUND)
            printf("Не обнаружен файл %s", FILE_PATH);
        else if (check_code == EMPTY_FILE)
            printf("Пустой файл.");
        else if (check_code == SPACE_IN_BEGIN)
            printf("Лишний пробел в начале.");
        else if (check_code == DOUBLE_SPACE)
            printf("Повторяющийся пробел.");
        else if (check_code == SPACE_IN_END)
            printf("Лишний пробел в конце.");
        else if (check_code == FOUND_WRONG_CHAR)
            printf("Обнаружен неверный символ.");
        else if (check_code == WORD_IS_TOO_BIG)
            printf("Обнаружено слово размером 20 или больше.");
        printf("\n\n");
#ifdef DIRECTORY
        printf("Убедитесь, что существует словарь по адресу\n%s/%s\n\n",
               DIRECTORY,
               FILE_PATH);
#endif
        printf("Словарь не должен быть пустым, не должен содержать\n"
               "пробелов в начале, конце, повторяющихся пробелов и символов,\n"
               "кроме букв русского алфавита. Слова не должны содержать\n"
               "в себе больше 20 букв.\n\n");
    }
    return check_code;
}