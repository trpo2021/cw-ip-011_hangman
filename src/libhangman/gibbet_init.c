#include "gibbet_init.h"

#include "constants.h"

#include <SDL2/SDL_image.h>

/**
 * Инициализирует SDL и открывает окно с виселицей.
 * @param renderer Двойной адрес рендера.
 * @param window Двойной адрес окна.
 * @return STATE_OK при успешной инициализации
 * или один из кодов ошибок, указанных в
 * constants.h
 */
int initialize(SDL_Renderer** renderer, SDL_Window** window)
{
    SDL_DisplayMode DM; // Используется для определения разрешения экрана
    SDL_Surface* icon;  // Иконка окна с виселицей.
    int window_disloc_x,
            window_disloc_y; // Отколнение окна от центра экрана в пикселях
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        // Инициализация SDL, проверка на ошибку.
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return ERROR_SDL_NOT_INIT;
    }
    if (SDL_GetDesktopDisplayMode(0, &DM) != 0) {
        // Получение режима дисплея, проверка на ошибку.
        SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        return ERROR_DM_NOT_INIT;
    }
    if (SCREEN_PART_MOVE_X > 0) // Расчёт отклонения окна от центра в пикселях.
        window_disloc_x = DM.w / SCREEN_PART_MOVE_X;
    else
        window_disloc_x = 0;
    if (SCREEN_PART_MOVE_Y > 0)
        window_disloc_y = DM.h / SCREEN_PART_MOVE_Y;
    else
        window_disloc_y = 0;
    if (!(*window = SDL_CreateWindow( // Создание окна, проверка на ошибку.
                  HANGMAN_TITLE,
                  DM.w / 2 - WINDOW_WIDTH / 2 + window_disloc_x,
                  DM.h / 2 - WINDOW_HEIGHT / 2 + window_disloc_y,
                  WINDOW_WIDTH,
                  WINDOW_HEIGHT,
                  0))) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        return ERROR_WINDOW_NOT_INIT;
    }
    if (!(icon = IMG_Load(ICON_PATH))) { // Получение изображения для иконки,
                                         // проверка на ошибку.
        SDL_Log("Not critical: IMG_Load failed: %s", SDL_GetError());
    }
    SDL_SetWindowIcon(*window, icon); // Присваиваем окну иконку.
    if (!(*renderer = SDL_CreateRenderer(*window, -1, 0))) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        return ERROR_RENDER_NOT_INIT;
    }
    SDL_SetRenderDrawColor(*renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    return STATE_OK;
}

/**
 * Отключает рендер, окно и SDL.
 * @param renderer Двойной адрес рендера.
 * @param window Двойной адрес окна.
 * @param code Код, возвращённый функцией инициализации.
 */
void close(SDL_Renderer** renderer, SDL_Window** window, int code)
{
    if (*renderer != NULL) {
        SDL_DestroyRenderer(*renderer);
        *renderer = NULL;
    }
    if (*window != NULL) {
        SDL_DestroyWindow(*window);
        *window = NULL;
    }
    if (code != ERROR_SDL_NOT_INIT)
        SDL_Quit();
}