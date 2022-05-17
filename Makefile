CC     = gcc
CFLAGS = -std=c99 -Wall -g -Wno-parentheses -Wno-unused-const-variable
SRC    = $(wildcard src/*.c)
OBJ    = $(patsubst src/%.c, obj/%.o, $(SRC))
UNAME  = $(shell uname)

ifeq ($(OS),Windows_NT)
	BIN=lisp-in-c.exe
else
	BIN=lisp-in-c
endif

ifeq ($(UNAME), Darwin)
	GDB=lldb
else
	GDB=gdb
endif

all: $(BIN)

obj:
	mkdir $@

obj/%.o: src/%.c obj
	$(CC) -c $< -o $@ $(CFLAGS)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)

test: clean all
	./$(BIN)

debug: clean all
	$(GDB) ./$(BIN)

