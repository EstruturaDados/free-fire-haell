#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

//-----------------------------------------------------
// STRUCTS
//-----------------------------------------------------

// Estrutura básica de item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

//-----------------------------------------------------
// VARIÁVEIS GLOBAIS PARA O VETOR
//-----------------------------------------------------
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;

// Contadores de comparação
int compBuscaSequencial = 0;
int compBuscaBinaria = 0;

//-----------------------------------------------------
// FUNÇÕES DO VETOR
//-----------------------------------------------------

void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome: "); fflush(stdin);
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo: "); fflush(stdin);
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[totalVetor++] = novo;

    printf("Item inserido no vetor!\n");
}

void listarVetor() {
    printf("\n--- ITENS NO VETOR (%d) ---\n", totalVetor);
    for (int i = 0; i < totalVetor; i++) {
        printf("%d) %s | %s | %d\n",
               i + 1,
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
}

void removerItemVetor() {
    char nome[30];
    printf("Nome a remover: "); fflush(stdin);
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalVetor - 1; j++)
                mochilaVetor[j] = mochilaVetor[j + 1];
            totalVetor--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = 0; j < totalVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("Vetor ordenado!\n");
}

void buscarSequencialVetor() {
    char nome[30];
    compBuscaSequencial = 0;

    printf("Nome a buscar: "); fflush(stdin);
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < totalVetor; i++) {
        compBuscaSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("Encontrado: %s | %s | %d\n",
                   mochilaVetor[i].nome,
                   mochilaVetor[i].tipo,
                   mochilaVetor[i].quantidade);
            printf("Comparacoes: %d\n", compBuscaSequencial);
            return;
        }
    }
    printf("Item nao encontrado! Comparacoes: %d\n", compBuscaSequencial);
}

void buscarBinariaVetor() {
    char nome[30];
    compBuscaBinaria = 0;

    printf("Nome a buscar (binaria): "); fflush(stdin);
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int inicio = 0, fim = totalVetor - 1;

    while (inicio <= fim) {
        compBuscaBinaria++;

        int meio = (inicio + fim) / 2;
        int cmp = strcmp(nome, mochilaVetor[meio].nome);

        if (cmp == 0) {
            printf("Encontrado: %s | %s | %d\n",
                   mochilaVetor[meio].nome,
                   mochilaVetor[meio].tipo,
                   mochilaVetor[meio].quantidade);
            printf("Comparacoes binaria: %d\n", compBuscaBinaria);
            return;
        }
        if (cmp > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("Item nao encontrado! Comparacoes: %d\n", compBuscaBinaria);
}

//-----------------------------------------------------
// FUNÇÕES DA LISTA ENCADEADA
//-----------------------------------------------------

No* lista = NULL;

void inserirItemLista() {
    No* novo = (No*) malloc(sizeof(No));

    printf("Nome: "); fflush(stdin);
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo: "); fflush(stdin);
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = lista;
    lista = novo;

    printf("Item inserido na lista!\n");
}

void listarLista() {
    printf("\n--- LISTA ENCADEADA ---\n");
    No* aux = lista;
    int i = 1;

    while (aux != NULL) {
        printf("%d) %s | %s | %d\n",
               i++,
               aux->dados.nome,
               aux->dados.tipo,
               aux->dados.quantidade);
        aux = aux->proximo;
    }
}

void removerItemLista() {
    char nome[30];
    printf("Nome a remover: "); fflush(stdin);
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *aux = lista, *ant = NULL;

    while (aux != NULL) {
        if (strcmp(aux->dados.nome, nome) == 0) {
            if (ant == NULL)
                lista = aux->proximo;
            else
                ant->proximo = aux->proximo;

            free(aux);
            printf("Item removido!\n");
            return;
        }
        ant = aux;
        aux = aux->proximo;
    }

    printf("Item nao encontrado.\n");
}

void buscarSequencialLista() {
    char nome[30];
    int comparacoes = 0;

    printf("Nome a buscar: "); fflush(stdin);
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No* aux = lista;

    while (aux != NULL) {
        comparacoes++;
        if (strcmp(aux->dados.nome, nome) == 0) {
            printf("Encontrado: %s | %s | %d\n",
                   aux->dados.nome,
                   aux->dados.tipo,
                   aux->dados.quantidade);
            printf("Comparacoes sequencial (lista): %d\n", comparacoes);
            return;
        }
        aux = aux->proximo;
    }

    printf("Item nao encontrado! Comparacoes: %d\n", comparacoes);
}

//-----------------------------------------------------
// MENUS
//-----------------------------------------------------

void menuVetor() {
    int op;
    do {
        printf("\n--- MOCHILA (VETOR) ---\n");
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Listar\n");
        printf("4 - Busca sequencial\n");
        printf("5 - Ordenar\n");
        printf("6 - Busca binaria\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarVetor(); break;
            case 4: buscarSequencialVetor(); break;
            case 5: ordenarVetor(); break;
            case 6: buscarBinariaVetor(); break;
        }

    } while (op != 0);
}

void menuLista() {
    int op;
    do {
        printf("\n--- MOCHILA (LISTA ENCADEADA) ---\n");
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Listar\n");
        printf("4 - Busca sequencial\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarLista(); break;
            case 4: buscarSequencialLista(); break;
        }

    } while (op != 0);
}

//-----------------------------------------------------
// MAIN
//-----------------------------------------------------

int main() {
    int op;

    do {
        printf("\n=== SISTEMA DE INVENTÁRIO ===\n");
        printf("1 - Mochila com VETOR\n");
        printf("2 - Mochila com LISTA ENCADEADA\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar();

        if (op == 1) menuVetor();
        else if (op == 2) menuLista();

    } while (op != 0);

    printf("Encerrando...\n");
    return 0;
}
