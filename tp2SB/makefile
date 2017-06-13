CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -Werror -std=c99 -pedantic
OBJ = main.o assembler.o lista.o conversor.o
DEPS = assembler.h lista.h conversor.h tp1.h
VFLAGS = --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes
EXEC = ./tp1

all: tp1

tp1: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o tp1 saida.mif vgcore.*

valgrind:
	valgrind $(VFLAGS) $(EXEC) ../tst/entrada1.a

run1:
	$(EXEC) ../tst/entrada1.a

run2:
	$(EXEC) ../tst/entrada2.a
