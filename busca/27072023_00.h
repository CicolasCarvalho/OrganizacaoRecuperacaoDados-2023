//@start incl
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
//@end

//@start defn
int leia_reg(char *buffer, int tam, FILE* fd);
//@end

//@start func
int leia_reg(char *buffer, int tam, FILE* fd) {
    int size;
    fread(&size, sizeof(int), 1, fd);

    if (size < tam-1) {
        fread(buffer, sizeof(char), size, fd);
        strcat(buffer, "\0");
        return size;
    }

    return 0;
}
//@end