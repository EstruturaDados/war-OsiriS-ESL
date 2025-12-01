#include <stdio.h>
#include <string.h>

/*
    Definição da estrutura Territorio.
    Cada território possui:
    - nome: nome do território (ex: Brasil)
    - cor: cor do exército (ex: Azul, Vermelho, Verde)
    - tropas: quantidade de tropas posicionadas
*/
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Vetor de 5 territórios (cumpre o requisito do projeto)
    struct Territorio territorios[5];

    printf("========== Cadastro de Territorios (WAR - Nível 1) ==========\n\n");

    // Cadastro dos 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do Territorio %d:\n", i + 1);

        // Entrada do nome
        printf("Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome);

        // Entrada da cor
        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);

        // Entrada da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("\n========== Territorios Cadastrados ==========\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exercito: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("-------------------------------\n");
    }

    return 0;
}
