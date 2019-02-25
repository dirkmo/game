.PHONY: all clean

CFLAGS=-Wall -g -D__LINUX
INC=-I../src -I.
LDFLAGS=

SRCS=../src/dem128064a.c ../src/fifo.c ../src/game.c main.c ports.c
OBJS=$(SRCS:.c=.o)

BIN=game

all: $(OBJS)
	gcc $(LDFLAGS) $(OBJS) -o $(BIN)

%.o: %.c
	gcc $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS) $(BIN)
