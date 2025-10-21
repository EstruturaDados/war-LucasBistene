#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 30
#define MAX_COR 10
#define NUM_TERRITORIOS 5

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
    int conquistado; // 0 = não, 1 = sim
} Territorio;

typedef struct {
    char objetivo[100];
    char corAlvo[MAX_COR];
    int territoriosParaConquistar;
} Missao;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio *vetor) {
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", vetor[i].nome);
        printf("Cor do exército: ");
        scanf("%s", vetor[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &vetor[i].tropas);
        vetor[i].conquistado = 0;
    }
}

// Exibir estado atual do mapa
void exibirMapa(const Territorio *vetor) {
    printf("\n=== Mapa Atual ===\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Território %d: %s | Cor: %s | Tropas: %d | Conquistado: %s\n",
               i + 1, vetor[i].nome, vetor[i].cor, vetor[i].tropas,
               vetor[i].conquistado ? "Sim" : "Não");
    }
}

// Simular batalha entre dois territórios
void atacar(Territorio *vetor) {
    int atacante, defensor;
    printf("\nEscolha o território atacante (1 a 5): ");
    scanf("%d", &atacante);
    printf("Escolha o território defensor (1 a 5): ");
    scanf("%d", &defensor);

    if (atacante < 1 || atacante > 5 || defensor < 1 || defensor > 5 || atacante == defensor) {
        printf("Entrada inválida.\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        vetor[defensor - 1].tropas--;
        printf("O defensor perdeu 1 tropa!\n");
        if (vetor[defensor - 1].tropas <= 0) {
            vetor[defensor - 1].conquistado = 1;
            printf("Território %s foi conquistado!\n", vetor[defensor - 1].nome);
        }
    } else {
        printf("O atacante não conseguiu conquistar o território.\n");
    }
}

// Definir missão aleatória
void definirMissao(Missao *m) {
    int tipo = rand() % 2;
    if (tipo == 0) {
        strcpy(m->objetivo, "Destruir o exército Verde");
        strcpy(m->corAlvo, "Verde");
        m->territoriosParaConquistar = 0;
    } else {
        strcpy(m->objetivo, "Conquistar 3 territórios");
        m->territoriosParaConquistar = 3;
        strcpy(m->corAlvo, "");
    }
    printf("\nMissão atribuída: %s\n", m->objetivo);
}

// Verificar se missão foi cumprida
int verificarMissao(const Territorio *vetor, const Missao *m) {
    if (strcmp(m->objetivo, "Destruir o exército Verde") == 0) {
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(vetor[i].cor, m->corAlvo) == 0 && vetor[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    } else {
        int conquistados = 0;
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (vetor[i].conquistado) {
                conquistados++;
            }
        }
        return conquistados >= m->territoriosParaConquistar;
    }
}

int main() {
    srand(time(NULL));
    Territorio *territorios = (Territorio *)calloc(NUM_TERRITORIOS, sizeof(Territorio));
    Missao missao;
    int opcao;

    cadastrarTerritorios(territorios);
    definirMissao(&missao);

    do {
        printf("\nMenu:\n1 - Atacar\n2 - Verificar Missão\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                atacar(territorios);
                exibirMapa(territorios);
                break;
            case 2:
                if (verificarMissao(territorios, &missao)) {
                    printf("✅ Missão cumprida! Parabéns!\n");
                } else {
                    printf("❌ Missão ainda não foi cumprida.\n");
                }
                break;
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    free(territorios);
    return 0;
}
