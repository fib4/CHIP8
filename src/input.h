#pragma once

#include <SDL2/SDL.h>

#include "chip8.h"

const SDL_Scancode input_keymap[16] = {
    SDL_SCANCODE_X, //Chip-8 0
    SDL_SCANCODE_1, //Chip-8 1
    SDL_SCANCODE_2, //Chip-8 2
    SDL_SCANCODE_3, //Chip-8 3
    SDL_SCANCODE_Q, //Chip-8 4
    SDL_SCANCODE_W, //Chip-8 5
    SDL_SCANCODE_E, //Chip-8 6
    SDL_SCANCODE_A, //Chip-8 7
    SDL_SCANCODE_S, //Chip-8 8
    SDL_SCANCODE_D, //Chip-8 9
    SDL_SCANCODE_Z, //Chip-8 A
    SDL_SCANCODE_C, //Chip-8 B
    SDL_SCANCODE_4, //Chip-8 C
    SDL_SCANCODE_R, //Chip-8 D
    SDL_SCANCODE_F, //Chip-8 E
    SDL_SCANCODE_V //Chip-8 F
};

void input_handler(struct chip8 *chip8);