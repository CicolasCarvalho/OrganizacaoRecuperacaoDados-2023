#include "27072023_00.h"

//@start expl
// Busca Sequencial
//@end

int main(void) {
    //@start main
    FILE *fd;
    char nome_arq[30], buffer[120], *sobrenome, sobrenome_busca[30], *campo;
    bool achou = false;

    printf("Insira o nome do arquivo: ");
    scanf("%s", nome_arq);
    printf("Insira o sobrenome_busca a ser buscado: ");
    scanf("%s", sobrenome_busca);

    fd = fopen(nome_arq, "rb");
    assert(fd != NULL);

    int comp_reg = leia_reg(buffer, 150, fd);

    while (!achou && comp_reg && !feof(fd)) {
        sobrenome = strtok(buffer, "|");

        if (strcmp(sobrenome, sobrenome_busca) == 0) {
            achou = true;
        } else {
            comp_reg = leia_reg(buffer, 150, fd);
        }
    }

    if (achou) {
        printf("%s: ", sobrenome_busca);
        campo = strtok(NULL, "|");

        while (campo != NULL) {
            printf("%s|", campo);
            campo = strtok(NULL, "|");
        }
    } else {
        printf("%s nao foi encontrado!", sobrenome_busca);
    }
    //@end

    return 0;
}