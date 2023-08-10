// Nícolas dos Santos Carvalho - 128660
// Ciência da Computação - UEM
// 06 07 2022

//@start expl
// Escreve Campos
//@end

#include "13072023_00.h"

//@start defn
void pessoa_salvar(Pessoa *pessoa, FILE *fd);
//@end

int main(void) {
    //@start main
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
    //@end

    return 0;
}

//@start func
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
//@end