#pragma once

// Максимальное количество ошибок
static const int MAX_FAIL = 6;
// Обозначение спрятанного символа.
static const char HIDDEN_SYMBOL = '#';

//Ширина окна в пикселях.
static const int WINDOW_WIDTH = 500;
//Высота окна в пикселях.
static const int WINDOW_HEIGHT = 800;

/* Насколько окно должно быть смещено от центра экрана.
                4 для четверти экрана, 2 для половины.
                Не рекоммендуется использовать значения меньше 3.
                Чтобы запускать окно в центра, ставь значение -1. */
static const int SCREEN_PART_MOVE_X = 4;
static const int SCREEN_PART_MOVE_Y = -1;

// Заголовок окна.
static const char HANGMAN_TITLE[] = "HANGMAN";
// Путь к иконке.
static const char ICON_PATH[] = "./assets/icon.png";

//Коды результата иницилизации SDL.
static const int STATE_OK = 0;
static const int ERROR_SDL_NOT_INIT = 1;
static const int ERROR_DM_NOT_INIT = 2;
static const int ERROR_WINDOW_NOT_INIT = 3;
static const int ERROR_RENDER_NOT_INIT = 4;

// Коды инициализации/отключения SDL.
static const int START_COMMAND = 0;
static const int CLOSE_COMMAND = 999;

/**
 * Условно делим окно на 16*10 (VIRTUAL_RES_Y*VIRTUAL_RES_X)
 * частей, по ним строим виселицу и части тела.
 */
static const int VIRTUAL_RES_X = 10;
static const int VIRTUAL_RES_Y = 16;

// Изменение размера виселицы.
static const int GIB_RESIZE_LESS = 3;
static const int GIB_RESIZE_MORE = 2;

// Координаты частей виселицы и тела для отрисовки.
static const int POST_X1 = WINDOW_WIDTH / VIRTUAL_RES_X;
static const int POST_Y1 = WINDOW_HEIGHT / (VIRTUAL_RES_Y / 2);
static const int POST_W
        = GIB_RESIZE_MORE * WINDOW_WIDTH / (VIRTUAL_RES_X * GIB_RESIZE_LESS);
static const int POST_H = 7 * WINDOW_HEIGHT / (VIRTUAL_RES_Y / 2);
static const int POST_X2 = POST_X1 + POST_W;
static const int POST_Y2 = POST_Y1 + POST_H;

static const int PLANK_X1 = POST_X2;
static const int PLANK_Y1 = POST_Y1;
static const int PLANK_W = 3 * WINDOW_WIDTH / (VIRTUAL_RES_X / 2)
        + (WINDOW_WIDTH / VIRTUAL_RES_X - POST_W);
static const int PLANK_H
        = GIB_RESIZE_MORE * WINDOW_HEIGHT / (VIRTUAL_RES_Y * GIB_RESIZE_LESS);
static const int PLANK_X2 = PLANK_X1 + PLANK_W;
static const int PLANK_Y2 = PLANK_Y1 + PLANK_H;

static const int HEAD_X
        = PLANK_X1 + GIB_RESIZE_MORE * PLANK_W / GIB_RESIZE_LESS;
static const int HEAD_Y = PLANK_Y2 + 4 * WINDOW_HEIGHT / VIRTUAL_RES_Y;
static const int HEAD_RAD = WINDOW_HEIGHT / VIRTUAL_RES_Y;

static const int BODY_X = HEAD_X;
static const int BODY_RAD_X = GIB_RESIZE_MORE * HEAD_RAD / GIB_RESIZE_LESS;
static const int BODY_RAD_Y = GIB_RESIZE_MORE * HEAD_RAD;
static const int BODY_Y = HEAD_Y + HEAD_RAD + BODY_RAD_Y;

//Цвет рисунка.
static const int RED = 255;
static const int GREEN = 255;
static const int BLUE = 255;
static const int ALPHA = 255;

//Цвет фона.
static const int RED_BACK = 0;
static const int GREEN_BACK = 0;
static const int BLUE_BACK = 0;
static const int ALPHA_BACK = 0;

// Путь к файлу и макс. размер слова.
static const char FILE_PATH[] = "words.txt";
static const int MAX_WORD_SIZE = 41;

// Коды результата проверки файла.
static const int SUCCESS = 5;
static const int FILE_NOT_FOUND = 6;
static const int EMPTY_FILE = 7;
static const int SPACE_IN_BEGIN = 8;
static const int DOUBLE_SPACE = 9;
static const int SPACE_IN_END = 10;
static const int FOUND_WRONG_CHAR = 11;
static const int WORD_IS_TOO_BIG = 12;

// CYR - CYRILLIC
static const int CYR_BYTE_COUNT = 2;
static const int CYR_FIRST_BYTE_0 = 0xD0;
static const int CYR_FIRST_BYTE_1 = 0xD1;
static const int CYR_START_0 = 0x90;
static const int CYR_START_1 = 0xA0;
static const int CYR_END_0 = 0x9F;
static const int CYR_END_UPPERCASE = 0xAF;
static const int CYR_CAPS_DISLOC_0 = 0xB0 - CYR_START_0;
static const int CYR_CAPS_DISLOC_1 = 0x80 - CYR_START_1;
static const int CYR_YO_UPPERCASE = 0x81;
static const int CYR_YO_LOWERCASE = 0x91;

//Русский алфавит для проверка повтора буквы.
static const int ALPHABET_SIZE = 33;
static const int ALPHABET_D0_DISLOC = CYR_START_0 + CYR_CAPS_DISLOC_0;
static const int ALPHABET_D1_DISLOC
        = CYR_START_0 - CYR_START_1 + CYR_START_1 + CYR_CAPS_DISLOC_1;
static const int ALPHABET_YO_DISLOC
        = CYR_START_0 - CYR_START_1 + CYR_YO_LOWERCASE;

// Коды результата игры.
// EXIT - преждевременный выход.
static const int WIN = 13;
static const int LOSE = 14;
static const int EXIT = 15;