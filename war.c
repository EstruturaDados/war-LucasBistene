#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR 10
#define MAX_MISSAO 100

// Estrutura de dados para território
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Estrutura de dados para missão
typedef struct {
    char descricao[MAX_MISSAO];
    int tropasNecessarias;
} Missao;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", vetor[i].nome);

        printf("Cor do exército: ");
        scanf("%s", vetor[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &vetor[i].tropas);
    }
}

// Função para exibir territórios
void exibirTerritorios(const Territorio *vetor, int tamanho) {
    printf("\n=== Territórios Registrados ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", vetor[i].nome);
        printf("Cor do exército: %s\n", vetor[i].cor);
        printf("Tropas: %d\n", vetor[i].tropas);
        printf("-----------------------------\n");
    }
}

// Função para definir missão
void definirMissao(Missao *m) {
    strcpy(m->descricao, "Conquistar a Ásia com pelo menos 100 tropas.");
    m->tropasNecessarias = 100;
}

// Função para verificar se missão foi cumprida
int verificarMissao(const Territorio *vetor, int tamanho, const Missao *m) {
    int totalTropas = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(vetor[i].nome, "Asia") == 0) {
            totalTropas += vetor[i].tropas;
        }
    }
    return totalTropas >= m->tropasNecessarias;
}

int main() {
    Territorio territorios[MAX_TERRITORIOS];
    Missao missao;

    cadastrarTerritorios(territorios, MAX_TERRITORIOS);
    exibirTerritorios(territorios, MAX_TERRITORIOS);

    definirMissao(&missao);
    printf("\nMissão: %s\n", missao.descricao);

    if (verificarMissao(territorios, MAX_TERRITORIOS, &missao)) {
        printf("✅ Missão cumprida! Você conquistou a Ásia com tropas suficientes.\n");
    } else {
        printf("❌ Missão não cumprida. Reforce seus territórios!\n");
    }

    return 0;
}
