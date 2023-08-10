//@prior 8

//@start incl
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
//@end

//@start defn
#ifndef _WIN32
    #define FLUSH(fd) __fpurge(fd)
#else
    #define FLUSH(fd) fflush(fd)
#endif

typedef struct {
    char nome[20], sobrenome[20], endereco[30], cidade[20], estado[4], cep[9];
} Pessoa;

int get_s(char *str, int size, FILE* fd);
//@end

//@start func
int get_s(char *str, int size, FILE* fd) {
    FLUSH(fd);
    fgets(str, size, fd);
    str[strlen(str)-1] = '\0';
    return strlen(str);
}
//@end