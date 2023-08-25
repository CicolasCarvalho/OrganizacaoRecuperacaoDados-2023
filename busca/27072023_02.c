#include "27072023_00.h"

//@start expl
// Busca RRN
//@end

int main(void) {
    //@start main
    FILE *fd;
    char nome_arq[30], buffer[65];
    int rrn = 0, cabecalho = 0;

    printf("Insira o nome do arquivo: ");
    scanf("%s", nome_arq);
    printf("Insira o rrn a ser buscado: ");
    scanf("%i", &rrn);

    fd = fopen(nome_arq, "rb");
    assert(fd != NULL);

    fread(&cabecalho, sizeof(int), 1, fd);

    if (rrn > (cabecalho - 1)) {
        printf("RRN deve ser menor que %i", cabecalho);
        exit(1);
    }

    int offset = (rrn * 64) + 4;
    fseek(fd, offset, SEEK_SET);
    fread(buffer, sizeof(char), 64, fd);
    printf("%i: %s", rrn, buffer);

    fclose(fd);
    //@end

    return 0;
}