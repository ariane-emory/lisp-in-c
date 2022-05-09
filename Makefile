CC     = gcc
CFLAGS = -std=c99 -Wall -g -Wno-parentheses -Wno-unused-const-variable
SRC    = $(wildcard src/*.c)
OBJ    = $(patsubst src/%.c, obj/%.o, $(SRC))
BIN    = lisp-in-c
UNAME  = $(shell uname)

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
	./lisp-in-c

debug: clean all
	$(GDB) ./lisp-in-c

