// Ní­colas dos Santos Carvalho - 128660
// Ciência da Computação - UEM
// 06 07 2022

//@start expl
// Escreve campos binários
//@end

#include "13072023_00.h"

int main(void){
    //@start main
    FILE *fd;
    char nome_arq[30], buffer[120], campo[30];
    int comp_campo = 0;

    char campos[6][20] = {
        "sobrenome\0", "nome\0", "endereco\0", "cidade\0", "estado\0", "cep\0"
    };

    printf("Insira o nome do arquivo: ");
    scanf("%s", nome_arq);

    fd = fopen(nome_arq, "wb");
    if (fd == NULL) assert(false);

    printf("Insira seu sobrenome: ");
    comp_campo = get_s(campo, 30, stdin);

    while (comp_campo > 0) {
        buffer[0] = '\0';

        strcat(buffer, campo);
        strcat(buffer, "|");

        for (int i = 1; i < 6; i++) {
            printf("Insira seu %s: ", campos[i]);
            get_s(campo, 30, stdin);

            strcat(buffer, campo);
            strcat(buffer, "|");
        }

        int size = strlen(buffer);

        fwrite(&size, sizeof(int), 1, fd);
        fwrite(buffer, sizeof(char), size, fd);

        printf("Insira seu sobrenome: ");
        comp_campo = get_s(campo, 20, stdin);
    }

    fclose(fd);
    //@end
}