#include <stdio.h>
#include <stdlib.h>

void encriptar(char* c, int* out, int size);

int main(void) {
    char dados_str[50];
    FILE *file;

    fprintf(stdout, "hey usuario insira seus dados de entrada:\n");
    scanf("%s", dados_str);

    file = fopen("./paulo/sistema_de_save/game.save", "wb");
    if (file == NULL) {
        fprintf(stderr, "erro");
        return 1;
    }

    int a[50];
    encriptar(dados_str, a, 50);

    fprintf(stdout, "%s", dados_str);
    fwrite(a, sizeof(int), 50*sizeof(int), file);

    fclose(file);
    return 0;
}

void encriptar(char* c, int* out, int size) {
    for (int i = 0; i < size; i++) {
        out[i] = (int)c[i]+128;
    }
}