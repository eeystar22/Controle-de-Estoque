#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void exibirMenu() {
    printf("========================================\n");
    printf("          Controle de Estoque           \n");
    printf("========================================\n");
    printf("Selecione uma opção:\n");
    printf("1. Adicionar Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Estoque\n");
    printf("4. Sair\n");
    printf("Opção: ");
}
int main() {
    int opcao;
    char continuar;

    do {
        exibirMenu();
        while (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 4) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Opção inválida! Tente novamente.\n");
            printf("Opção: ");
        }
        if (opcao == 1) {
            char nome[100];
            int quantidade;
            printf("Digite o nome do item: ");
            scanf("%s", nome);
            printf("Digite a quantidade: ");
            scanf("%d", &quantidade);

            FILE *arquivo = fopen("inventory.txt", "a");
            if (arquivo != NULL) {
                fprintf(arquivo, "%s\n%d\n", nome, quantidade);
                fclose(arquivo);
            }
            printf("Item adicionado com sucesso!\n");
        } else if (opcao == 2) {
            char nomeRemover[100];
            int qtdRemover;
            printf("Digite o nome do item: ");
            scanf("%s", nomeRemover);
            printf("Digite a quantidade a ser removida: ");
            scanf("%d", &qtdRemover);

            FILE *arquivo = fopen("inventory.txt", "r");
            FILE *temp = fopen("temp.txt", "w");

            int encontrado = 0;
            char nomeAtual[100];
            int qtdAtual;

            if (arquivo != NULL && temp != NULL) {
                while (fscanf(arquivo, "%s %d", nomeAtual, &qtdAtual) == 2) {
                    if (strcmp(nomeAtual, nomeRemover) == 0) {
                        encontrado = 1;
                        if (qtdRemover > qtdAtual) {
                            printf("Estoque insuficiente. Quantidade disponível: %d\n", qtdAtual);
                            fprintf(temp, "%s\n%d\n", nomeAtual, qtdAtual);
                        } else if (qtdRemover == qtdAtual) {
                            printf("Item removido do estoque!\n");
                        } else {
                            int novaQtd = qtdAtual - qtdRemover;
                            printf("Quantidade atualizada com sucesso!\n");
                            fprintf(temp, "%s\n%d\n", nomeAtual, novaQtd);
                        }
                    } else {
                        fprintf(temp, "%s\n%d\n", nomeAtual, qtdAtual);
                    }
                }
                fclose(arquivo);
                fclose(temp);
                remove("inventory.txt");
                rename("temp.txt", "inventory.txt");
                if (!encontrado) {
                    printf("Item não encontrado.\n");
                }
            } else {
                if (arquivo != NULL) fclose(arquivo);
                if (temp != NULL) fclose(temp);
                printf("Item não encontrado.\n");
            }
        } else if (opcao == 3) {
            FILE *arquivo = fopen("inventory.txt", "r");
            char nomeAtual[100];
            int qtdAtual;
            int primeiro = 1;

            if (arquivo != NULL) {
                while (fscanf(arquivo, "%s %d", nomeAtual, &qtdAtual) == 2) {
                    if (primeiro) {
                        printf("================================\n");
                        printf("         Estoque Atual          \n");
                        printf("================================\n");
                        primeiro = 0;
                    } else {
                        printf("\n");
                    }
                    printf("Nome: %s\n", nomeAtual);
                    printf("Quantidade: %d\n", qtdAtual);
                }
                fclose(arquivo);
            }
            if (primeiro) {
                printf("O estoque está vazio.\n");
            }
        } else if (opcao == 4) {
            printf("Obrigada por usar o Controle de Estoques! Até a próxima.\n");
            break;
        }
    } while (1);
    return 0;
}













