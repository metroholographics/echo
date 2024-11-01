CC = clang
IFLAGS = -I./lib/
LFLAGS = `sdl2-config --libs --cflags` -lSDL2_image -lm
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 
SOURCES = ./src/*.c
TARGET = echo

all:
	$(CC) $(IFLAGS) $(LFLAGS) $(CFLAGS) $(SOURCES) -o echo