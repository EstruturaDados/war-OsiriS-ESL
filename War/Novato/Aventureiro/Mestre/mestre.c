#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    Estrutura do Território conforme o projeto:
    - nome: nome do território
    - cor: dono atual
    - tropas: quantidade de tropas
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


/* ============================================================
                    FUNÇÃO: CADASTRAR TERRITÓRIOS
   ============================================================*/
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor (dono): ");
        scanf("%s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}


/* ============================================================
                    FUNÇÃO: EXIBIR MAPA
   ============================================================*/
void exibirMapa(Territorio* mapa, int n) {
    printf("\n========== MAPA ATUAL ==========\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] %s\n", i, mapa[i].nome);
        printf("    Cor: %s\n", mapa[i].cor);
        printf("    Tropas: %d\n", mapa[i].tropas);
    }
}


/* ============================================================
                    FUNÇÃO: ATAQUE ENTRE TERRITÓRIOS
   ============================================================*/
void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante->tropas <= 1) {
        printf("\nO atacante não tem tropas suficientes!\n");
        return;
    }

    printf("\n===== BATALHA =====\n");

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("Ataque (%s) rolou: %d\n", atacante->nome, dadoA);
    printf("Defesa (%s) rolou: %d\n", defensor->nome, dadoD);

    if (dadoA > dadoD) {
        printf(">> O atacante venceu!\n");

        // Defensor muda de dono
        strcpy(defensor->cor, atacante->cor);

        // Metade das tropas migra
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas;

    } else {
        printf(">> Defesa bem-sucedida!\n");
        atacante->tropas--;
    }
}


/* ============================================================
             FUNÇÃO: ATRIBUIR MISSÃO AO JOGADOR
   ============================================================*/
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]); // cópia da missão sorteada
}


/* ============================================================
        FUNÇÃO: EXIBIR MISSÃO (passagem por valor)
   ============================================================*/
void exibirMissao(char* missao) {
    printf("\n===== SUA MISSÃO =====\n%s\n", missao);
}


/* ============================================================
        FUNÇÃO: VERIFICAR MISSÃO — retorna 1 se concluída
   ============================================================*/
int verificarMissao(char* missao, Territorio* mapa, int n) {

    // Exemplo de lógica simples de vitória
    // 1) Missão: "Conquistar 3 territórios da cor Azul"
    if (strstr(missao, "3 territorios Azul") != NULL) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0)
                count++;
        }
        if (count >= 3)
            return 1;
    }

    // 2) Missão: "Eliminar tropas vermelhas"
    if (strstr(missao, "Eliminar vermelho") != NULL) {
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0)
                return 0; // ainda existe vermelho
        }
        return 1;
    }

    // 3) Missão: "Controlar todos os territórios"
    if (strstr(missao, "todos territorios") != NULL) {
        char corDono[10];
        strcpy(corDono, mapa[0].cor);

        for (int i = 1; i < n; i++) {
            if (strcmp(mapa[i].cor, corDono) != 0)
                return 0;
        }

        return 1;
    }

    // Missões genéricas podem ser adicionadas

    return 0; // missão não cumprida
}


/* ============================================================
                FUNÇÃO: LIBERAR MEMÓRIA
   ============================================================*/
void liberarMemoria(Territorio* mapa, char* missaoJogador) {
    free(mapa);
    free(missaoJogador);
}


/* ============================================================
                        FUNÇÃO PRINCIPAL
   ============================================================*/
int main() {
    srand(time(NULL));

    int n;

    printf("===== WAR ESTRUTURADO — Missões Estratégicas =====\n");
    printf("Quantos territórios terá o mapa? ");
    scanf("%d", &n);

    // Alocação dinâmica dos territórios
    Territorio* mapa = (Territorio*) malloc(n * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    // Definição das missões pré-definidas
    char* missoes[] = {
        "Conquistar 3 territorios Azul",
        "Eliminar tropas da cor Vermelho",
        "Controlar todos territorios",
        "Conquistar qualquer 2 territorios",
        "Dominar 1 territorio com mais de 15 tropas"
    };

    int totalMissoes = 5;

    // Alocação dinâmica da missão do jogador
    char* missaoJogador = (char*) malloc(150 * sizeof(char));

    atribuirMissao(missaoJogador, missoes, totalMissoes);

    // Mostra ao jogador apenas uma vez
    exibirMissao(missaoJogador);

    int continuar = 1;

    while (continuar) {

        exibirMapa(mapa, n);

        int a, d;
        printf("\nEscolha o território atacante (índice): ");
        scanf("%d", &a);

        printf("Escolha o território defensor (índice): ");
        scanf("%d", &d);

        // Valida ataque
        if (strcmp(mapa[a].cor, mapa[d].cor) == 0) {
            printf("\nErro: não é permitido atacar seu próprio território!\n");
        } else {
            atacar(&mapa[a], &mapa[d]);
        }

        // Verifica missão silenciosamente
        if (verificarMissao(missaoJogador, mapa, n)) {
            printf("\n===== MISSÃO CUMPRIDA! Você venceu o jogo! =====\n");
            break;
        }

        printf("\nDeseja continuar? (1 = sim, 0 = não): ");
        scanf("%d", &continuar);
    }

    liberarMemoria(mapa, missaoJogador);

    printf("\nJogo encerrado.\n\n");

    return 0;
}
