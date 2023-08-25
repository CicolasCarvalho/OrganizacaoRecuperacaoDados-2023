#include "27072023_00.h"

//@start expl
// Busca Sequencial
//@end

int main(void) {
    //@start main
    FILE *fd;
    char nome_arq[30], buffer[65], campo[30];
    int rrn = 0, cabecalho = 0, opcao = -1;
    char alterar = ' ';
    char campos[6][20] = {
        "sobrenome\0", "nome\0", "endereco\0", "cidade\0", "estado\0", "cep\0"
    };

    printf("Insira o nome do arquivo: ");
    scanf("%s", nome_arq);

    fd = fopen(nome_arq, "rb+");
    if (fd == NULL) {
        fd = fopen(nome_arq, "wb+");
        fwrite(&cabecalho, sizeof(int), 1, fd);
    } else {
        fread(&cabecalho, sizeof(int), 1, fd);
    }

    printf("Insira uma operacao (1 - inserir; 2 - buscar/atualizar; 3 - sair): ");
    scanf("%i", &opcao);

    while (opcao < 3) {
        if (opcao == 1) {
            buffer[0] = '\0';

            for (int i = 0; i < 6; i++) {
                printf("Insira seu %s: ", campos[i]);
                get_s(campo, 30, stdin);

                strcat(buffer, campo);
                strcat(buffer, "|");
            }

            fseek(fd, (cabecalho * 64) + 4, SEEK_SET);
            fwrite(buffer, sizeof(char), 64, fd);
            cabecalho++;
        } else if (opcao == 2) {
            printf("Insira o rrn a ser buscado: ");
            scanf("%i", &rrn);

            if (rrn > (cabecalho - 1)) {
                printf("RRN deve ser menor que %i", cabecalho);
                exit(1);
            }

            int offset = (rrn * 64) + 4;
            fseek(fd, offset, SEEK_SET);
            fread(buffer, sizeof(char), 64, fd);
            printf("%i: %s\n", rrn, buffer);

            FLUSH(stdin);
            printf("Deseja alterar o conteudo? (S/s - sim; N/n - nao): ");
            scanf("%c", &alterar);

            if (alterar == 'S' || alterar == 's') {
                buffer[0] = '\0';

                for (int i = 0; i < 6; i++) {
                    printf("Insira seu %s: ", campos[i]);
                    get_s(campo, 30, stdin);

                    strcat(buffer, campo);
                    strcat(buffer, "|");
                }

                fseek(fd, offset, SEEK_SET);
                fwrite(buffer, sizeof(char), 64, fd);
            }
        }

        printf("Insira uma operacao (1 - inserir; 2 - buscar/atualizar; 3 - sair): ");
        scanf("%i", &opcao);
    }

    fseek(fd, 0, SEEK_SET);
    fwrite(&cabecalho, sizeof(int), 1, fd);
    fclose(fd);
    //@end

    return 0;
}