CC = gcc
CFLAGS = -std=c99 -Wall

SRC  = $(wildcard src/*.c)
OBJ  = $(patsubst src/%.c, obj/%.o, $(SRC))
BIN = lisp-in-c

all: $(BIN)

obj:
	mkdir $@

obj/%.o: src/%.c obj
	$(CC) -c $< -o $@ $(CFLAGS)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)
