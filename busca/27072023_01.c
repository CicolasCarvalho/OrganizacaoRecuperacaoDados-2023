#include "27072023_00.h"

int main(void) {
    //@start main
    FILE *fd;
    char nome_arq[30], buffer[120], *campo, sobrenome[30];
    int comp_campo = 0;
    bool achou = false;

    printf("Insira o nome do arquivo: ");
    scanf("%s", nome_arq);
    printf("Insira o sobrenome a ser buscado: ");
    scanf("%s", sobrenome);

    fd = fopen(nome_arq, "rb");
    assert(fd != NULL);

    comp_campo = leia_reg(buffer, 120, fd);

    while(comp_campo > 0 && !achou) {
        char _buf[120] = {0};
        strcpy(_buf, buffer);

        campo = strtok(_buf, "|");
        assert(campo != NULL);

        if (strcmp(sobrenome, campo) != 0){
            comp_campo = leia_reg(buffer, 120, fd);
        } else {
            achou = true;
        }
    }

    printf("%s: %s", sobrenome, achou ? buffer : "Não encontrado");
    //@end

    return 0;
}