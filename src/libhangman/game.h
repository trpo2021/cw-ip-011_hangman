#pragma once

#include <SDL2/SDL.h>

/**
 * Здесь происходят основные действия игры.
 * Для теста нужно передать symbols.
 * @param renderer Двойной адрес рендера.
 * При тесте желательно передать NULL.
 *
 * @param window Двойной адрес окна.
 * При тесте желательно передать NULL.
 *
 * @param word Ссылка на массив слова,
 * которое нужно отгадать.
 *
 * @param symbols Ссылка на строку символов,
 * которые принимает программа в качестве ввода.
 * Используется для тестирования. Вне теста
 * передавать NULL.
 *
 * @return WIN при победе,
 * LOSE при проигрыше,
 * EXIT при преждевременном
 * прекращении работы.
 */
int game(
        SDL_Renderer** renderer,
        SDL_Window** window,
        char* word,
        char* symbols);