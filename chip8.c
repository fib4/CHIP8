#include "chip8.h"
#include <stdio.h>

void chip8_load_rom(struct chip8 *chip8, const char *filename) {
    FILE * rom;
    rom = fopen(filename, "rb");

    if(rom == NULL){
        printf("Error opening rom");
    }

    fseek(rom, 0, SEEK_END);
    size_t rom_size = ftell(rom);
    
    if(rom_size > (4096 - 0x200)){
        printf("Too big rom");
    }

    rewind(rom);
    fread(&chip8->memory[0x200], rom_size, 1, rom);

    fclose(rom);

    chip8->pc = 0x200;
}

void chip8_execute(struct chip8 *chip8){
    uint16_t opcode = ((chip8->memory[chip8->pc] << 8) | chip8->memory[chip8->pc + 1]);

    chip8->pc += 2;

    uint16_t instruction = (opcode & 0xf000) >> 12;
    uint16_t x = (opcode & 0x0f00) >> 8;
    uint16_t y = (opcode & 0x00f0) >> 4;
    uint16_t n = opcode & 0x000f;
    uint16_t nn = opcode & 0x00ff;
    uint16_t nnn = opcode & 0x0fff;

    switch (instruction) {
        case 0x0:
            break;
        case 0x1:
            break;
        case 0x2:
            break;
        case 0x3:
            break;
        case 0x4:
            break;
        case 0x5:
            break;
        case 0x6:
            break;
        case 0x7:
            break;
        case 0x8:
            break;
        case 0x9:
            break;
        case 0xA:
            break;
        case 0xB:
            break;
        case 0xC:
            break;
        case 0xD:
            break;
        case 0xE:
            break;
        case 0xF:
            break;
    }
}