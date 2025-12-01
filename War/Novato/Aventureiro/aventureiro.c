#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    Estrutura básica do território:
    - nome: nome do território (ex: Alaska)
    - cor: dono atual do território (ex: Azul)
    - tropas: quantidade de tropas presentes
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


/* ======================================================
                FUNÇÃO: CADASTRAR TERRITÓRIOS
   ======================================================*/
void cadastrarTerritorios(Territorio* mapa, int n) {
    printf("\n===== Cadastro de Territorios =====\n");

    for (int i = 0; i < n; i++) {
        printf("\nTerritorio %d:\n", i + 1);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exercito (dono): ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}


/* ======================================================
                FUNÇÃO: EXIBIR TERRITÓRIOS
   ======================================================*/
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n===== Mapa Atual =====\n");

    for (int i = 0; i < n; i++) {
        printf("\n[%d] %s\n", i, mapa[i].nome);
        printf("    Cor: %s\n", mapa[i].cor);
        printf("    Tropas: %d\n", mapa[i].tropas);
    }
}


/* ======================================================
              FUNÇÃO DE ATAQUE ENTRE TERRITÓRIOS
   ======================================================*/
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n===== BATALHA =====\n");

    if (atacante->tropas <= 1) {
        printf("O territorio atacante nao possui tropas suficientes para atacar!\n");
        return;
    }

    // simulação de dados (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("%s (Atacante) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("%s (Defensor) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\n>> O atacante venceu a batalha!\n");

        // defensor muda de dono
        strcpy(defensor->cor, atacante->cor);

        // defensor recebe metade das tropas do atacante
        defensor->tropas = atacante->tropas / 2;

        // atacante perde as tropas transferidas
        atacante->tropas = atacante->tropas - defensor->tropas;

        printf("O territorio %s agora pertence ao exército %s!\n",
               defensor->nome, defensor->cor);

    } else {
        printf("\n>> O ataque falhou! O defensor venceu.\n");
        atacante->tropas--; // atacante perde uma tropa
    }
}


/* ======================================================
             FUNÇÃO: LIBERAÇÃO DE MEMÓRIA
   ======================================================*/
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}


/* ======================================================
                       FUNÇÃO PRINCIPAL
   ======================================================*/
int main() {
    srand(time(NULL)); // garante aleatoriedade

    int n;

    printf("===== WAR ESTRUTURADO — Sistema de Ataques =====\n");
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &n);

    // alocação dinâmica
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // cadastro inicial
    cadastrarTerritorios(mapa, n);

    int continuar = 1;

    while (continuar) {
        exibirTerritorios(mapa, n);

        int tAtacante, tDefensor;

        printf("\nEscolha o territorio atacante (indice): ");
        scanf("%d", &tAtacante);

        printf("Escolha o territorio defensor (indice): ");
        scanf("%d", &tDefensor);

        // validação
        if (strcmp(mapa[tAtacante].cor, mapa[tDefensor].cor) == 0) {
            printf("\nErro: voce nao pode atacar um territorio que tambem é seu!\n");
        } else {
            atacar(&mapa[tAtacante], &mapa[tDefensor]);
        }

        printf("\nDeseja realizar outro ataque? (1 = Sim, 0 = Nao): ");
        scanf("%d", &continuar);
    }

    // libera memória
    liberarMemoria(mapa);

    printf("\nPrograma encerrado. Ate a proxima batalha!\n");

    return 0;
}
