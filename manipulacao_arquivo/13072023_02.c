// Ní­colas dos Santos Carvalho - 128660
// Ciência da Computação - UEM
// 06 07 2022

//@start expl
// Le Campos
//@end

#include "13072023_00.h"

//@start defn
int leia_campo(char *str, int tam, FILE *entrada);
//@end

int main(void) {
    //@start main
    FILE *fd;
    char nome_arq[30];
    char str[30] = "\0";

    printf("Insira o nome do arquivo: ");
    scanf("%s", nome_arq);

    fd = fopen(nome_arq, "r");
    if (fd == NULL) assert(false);

    while (leia_campo(str, 30, fd) > 0) {
        printf("%s ", str);
    }
    //@end

    return 0;
}

//@start func
int leia_campo(char *str, int tam, FILE *entrada) {
    int i = 0;
    char ch = '\0';

    while ((ch = fgetc(entrada)) != EOF && ch != '|' && ch != '\n' && i < tam - 1) {
        str[i] = ch;
        str[i+1] = '\0';
        i++;
    }

    return i;
}
//@end