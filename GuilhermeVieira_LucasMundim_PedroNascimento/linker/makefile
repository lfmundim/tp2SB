CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -std=c99 -pedantic
OBJ = main.o conversor.o assembler.o lista.o
DEPS = conversor.h assember.h lista.h tpsb.h
VFLAGS = --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes
EXEC = ./link ../tst/

all: link

link: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f link main.o conversor.o assembler.o lista.o

valgrind:
	valgrind $(VFLAGS) $(EXEC)

run:
	$(EXEC)
