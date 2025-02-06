#include "graphics.h"

bool graphics_sdl_init(struct graphics *graphics){

    //initialize SDL components, if anything fails return false

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Failed to initialize SDL! %s\n", SDL_GetError());
        return false;
    }

    graphics->window = SDL_CreateWindow("CHIP8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, 0);
    if(graphics->window == NULL) {
        SDL_Log("Could not create window! %s\n", SDL_GetError());
        return false;
    }

    graphics->renderer = SDL_CreateRenderer(graphics->window, -1, SDL_RENDERER_ACCELERATED);
    if(graphics->renderer == NULL) {
        SDL_Log("Failed to create renderer! %s\n", SDL_GetError());
        return false;
    }

    //everything works so return true;

    return true;
}

void graphics_draw_graphics(struct graphics * graphics, struct chip8 * chip8){
    SDL_Rect pixel = {0,0,10,10};

    for(int i = 0; i < 32; ++i){
        for(int j = 0; j < 64; ++j){
            pixel.x = j * 10;
            pixel.y = i * 10;

            if(chip8->display[i][j]){
                SDL_SetRenderDrawColor(graphics->renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(graphics->renderer, &pixel);
            } else{
                SDL_SetRenderDrawColor(graphics->renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(graphics->renderer, &pixel);
            };
        }
    }

    SDL_RenderPresent(graphics->renderer);
}

void graphics_clear_screen(struct graphics *graphics){
    SDL_SetRenderDrawColor(graphics->renderer, 0, 0, 0, 255);
    SDL_RenderClear(graphics->renderer);
    SDL_RenderPresent(graphics->renderer);
}

void graphics_sdl_stop(struct graphics *graphics){
    SDL_DestroyRenderer(graphics->renderer);
    SDL_DestroyWindow(graphics->window);
    SDL_Quit();
}