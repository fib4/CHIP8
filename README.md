# CHIP-8 Emulator (WIP)

![Screenshot](https://raw.githubusercontent.com/fib4/CHIP8/main/ibm.png)

A basic C-based CHIP-8 interpreter/emulator. Built for fun and educational purposes to explore low-level systems programming and emulator development fundamentals. Uses SDL2 for GUI and input handling. Currently very much work in progress but

**Stuff implemented at the moment**
- IBM logo test rom displays logo correctly
- ROM loading via CLI argument
- Basic SDL2 window and inputs
- Skeleton for CPU cycle

**Currently working on**
- Full opcode implementation
- Working input handling

## Get it running

### Dependencies

- C compiler (ie. GCC)
- SDL2 development libraries

### Compile

```bash
git clone https://github.com/fib4/CHIP8.git
make all
```

### Run

```bash
./main path/to/rom.ch8
```