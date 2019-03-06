.PHONY: all clean

CFLAGS=-Wall -g -D__LINUX
INC=-I../src -I. -I/usr/include/SDL2
LDFLAGS=-lSDL2

SRCS=../src/dem128064a.c ../src/fifo.c ../src/game.c ../src/salma.c ../src/font_6x8.c ../src/font.c ../src/canvas.c ../src/blocks.c
SRCS+=main.c ports.c dem128064a_sim.c
OBJS=$(SRCS:.c=.o)

BIN=game

all: $(OBJS)
	gcc $(OBJS) $(LDFLAGS) -o $(BIN)

%.o: %.c
	gcc $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS) $(BIN)
