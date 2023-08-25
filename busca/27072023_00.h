//@start incl
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
//@end

//@start defn
#ifndef _WIN32
    #define FLUSH(fd) __fpurge(fd)
#else
    #define FLUSH(fd) fflush(fd)
#endif

int leia_reg(char *buffer, int tam, FILE* fd);
int get_s(char *str, int size, FILE* fd);
//@end

//@start func
int leia_reg(char *buffer, int tam, FILE* fd) {
    int size;
    fread(&size, sizeof(int), 1, fd);

    if (size < tam-1) {
        fread(buffer, sizeof(char), size, fd);
        buffer[size] = '\0';
        return size;
    }

    return 0;
}

int get_s(char *str, int size, FILE* fd) {
    FLUSH(fd);
    fgets(str, size, fd);
    str[strlen(str)-1] = '\0';
    return strlen(str);
}
//@end