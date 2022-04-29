#include "file.h"

File *open_file(char* filename) {
    char path[PATH_MAX];
    if (!getcwd(path, sizeof(path))) {
        perror("getcwd() error");
        exit(1);
    }
    snprintf(path, PATH_MAX*sizeof(char), "../%s", filename);

    File *f = calloc(1, sizeof(File));
    f->file = fopen(path, "r");
    if (!f->file) {
        printf("Error: file \"%s\" does not exist!", path);
        exit(1);
    }
    return f;
}

void close_file(File *file) {
    fclose(file->file);
    free(file);
    file = NULL;
}

char *file_to_str(File *self) {
    char *buffer = NULL;
    long string_size;
    unsigned long read_size;
    FILE *handler = self->file;

    if (handler)
    {
        fseek(handler, 0, SEEK_END);
        string_size = ftell(handler);
        rewind(handler);
        buffer = (char*) malloc(sizeof(char) * (string_size + 1) );
        read_size = fread(buffer, sizeof(char), string_size, handler);
        buffer[string_size] = '\0';
        if (string_size != read_size)
        {
            free(buffer);
            buffer = NULL;
        }
        fclose(handler);
    }

    return buffer;
}

char file_next(File *self) {
    return (char) fgetc(self->file);
}

char file_peek(File *self) {
    int c;
    c = fgetc(self->file);
    ungetc(c, self->file);
    return (char) c;
}