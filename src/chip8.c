#include "chip8.h"
#include <stdio.h>
#include <stdlib.h>

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
                case 0xe0: //CLS
                    memset(chip8->display, 0, sizeof(chip8->display));
                    chip8->state = CLEAR;
                    break;
                case 0xee: //RET
                    --chip8->sp;
                    chip8->pc = chip8->stack[chip8->sp];
                    break;
            }
            break;
        case 0x1: //JP addr nnn
            chip8->pc = nnn;
            break;
        case 0x2: //CALL addr nnn
            chip8->stack[chip8->sp] = chip8->pc;
            ++chip8->sp;
            chip8->pc = nnn;
            break;
        case 0x3: //SE Vx, nn
            if(chip8->v[x] == nn)
                chip8->pc += 2;
            break;
        case 0x4: //SNE Vx, nn
            if(chip8->v[x] != nn)
                chip8->pc += 2;
            break;
        case 0x5: //SE Vx, Vy
            if(chip8->v[x] == chip8->v[y])
                chip8->pc += 2;
            break;
        case 0x6: //LD Vx, nn
            chip8->v[x] = nn;
            break;
        case 0x7: //ADD Vx, nn
            chip8->v[x] += nn;
            break;
        case 0x8:
            switch(n) {
                case 0x0: //LD Vx, Vy
                    chip8->v[x] = chip8->v[y];
                    break;
                case 0x1: //OR Vx, Vy
                    chip8->v[x] = chip8->v[x] | chip8->v[y];
                    break;
                case 0x2: //AND Vx, Vy
                    chip8->v[x] = chip8->v[x] & chip8->v[y];
                    break;
                case 0x3: //XOR Vx, Vy
                    chip8->v[x] = chip8->v[x] ^ chip8->v[y];
                    break;
                case 0x4: //ADD Vx, Vy
                    uint16_t sum = chip8->v[x] + chip8->v[y];
                    chip8->v[0xF] = sum > 0xFF;
                    chip8->v[x] = sum & 0xFF;
                    break;
                case 0x5: //SUB Vx, Vy
                    chip8->v[0xF] = chip8->v[x] > chip8->v[y];
                    chip8->v[x] = chip8->v[x] - chip8->v[y];
                    break;
                case 0x6: //SHR Vx {, Vy}
                    //TODO handle both original and 90s-> implementations?
                    chip8->v[0xF] = chip8->v[x] & 0x1;
                    chip8->v[x] = chip8->v[x] >> 1;
                    break;
                case 0x7: //SUBN Vx, Vy
                    chip8->v[0xF] = chip8->v[y] > chip8->v[x];
                    chip8->v[x] = chip8->v[y] - chip8->v[x];
                    break;
                case 0xE: //SHL Vx {, Vy}
                    //TODO same as 8xy6
                    chip8->v[0xF] = chip8->v[x] & 0x80;
                    chip8->v[x] = chip8->v[x] << 1;
                    break;
            }
            break;
        case 0x9: //SNE Vx, Vy
            if(chip8->v[x] != chip8->v[y])
                chip8->pc += 2;
            break;
        case 0xA: //LD I, addr nnn
            chip8->i = nnn;
            break;
        case 0xB: //JP V0, addr nnn
            chip8->pc = chip8->v[0x0] + nnn;
            break;
        case 0xC: //RND Vx, nn
            uint8_t random = rand() % 256;
            chip8->v[x] = random & nn;
            break;
        case 0xD:
            chip8_diplay_framebuffer(chip8, chip8->v[x] % 64, chip8->v[y] % 32, n);
            break;
        case 0xE: //keypress codes
            break;
        case 0xF:
            switch(nn){
                //0x07 to 0x18 keypress or timer codes
                case 0x07:
                    break;
                case 0x0A:
                    break;
                case 0x15:
                    break;
                case 0x18:
                    break;
                case 0x1E: //ADD I, Vx
                    chip8->i = chip8->i + chip8->v[x]; 
                    break;
                case 0x29: //LD F, Vx
                    //fontset start at address 0x050
                    chip8->i = 0x050 + chip8->v[x] * 5;
                    break;
                case 0x33: //LD B, Vx
                    //we are working with integers so division and modulo give correct results
                    chip8->memory[chip8->i] = chip8->v[x] / 100;
                    chip8->memory[chip8->i + 1] = (chip8->v[x] / 10) % 10;
                    chip8->memory[chip8->i + 2] = chip8->v[x] % 10;
                    break;
                case 0x55: //LD I, Vx
                    for(uint8_t i = 0; i <= x; ++i){
                        chip8->memory[chip8->i + i] = chip8->v[i];
                    }
                    break;
                case 0x65: //LD Vx, I
                    for(uint8_t i = 0; i <= x; ++i){
                        chip8->v[i] = chip8->memory[chip8->i + i];
                    }
                    break;
            }
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