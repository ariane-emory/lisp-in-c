UNAME_S = $(shell uname -s)
CXX     = g++
CXXLAGS = -std=gnu++17 -Wall -g -Wno-parentheses -Wno-unused-const-variable -Wextra -Wpedantic -Wconversion # -Wshadow
SRC    = $(wildcard src/*.cpp)
OBJ    = $(patsubst src/%.cpp, obj/%.o, $(SRC))
UNAME  = $(shell uname)

ifeq ($(OS),Windows_NT)
	BIN=lisp-in-cpp.exe
else
	BIN=lisp-in-cpp
endif

ifeq ($(UNAME_S),Darwin)
	CXX = g++-12
	GDB=lldb
else
	GDB=gdb
endif

all: $(BIN)

obj:
	mkdir $@

obj/%.o: src/%.cpp obj
	$(CXX) -c $< -o $@ $(CXXLAGS)

$(BIN): $(OBJ)
	$(CXX) -o $@ $^ $(CXXLAGS)

clean:
	rm -rf $(BIN) $(OBJ)

test: clean all
	./$(BIN)

debug: clean all
	$(GDB) ./$(BIN)

