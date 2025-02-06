#include "chip8.h"
#include <stdio.h>

#define FONTSET_SIZE 80

uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void chip8_init(struct chip8 *chip8) {
    memset(chip8, 0, sizeof(*chip8));
    memcpy(&chip8->memory[0x050], fontset, FONTSET_SIZE);
}

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
    chip8->state = RUNNING;

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
            switch(nn) {
                case 0xe0:
                    chip8->state = CLEAR;
            }
            break;
        case 0x1:
            chip8->pc = nnn;
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
            chip8->v[x] = nn;
            break;
        case 0x7:
            chip8->v[x] += nn;
            break;
        case 0x8:
            break;
        case 0x9:
            break;
        case 0xA:
            chip8->i = nnn;
            break;
        case 0xB:
            break;
        case 0xC:
            break;
        case 0xD:
            chip8_diplay_framebuffer(chip8, chip8->v[x] % 64, chip8->v[y] % 32, n);
            break;
        case 0xE:
            break;
        case 0xF:
            break;
    }
}

void chip8_diplay_framebuffer(struct chip8 * chip8, uint8_t x, uint8_t y, uint16_t n){
    chip8->v[0xF] = 0; //set flag register to 0
    for(int i = 0; i < n; ++i){

        if((y  + i) > 32) //if y coordinate reaches bottom of the screen then stop
            break;

        //go through n bytes starting from memory address at register i
        uint8_t row = chip8->memory[chip8->i + i];

        //for every bit in row byte variable check if 0 or 1
        for(int j = 0; j < 8; ++j){
            if((x + j) > 64)
                break;
            if(row & (1 << (7 - j))){
                //if pixel already on, set flag register
                if(chip8->display[y + i][x + j]){
                    chip8->v[0xF] = 1;
                }
                //flip the value of pixel
                chip8->display[y + i][x + j] = !chip8->display[y + i][x + j];
            }
        }
    }
    chip8->state = DRAW;
}