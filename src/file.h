#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    FILE *file;
} File;

File *open_file(char* filename);
void close_file(File *file);
char *file_to_str(File *self);
char file_next(File *self);
char file_peek(File *self);

#endif
