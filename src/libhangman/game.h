#pragma once

#include <SDL2/SDL.h>

/**
 * Здесь происходят основные действия игры.
 * Для теста нужно передать symbols.
 * @param renderer Двойной адрес рендера.
 *
 * @param window Двойной адрес окна.
 *
 * @param word Ссылка на массив слова,
 * которое нужно отгадать.
 *
 * @param symbols Ссылка на строку символов,
 * которые принимает программа в качестве ввода.
 * Используется для тестирования. Вне теста
 * передавать NULL.
 *
 * @return SUCCESS_GAME
 *
 * При тесте:
 * WIN при победе,
 * LOSE при проигрыше,
 * LEAVE_TOO_SOON при преждевременном
 * прекращении работы.
 * Значения им присваиваются в константах теста.
 */

#ifndef TEST

int game(SDL_Renderer** renderer, SDL_Window** window, char* word);

#else

int game(char* word, char* symbols);

#endif
