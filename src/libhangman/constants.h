#pragma once

// Максимальное количество ошибок
const int MAX_FAIL = 6;
// Обозначение спрятанного символа.
const char HIDDEN_SYMBOL = '#';

//Ширина окна в пикселях.
const int WINDOW_WIDTH = 500;
//Высота окна в пикселях.
const int WINDOW_HEIGHT = 800;

/* Насколько окно должно быть смещено от центра экрана.
                4 для четверти экрана, 2 для половины.
                Не рекоммендуется использовать значения меньше 3.
                Чтобы запускать окно в центра, ставь значение -1. */
const int SCREEN_PART_MOVE_X = 4;
const int SCREEN_PART_MOVE_Y = -1;

// Заголовок окна.
const char HANGMAN_TITLE[] = "HANGMAN";
// Путь к иконке.
const char ICON_PATH[] = "./assets/icon.png";

//Коды результата иницилизации SDL.
const int STATE_OK = 0;
const int ERROR_SDL_NOT_INIT = 1;
const int ERROR_DM_NOT_INIT = 2;
const int ERROR_WINDOW_NOT_INIT = 3;
const int ERROR_RENDER_NOT_INIT = 4;

// Коды инициализации/отключения SDL.
const int START_COMMAND = 0;
const int CLOSE_COMMAND = 999;

/**
 * Условно делим окно на 16*10 (VIRTUAL_RES_Y*VIRTUAL_RES_X)
 * частей, по ним строим виселицу и части тела.
 */
const int VIRTUAL_RES_X = 10;
const int VIRTUAL_RES_Y = 16;

// Изменение размера виселицы.
const int GIB_RESIZE_LESS = 3;
const int GIB_RESIZE_MORE = 2;

// Координаты частей виселицы и тела для отрисовки.
const int POST_X1 = WINDOW_WIDTH / VIRTUAL_RES_X;
const int POST_Y1 = WINDOW_HEIGHT / (VIRTUAL_RES_Y / 2);
const int POST_W
        = GIB_RESIZE_MORE * WINDOW_WIDTH / (VIRTUAL_RES_X * GIB_RESIZE_LESS);
const int POST_H = 7 * WINDOW_HEIGHT / (VIRTUAL_RES_Y / 2);
const int POST_X2 = POST_X1 + POST_W;
const int POST_Y2 = POST_Y1 + POST_H;

const int PLANK_X1 = POST_X2;
const int PLANK_Y1 = POST_Y1;
const int PLANK_W = 3 * WINDOW_WIDTH / (VIRTUAL_RES_X / 2)
        + (WINDOW_WIDTH / VIRTUAL_RES_X - POST_W);
const int PLANK_H
        = GIB_RESIZE_MORE * WINDOW_HEIGHT / (VIRTUAL_RES_Y * GIB_RESIZE_LESS);
const int PLANK_X2 = PLANK_X1 + PLANK_W;
const int PLANK_Y2 = PLANK_Y1 + PLANK_H;

const int HEAD_X = PLANK_X1 + GIB_RESIZE_MORE * PLANK_W / GIB_RESIZE_LESS;
const int HEAD_Y = PLANK_Y2 + 4 * WINDOW_HEIGHT / VIRTUAL_RES_Y;
const int HEAD_RAD = WINDOW_HEIGHT / VIRTUAL_RES_Y;

const int BODY_X = HEAD_X;
const int BODY_RAD_X = GIB_RESIZE_MORE * HEAD_RAD / GIB_RESIZE_LESS;
const int BODY_RAD_Y = GIB_RESIZE_MORE * HEAD_RAD;
const int BODY_Y = HEAD_Y + HEAD_RAD + BODY_RAD_Y;

//Цвет рисунка.
const int RED = 255;
const int GREEN = 255;
const int BLUE = 255;
const int ALPHA = 255;

//Цвет фона.
const int RED_BACK = 0;
const int GREEN_BACK = 0;
const int BLUE_BACK = 0;
const int ALPHA_BACK = 0;

// Путь к файлу и макс. размер слова.
const char FILE_PATH[] = "words.txt";
const int MAX_WORD_SIZE = 41;

// Коды результата проверки файла.
const int SUCCESS = 5;
const int FILE_NOT_FOUND = 6;
const int EMPTY_FILE = 7;
const int SPACE_IN_BEGIN = 8;
const int DOUBLE_SPACE = 9;
const int SPACE_IN_END = 10;
const int FOUND_WRONG_CHAR = 11;
const int WORD_IS_TOO_BIG = 12;

// CYR - CYRILLIC
const int CYR_BYTE_COUNT = 2;
const int CYR_FIRST_BYTE_0 = 0xD0;
const int CYR_FIRST_BYTE_1 = 0xD1;
const int CYR_START_0 = 0x90;
const int CYR_START_1 = 0xA0;
const int CYR_END_0 = 0x9F;
const int CYR_END_UPPERCASE = 0xAF;
const int CYR_CAPS_DISLOC_0 = 0xB0 - CYR_START_0;
const int CYR_CAPS_DISLOC_1 = 0x80 - CYR_START_1;
const int CYR_YO_UPPERCASE = 0x81;
const int CYR_YO_LOWERCASE = 0x91;

//Русский алфавит для проверка повтора буквы.
const int ALPHABET_SIZE = 33;
const int ALPHABET_D0_DISLOC = CYR_START_0 + CYR_CAPS_DISLOC_0;
const int ALPHABET_D1_DISLOC
        = CYR_START_0 - CYR_START_1 + CYR_START_1 + CYR_CAPS_DISLOC_1;
const int ALPHABET_YO_DISLOC = CYR_START_0 - CYR_START_1 + CYR_YO_LOWERCASE;

// Коды результата игры.
// EXIT - преждевременный выход.
const int WIN = 13;
const int LOSE = 14;
const int EXIT = 15;

// Какой сивол нужно ввести для выхода.
const char EXIT_SYMBOL = '0';