OBJS=main.o eeprom.o
CC=gcc
CFLAGS= -std=c99 -Wall -g -O0

main.out: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -l pthread

.PHONY: all
all: main.out

