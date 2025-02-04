#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

bool sdl_init(App *app){

    //initialize SDL components, if anything fails return false

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Failed to initialize SDL! %s\n", SDL_GetError());
        return false;
    }

    app->window = SDL_CreateWindow("CHIP8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, 0);
    if(app->window == NULL) {
        SDL_Log("Could not create window! %s\n", SDL_GetError());
        return false;
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
    if(app->renderer == NULL) {
        SDL_Log("Failed to create renderer! %s\n", SDL_GetError());
        return false;
    }

    //everything works so return true;

    return true;
}

void sdl_stop(App *app){
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}

int main(int argc, char *argv[]){

    //initialize app
    App app = {0};

    //if sdl initialization returns falsy exit with failure
    if(!sdl_init(&app)){
    exit(EXIT_FAILURE);
    }

    SDL_Delay(3000);

    printf("terve vaan\n");

    sdl_stop(&app);
    return 0;
}