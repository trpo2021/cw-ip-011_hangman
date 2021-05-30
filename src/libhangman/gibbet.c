#include "gibbet.h"

#include "bodyparts.h"
#include "constants.h"
#include "define_sizes.h"
#include "gibbet_init.h"

#include <stdio.h>

void add_part(SDL_Renderer* renderer, int attempt)
{
    static rect post = {-1, 0, 0, 0, 0, 0};
    static rect plank;
    static cir head;
    static ell body;
    static line hand1;
    static line hand2;
    static line leg1;
    static line leg2;

    if (post.x_1 == -1)
        define_sizes(&post, &plank, &head, &body, &hand1, &hand2, &leg1, &leg2);

    if (attempt == CLOSE_COMMAND)
        return;
    if (attempt == START_COMMAND) {
        build_gibbet(renderer, &post, &plank, &head);
        SDL_RenderPresent(renderer);
        return;
    }

    // Полность очищаем рендер и заного строим виселицу.
    SDL_SetRenderDrawColor(
            renderer, RED_BACK, GREEN_BACK, BLUE_BACK, ALPHA_BACK);
    SDL_RenderClear(renderer);

    build_gibbet(renderer, &post, &plank, &head);
    switch (attempt) {
    case 6:
        add_leg2(renderer, &leg2);
        // FALLTHROUGH
    case 5:
        add_leg1(renderer, &leg1);
        // FALLTHROUGH
    case 4:
        add_hand2(renderer, &hand2);
        // FALLTHROUGH
    case 3:
        add_hand1(renderer, &hand1);
        // FALLTHROUGH
    case 2:
        add_body(renderer, &body);
        // FALLTHROUGH
    case 1:
        add_head(renderer, &head);
        // FALLTHROUGH
    default:
        SDL_RenderPresent(renderer);
    }
}

/**
 * Главная функция для создания, изменения и закрытия окна с виселицей.
 * @param attempt Число неудачных попыток. Передать START_COMMAND
 * при запуске программы, CLOSE_COMMAND при её закрытии, или числа
 * от 1 до 6 для соответствующей неудачной попытки.
 * Число попыток остаётся неизменным после вызова функции.
 * @param renderer Двойная ссылка рендера.
 * @param window Двойная ссылка окна.
 * @return STATE_OK при успешном открытии/рисунке части тела/закрытии.
 * Код одной из ошибок, указанных в constants.h при неудаче.
 */
int gibbet(int attempt, SDL_Renderer** renderer, SDL_Window** window)
{
    int init_code = STATE_OK;

    if (*renderer == NULL || *window == NULL)
        init_code = initialize(renderer, window);

    if (init_code != STATE_OK) {
        close(renderer, window, init_code);
        return init_code;
    }

    add_part(*renderer, attempt);

    if (attempt == CLOSE_COMMAND)
        close(renderer, window, init_code);

    return STATE_OK;
}