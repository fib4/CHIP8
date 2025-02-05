#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "chip8.h"

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} Sdl_window;

bool sdl_init(Sdl_window *sdl_window){

    //initialize SDL components, if anything fails return false

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Failed to initialize SDL! %s\n", SDL_GetError());
        return false;
    }

    sdl_window->window = SDL_CreateWindow("CHIP8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, 0);
    if(sdl_window->window == NULL) {
        SDL_Log("Could not create window! %s\n", SDL_GetError());
        return false;
    }

    sdl_window->renderer = SDL_CreateRenderer(sdl_window->window, -1, SDL_RENDERER_ACCELERATED);
    if(sdl_window->renderer == NULL) {
        SDL_Log("Failed to create renderer! %s\n", SDL_GetError());
        return false;
    }

    //everything works so return true;

    return true;
}

void sdl_stop(Sdl_window *sdl_window){
    SDL_DestroyRenderer(sdl_window->renderer);
    SDL_DestroyWindow(sdl_window->window);
    SDL_Quit();
}

void inputHandler(struct chip8 *chip8){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                chip8->state = STOPPED;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode){
                    //when escape is pressed, set sdl_window state to stop
                    case SDL_SCANCODE_ESCAPE:
                        chip8->state = STOPPED;
                        break;

                    //CHIP 8 key mappings
                    case SDL_SCANCODE_1:
                        //CHIP 8 key 1
                        printf("1\n");
                        break;
                    case SDL_SCANCODE_2:
                        //CHIP 8 key 2
                        printf("2\n");
                        break;
                    case SDL_SCANCODE_3:
                        //CHIP 8 key 3
                        printf("3\n");
                        break;
                    case SDL_SCANCODE_4:
                        //CHIP 8 key C
                        printf("C\n");
                        break;
                    case SDL_SCANCODE_Q:
                        //CHIP 8 key 4
                        printf("4\n");
                        break;
                    case SDL_SCANCODE_W:
                        //CHIP 8 key 5
                        printf("5\n");
                        break;
                    case SDL_SCANCODE_E:
                        //CHIP 8 key 6
                        printf("6\n");
                        break;
                    case SDL_SCANCODE_R:
                        //CHIP 8 key D
                        printf("D\n");
                        break;
                    case SDL_SCANCODE_A:
                        //CHIP 8 key 7
                        printf("7\n");
                        break;
                    case SDL_SCANCODE_S:
                        //CHIP 8 key 8
                        printf("8\n");
                        break;
                    case SDL_SCANCODE_D:
                        //CHIP 8 key 9
                        printf("9\n");
                        break;
                    case SDL_SCANCODE_F:    
                        //CHIP 8 key E
                        printf("E\n");
                        break;
                    case SDL_SCANCODE_Z:
                        //CHIP 8 key A
                        printf("A\n");
                        break;
                    case SDL_SCANCODE_X:
                        //CHIP 8 key 0
                        printf("0\n");
                        break;
                    case SDL_SCANCODE_C:
                        //CHIP 8 key B
                        printf("B\n");
                        break;
                    case SDL_SCANCODE_V:
                        //CHIP 8 key F
                        printf("F\n");
                        break;

                    default:
                        break;
                }
        }
    }
}

int main(int argc, char *argv[]){

    //initialize sdl_window
    Sdl_window sdl_window = {0};

    //initialize chip8
    struct chip8 chip8 = {0};

    //if sdl initialization returns falsy exit with failure
    if(!sdl_init(&sdl_window)){
        exit(EXIT_FAILURE);
    }

    chip8.state = RUNNING;

    while(chip8.state != STOPPED){
        inputHandler(&chip8);
        
        SDL_Delay(16); //delay for ~60hz/60fps
    }

    printf("terve vaan\n");

    sdl_stop(&sdl_window);
    return 0;
}