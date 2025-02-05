#Compiler and flags

CC = gcc
CFLAGS = -Wall -Wextra -g  # Warnings for debugging purposes

# SDL2 flags
SDL2_CFLAGS = $(shell sdl2-config --cflags) # Include paths for SDL2
SDL2_LDFLAGS = $(shell sdl2-config --libs) # Linker flags for SDL2

BUILD_DIR = build
BIN = main

SRCS = main.c chip8.c graphics.c
OBJS = $(SRCS:/%.c=$(BUILD_DIR)/%.o)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN) $(SDL2_LDFLAGS)

$(BUILD_DIR)/%.o: /%.c
	mkdir -p $(BUILD_DIR)   # Ensure build directory exists
	$(CC) $(CFLAGS) $(SDL2_CFLAGS) -c $< -o $@

