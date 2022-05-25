#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#if __linux__
  #include <linux/limits.h>
#else
  #include <limits.h>
#endif

FILE *open_file(char* filename);
char file_next(FILE *self);
char file_peek(FILE *self);

#endif
