#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

enum state {
    RUNNING,
    DRAW,
    CLEAR,
    PAUSED,
    STOPPED
};

struct chip8 {
    uint8_t v[16]; //16 8-bit registers
    uint8_t memory[4096]; //4KB memory
    bool display[32][64]; //display pixels on/off
    uint16_t pc; //16-bit program counter
    uint16_t i; //16-bit index register
    uint16_t stack[16]; //stack can store 16 pc addresses
    uint8_t sp; //stack pointer

    enum state state;
};

void chip8_init(struct chip8 *chip8);

void chip8_load_rom(struct chip8 *chip8, const char *filename); //function to load rom file into memory

void chip8_execute(struct chip8 *chip8);

void chip8_diplay_framebuffer(struct chip8 * chip8, uint8_t x, uint8_t y, uint16_t n);