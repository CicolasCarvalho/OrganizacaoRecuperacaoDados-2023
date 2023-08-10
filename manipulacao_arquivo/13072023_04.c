// Ní­colas dos Santos Carvalho - 128660
// Ciência da Computação - UEM
// 06 07 2022

//@start expl
// Escreve campos binários
//@end

#include "13072023_00.h"

//@start defn
int leia_reg(char *buffer, int tam, FILE* fd);
//@end

int main(void){
    //@start main
    FILE *fd;
    char nome_arq[30], buffer[120], *campo;
    int comp_campo = 0;

    printf("Insira o nome do arquivo: ");
    scanf("%s", nome_arq);

    fd = fopen(nome_arq, "rb");
    if (fd == NULL) assert(false);

    comp_campo = leia_reg(buffer, 120, fd);

    while (comp_campo > 0) {
        printf("\n---\n");

        campo = strtok(buffer, "|");

        while (campo != NULL) {
            printf("campo: %s\n", campo);
            campo = strtok(NULL, "|");
        }

        buffer[0] = '\0';
        comp_campo = leia_reg(buffer, 120, fd);
    }

    fclose(fd);
    //@end
}

//@start func
int leia_reg(char *buffer, int tam, FILE* fd) {
    int size;
    fread(&size, sizeof(int), 1, fd);

    if (size < tam) {
        fread(buffer, sizeof(char), size, fd);
        strcat(buffer, "\0");
        return size;
    }

    return 0;
}
//@end