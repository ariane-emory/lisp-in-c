CC = gcc

SRC  = $(wildcard src/*.c)
OBJ  = $(SRC:.c=.o)
BIN = lisp-in-c

all: $(BIN)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)