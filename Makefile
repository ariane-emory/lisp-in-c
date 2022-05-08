CC = gcc
CFLAGS = -std=c99 -Wall -g

SRC  = $(wildcard src/*.c)
OBJ  = $(patsubst src/%.c, obj/%.o, $(SRC))
BIN = lisp-in-c

all: $(BIN)

obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)