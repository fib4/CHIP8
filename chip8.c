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
}