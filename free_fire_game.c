#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// ----------------------------------------------------
// STRUCT DO ITEM
// ----------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ----------------------------------------------------
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);
// ----------------------------------------------------

int main() {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n========= SISTEMA DE INVENTÁRIO =========\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpa ENTER do buffer

        switch(opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}

// ----------------------------------------------------
// FUNÇÃO PARA INSERIR ITEM
// ----------------------------------------------------
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("A mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("Nome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo (arma, munição, cura etc): ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();  

    mochila[*total] = novo;
    (*total)++;

    printf("Item adicionado com sucesso!\n");
    listarItens(mochila, *total);
}

// ----------------------------------------------------
// FUNÇÃO PARA REMOVER ITEM
// ----------------------------------------------------
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("Não há itens na mochila.\n");
        return;
    }

    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {

            // desloca os itens para trás
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            (*total)--;
            printf("Item removido!\n");
            listarItens(mochila, *total);
            return;
        }
    }

    printf("Item não encontrado!\n");
}

// ----------------------------------------------------
// FUNÇÃO PARA LISTAR ITENS
// ----------------------------------------------------
void listarItens(Item mochila[], int total) {
    printf("\n====== ITENS NA MOCHILA (%d) ======\n", total);

    if (total == 0) {
        printf("Nenhum item registrado.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

// ----------------------------------------------------
// FUNÇÃO PARA BUSCAR ITEM PELO NOME (BUSCA SEQUENCIAL)
// ----------------------------------------------------
void buscarItem(Item mochila[], int total) {
    char nomeBusca[30];
    printf("Digite o nome do item a procurar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("Item não encontrado.\n");
}
