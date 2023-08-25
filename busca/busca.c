// Nícolas dos Santos Carvalho - 128660
// Ciência da Computação - UEM
// 24 08 2023

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#ifndef _WIN32
    #define FLUSH(fd) __fpurge(fd)
#else
    #define FLUSH(fd) fflush(fd)
#endif

int leia_reg(char *buffer, int tam, FILE* fd);
int get_s(char *str, int size, FILE* fd);

int main(void) {
    // 1
    {
        // Busca Sequencial

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

        fclose(fd);
    }

    // 2
    {
        // Busca RRN

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
    }

    // 3
    {
        // Busca/Alteracao

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
    }

    return 0;
}

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

