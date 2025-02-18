#Compiler and flags

CC = gcc
CFLAGS = -Wall -Wextra -g  # Warnings for debugging purposes

# SDL2 flags
SDL2_CFLAGS = $(shell sdl2-config --cflags) # Include paths for SDL2
SDL2_LDFLAGS = $(shell sdl2-config --libs | sed -E s/-mwindows//) # Linker flags for SDL2

BUILD_DIR = build
SRC_DIR = src
BIN = main

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/chip8.c $(SRC_DIR)/graphics.c
OBJS = $(SRCS:$(SRC_DIR)/.c=$(BUILD_DIR)/.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN) $(SDL2_LDFLAGS)

$(BUILD_DIR)/%.o: /%.c
	mkdir -p $(BUILD_DIR)   # Ensure build directory exists
	$(CC) $(CFLAGS) $(SDL2_CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN)