#include "input.h"

void input_handler(struct chip8 *chip8){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT)
            chip8->state = STOPPED;

    uint8_t *keyboard_state = SDL_GetKeyboardState(NULL);

    for(uint8_t i = 0; i < 16; ++i){
        chip8->input[i] = keyboard_state[input_keymap[i]] ? true : false;
    }
}