#pragma once

static const int MAX_FAIL = 6;

static const int WINDOW_WIDTH = 500;
static const int WINDOW_HEIGHT = 800;

static const int SCREEN_PART_MOVE_X
        = 4; /* Насколько окно должно быть смещено от центра экрана.
                4 для четверти экрана, 2 для половины.
                Не рекоммендуется использовать значения меньше 3.
                Чтобы запускать окно в центра, ставь значение -1. */
static const int SCREEN_PART_MOVE_Y = -1;

static const char HANGMAN_TITLE[] = "HANGMAN";
static const char ICON_PATH[] = "./assets/icon.png";

static const int STATE_OK = 0;
static const int ERROR_SDL_NOT_INIT = 1;
static const int ERROR_DM_NOT_INIT = 2;
static const int ERROR_WINDOW_NOT_INIT = 3;
static const int ERROR_RENDER_NOT_INIT = 4;

static const int START_COMMAND = 0;
static const int CLOSE_COMMAND = 999;

static const int VIRTUAL_RES_X = 10;
static const int VIRTUAL_RES_Y = 16;
static const int GIB_RESIZE_LESS = 3;
static const int GIB_RESIZE_MORE = 2;

static const int RED = 255;
static const int GREEN = 255;
static const int BLUE = 255;
static const int ALPHA = 255;
static const int RED_BACK = 0;
static const int GREEN_BACK = 0;
static const int BLUE_BACK = 0;
static const int ALPHA_BACK = 0;

static const char FILE_PATH[] = "../../words.txt";
static const int MAX_WORD_SIZE = 20;