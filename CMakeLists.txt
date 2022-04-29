cmake_minimum_required(VERSION 3.21)
project(lisp_in_c C)

set(CMAKE_C_STANDARD 99)

add_executable(lisp_in_c src/main.c src/token.c src/token.h src/lex.c src/lex.h src/parse.c src/parse.h
        src/ast.c src/ast.h src/file.c src/file.h src/gc.c src/gc.h src/eval.c src/eval.h)
