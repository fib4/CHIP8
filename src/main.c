#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <time.h>

#include "chip8.h"
#include "graphics.h"
#include "input.h"

int main(int argc, char *argv[]){

    printf("terve");

    clock_t frame_start = 0;
    clock_t frame_end = 0;
    double delta, accumulator;

    //initialize sdl_window
    struct graphics graphics = {0};

    //initialize chip8
    struct chip8 chip8;
    chip8_init(&chip8);

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

    /*
    * CHIP-8 is not a physical system but an interpreted language, meaning it has
    * no inherent clock speed. Execution speed historically depended on the
    * hardware running the interpreter (e.g. COSMAC VIP vs. modern computers).
    * 
    * In a proper implementation users should be able to configure
    * instructions per frame count to achieve the best performance for different programs
    * 
    * Currently this implementation defines the instructions per frame value in the source
    * code as a temporary solution until user-configurable timing is implemented
    */

    while(chip8.state != STOPPED){

        input_handler(&chip8);

        delta = (double)(frame_end - frame_start) / CLOCKS_PER_SEC;
        frame_start = clock();
        accumulator += delta;
        while(accumulator >= 0.0167){
            //execute 11 instructions per frame
            for(uint8_t i = 0; i < 11; ++i){
                chip8_execute(&chip8);
            }
            graphics_draw_graphics(&graphics, &chip8);
            accumulator -= 0.0167;
        }
        frame_end = clock();
    }

    printf("terve vaan\n");

    graphics_sdl_stop(&graphics);
    return 0;
}