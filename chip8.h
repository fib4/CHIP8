#pragma once

#include <stdint.h>

enum state {
    RUNNING,
    PAUSED,
    STOPPED
};

struct chip8 {
    uint8_t V[16]; //16 8-bit registers
    uint8_t memory[4096]; //4KB memory
    bool display[64*32]; //display pixels on/off
    uint16_t pc; //16-bit program counter
    uint16_t i; //16-bit index register
    uint16_t stack[16]; //stack can store 16 pc addresses
    uint8_t sp; //stack pointer

    enum state state;
};

void chip8_load_rom(struct chip8 *chip8, const char *filename); //function to load rom file into memory

