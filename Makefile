CC = gcc

SRC  = $(wildcard src/*.c)
OBJ  = $(SRC:.c=.o)
BIN = bin

all:
	$(CC) -o $(BIN)/lisp-in-c $(OBJ)

clean:
	rm -rf $(BIN) $(OBJ)