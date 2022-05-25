#include "file.h"

void str_concat(char* dest, char* src)
{
    while (*dest) dest++;
    while ((*dest++ = *src++));
    return;
}

FILE *open_file(char* filename) {
    char path[PATH_MAX];
    *path = 0;
    str_concat(path, "./");
    str_concat(path, filename);

    FILE *file = fopen(path, "r");
    if (!file) {
        printf("Error: file \"%s\" does not exist!", path);
        exit(1);
    }
    return file;
}

char file_next(FILE *self) {
    return (char) fgetc(self);
}

char file_peek(FILE *self) {
    int c = fgetc(self);
    ungetc(c, self);
    return (char) c;
}
