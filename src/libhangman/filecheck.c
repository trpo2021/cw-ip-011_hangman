#include "filecheck.h"

#include "constants.h"

#include <stdlib.h>

int check_exist(FILE* file)
{
    if (!file)
        return FILE_NOT_FOUND;
    return SUCCESS;
}

int check_empty(FILE* file)
{
    rewind(file);
    if (getc(file) == EOF)
        return EMPTY_FILE;
    return SUCCESS;
}

int check_space(FILE* file)
{
    int c;
    rewind(file);
    if (getc(file) == ' ')
        return SPACE_IN_BEGIN;
    rewind(file);
    while ((c = getc(file)) != EOF) {
        if (c == ' ')
            if (getc(file) == ' ')
                return DOUBLE_SPACE;
    }
    fseek(file, -1, SEEK_END);
    if (getc(file) == ' ')
        return SPACE_IN_END;
    return SUCCESS;
}

int check_symbol(FILE* file)
{
    int c, c_2nd_byte;
    rewind(file);
    while ((c = getc(file)) != EOF) {
        if (c == ' ')
            continue;
        if (c == CYR_FIRST_BYTE_0) {
            c_2nd_byte = getc(file);
            if (c_2nd_byte >= CYR_START_0 && c_2nd_byte <= CYR_END_UPPERCASE)
                continue;
            if (c_2nd_byte >= CYR_START_0 + CYR_CAPS_DISLOC_0
                && c_2nd_byte <= CYR_END_0 + CYR_CAPS_DISLOC_0)
                continue;
            if (c_2nd_byte == CYR_YO_UPPERCASE)
                continue;
            return FOUND_WRONG_CHAR;
        } else if (c == CYR_FIRST_BYTE_1) {
            c_2nd_byte = getc(file);
            if (c_2nd_byte >= CYR_START_1 && c_2nd_byte <= CYR_END_UPPERCASE)
                continue;
            if (c_2nd_byte >= CYR_START_1 + CYR_CAPS_DISLOC_1
                && c_2nd_byte <= CYR_END_UPPERCASE + CYR_CAPS_DISLOC_1)
                continue;
            if (c_2nd_byte == CYR_YO_LOWERCASE)
                continue;
            return FOUND_WRONG_CHAR;
        } else
            return FOUND_WRONG_CHAR;
    }
    return SUCCESS;
}

int check_word_size(FILE* file)
{
    int c, i;
    rewind(file);
    while ((c = getc(file)) != EOF) {
        if (c == ' ')
            i = 0;
        else
            i++;
        if (i >= MAX_WORD_SIZE - 1)
            return WORD_IS_TOO_BIG;
    }
    return SUCCESS;
}

int check(FILE* file)
{
    int code;
    if ((code = check_exist(file)) != SUCCESS)
        return code;
    if ((code = check_empty(file)) != SUCCESS)
        return code;
    if ((code = check_space(file)) != SUCCESS)
        return code;
    if ((code = check_symbol(file)) != SUCCESS)
        return code;
    if ((code = check_word_size(file)) != SUCCESS)
        return code;
    return SUCCESS;
}