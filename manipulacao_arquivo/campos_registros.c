// Nícolas dos Santos Carvalho - 128660
// Ciência da Computação - UEM
// 21 07 2023

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

#ifndef _WIN32
    #define FLUSH(fd) __fpurge(fd)
#else
    #define FLUSH(fd) fflush(fd)
#endif

typedef struct {
    char nome[20], sobrenome[20], endereco[30], cidade[20], estado[4], cep[9];
} Pessoa;

int get_s(char *str, int size, FILE* fd);
void pessoa_salvar(Pessoa *pessoa, FILE *fd);
int leia_campo(char *str, int tam, FILE *entrada);
int leia_reg(char *buffer, int tam, FILE* fd);

int main(void) {
    // 1
    {
        // Escreve Campos

        FILE *fd;
        char nome_arq[30];
        int comp_sobrenome = 0;
        Pessoa pessoa;
    
        printf("Insira o nome do arquivo: ");
        scanf("%s", nome_arq);
    
        fd = fopen(nome_arq, "w");
        if (fd == NULL) assert(false);
    
        printf("Insira seu sobrenome: ");
        comp_sobrenome = get_s(pessoa.sobrenome, 20, stdin);
    
        while (comp_sobrenome > 0) {
            printf("Insira seu nome: ");
            get_s(pessoa.nome, 20, stdin);
            printf("Insira seu endereco: ");
            get_s(pessoa.endereco, 30, stdin);
            printf("Insira seu cidade: ");
            get_s(pessoa.cidade, 20, stdin);
            printf("Insira seu estado: ");
            get_s(pessoa.estado, 4, stdin);
            printf("Insira seu cep: ");
            get_s(pessoa.cep, 8, stdin);
    
            pessoa_salvar(&pessoa, fd);
    
            printf("Insira seu sobrenome: ");
            comp_sobrenome = get_s(pessoa.sobrenome, 20, stdin);
        }
    
        fclose(fd);
    }

    // 2
    {
        // Le Campos

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
    }

    // 3
    {
        // Escreve campos binários

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
    }

    // 4
    {
        // Escreve campos binários

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
    }

    return 0;
}

int get_s(char *str, int size, FILE* fd) {
    FLUSH(fd);
    fgets(str, size, fd);
    str[strlen(str)-1] = '\0';
    return strlen(str);
}

void pessoa_salvar(Pessoa *pessoa, FILE *fd) {
    fprintf(
        fd, "%s|%s|%s|%s|%s|%s\n",
        pessoa->nome,
        pessoa->sobrenome,
        pessoa->endereco,
        pessoa->cidade,
        pessoa->estado,
        pessoa->cep
    );
}

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

