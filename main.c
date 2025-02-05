#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "chip8.h"
#include "graphics.h"

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
    struct graphics graphics = {0};

    //initialize chip8
    struct chip8 chip8 = {0};

    //if sdl initialization returns falsy exit with failure
    if(!graphics_sdl_init(&graphics)){
        exit(EXIT_FAILURE);
    }


    //only one argument allowed
    if(argc > 2){
        exit(EXIT_FAILURE);
    }

    //load rom from path given in argument
    chip8_load_rom(&chip8, argv[1]);

    chip8.state = RUNNING;

    while(chip8.state != STOPPED){

        chip8_execute(&chip8);
        inputHandler(&chip8);
        
        SDL_Delay(16); //delay for ~60hz/60fps
    }

    printf("terve vaan\n");

    graphics_sdl_stop(&graphics);
    return 0;
}