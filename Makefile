CC     = g++
CXXLAGS = -std=gnu++17 -Wall -g -Wno-parentheses -Wno-unused-const-variable
SRC    = $(wildcard src/*.cpp)
OBJ    = $(patsubst src/%.cpp, obj/%.o, $(SRC))
UNAME  = $(shell uname)

ifeq ($(OS),Windows_NT)
	BIN=lisp-in-cpp.exe
else
	BIN=lisp-in-cpp
endif

ifeq ($(UNAME), Darwin)
	GDB=lldb
else
	GDB=gdb
endif

all: $(BIN)

obj:
	mkdir $@

obj/%.o: src/%.cpp obj
	$(CC) -c $< -o $@ $(CXXLAGS)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CXXLAGS)

clean:
	rm -rf $(BIN) $(OBJ)

test: clean all
	./$(BIN)

debug: clean all
	$(GDB) ./$(BIN)

