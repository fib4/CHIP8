#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

struct graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;
};

bool graphics_sdl_init(struct graphics * graphics);
void graphics_draw_graphics(struct graphics * graphics);
void graphics_clear_screen(struct graphics * graphics);
void graphics_sdl_stop(struct graphics * graphics);