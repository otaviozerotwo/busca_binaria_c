#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOMES 1000
#define MAX_NOME_LEN 100

int busca_binaria(char nomes[MAX_NOMES][MAX_NOME_LEN], int n, char *inicio) {
    int esquerda = 0;
    int direita = n - 1;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        if (strncasecmp(nomes[meio], inicio, strlen(inicio)) == 0) {
            return meio;
        } else if (strcasecmp(nomes[meio], inicio) < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    return -1;
}

int encontrar_nomes(char *inicio, char *arquivo, char resultado[MAX_NOMES][MAX_NOME_LEN]) {
    FILE *fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return -1;
    }

    char nomes[MAX_NOMES][MAX_NOME_LEN];
    int n = 0;
    while (fgets(nomes[n], MAX_NOME_LEN, fp) != NULL) {
        nomes[n][strlen(nomes[n])-1] = '\0'; // remove o caractere de nova linha
        n++;
    }
    fclose(fp);

    int indice = busca_binaria(nomes, n, inicio);
    if (indice == -1) {
        return 0;
    }

    int i = indice;
    int j = 0;
    while (i < n && strncasecmp(nomes[i], inicio, strlen(inicio)) == 0) {
        strncpy(resultado[j], nomes[i], MAX_NOME_LEN);
        i++;
        j++;
    }

    return j;
}

int main() {
    char inicio[MAX_NOME_LEN];
    char arquivo[MAX_NOME_LEN];
    char resultado[MAX_NOMES][MAX_NOME_LEN];

    printf("Digite a sequencia de caracteres para buscar: ");
    fgets(inicio, MAX_NOME_LEN, stdin);
    inicio[strlen(inicio)-1] = '\0';

    printf("Digite o nome do arquivo com os nomes (ordenado): ");
    fgets(arquivo, MAX_NOME_LEN, stdin);
    arquivo[strlen(arquivo)-1] = '\0';

    // converte a sequência de busca para minúsculas
    for (int i = 0; i < strlen(inicio); i++) {
        inicio[i] = tolower(inicio[i]);
    }

    int n = encontrar_nomes(inicio, arquivo, resultado);

    if (n == 0) {
        printf("Nenhum nome encontrado!\n");
    } else {
        printf("Nomes encontrados:\n");
        for (int i = 0; i < n; i++) {
            printf("%s\n", resultado[i]);
        }
    }

    return 0;
}

