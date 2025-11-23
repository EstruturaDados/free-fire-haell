#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==========================
//        ESTRUTURAS
// ==========================

// Estrutura de itens da mochila (primeiros desafios)
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Estrutura para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Estrutura de componentes da torre de fuga (desafio final)
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ==========================
//     VARIÁVEIS GLOBAIS
// ==========================

Item mochilaVetor[10];
int totalItensVetor = 0;

No* inicioLista = NULL;

long long comparacoes = 0;


// ======================================================
//   FUNÇÕES DO VETOR - MOCHILA (INSERIR / REMOVER / BUSCAR)
// ======================================================

void inserirItemVetor() {
    if (totalItensVetor >= 10) {
        printf("\nMochila cheia!\n");
        return;
    }

    Item novo;
    printf("\nNome do item: ");
    scanf(" %[^\n]", novo.nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[totalItensVetor] = novo;
    totalItensVetor++;

    printf("\nItem inserido com sucesso!\n");
}

void removerItemVetor() {
    char nome[30];
    printf("\nDigite o nome do item para remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j+1];
            }
            totalItensVetor--;
            printf("\nItem removido!\n");
            return;
        }
    }

    printf("\nItem não encontrado!\n");
}

void listarItensVetor() {
    printf("\n====== Itens no Vetor ======\n");
    for (int i = 0; i < totalItensVetor; i++) {
        printf("%d) %s - %s - Qtd: %d\n",
            i + 1,
            mochilaVetor[i].nome,
            mochilaVetor[i].tipo,
            mochilaVetor[i].quantidade
        );
    }
}

int buscarSequencialVetor(char* nomeBuscado) {
    comparacoes = 0;

    for (int i = 0; i < totalItensVetor; i++) {
        comparacoes++;

        if (strcmp(mochilaVetor[i].nome, nomeBuscado) == 0)
            return i;
    }
    return -1;
}


// ======================================================
//      LISTA ENCADEADA - INSERIR / REMOVER / BUSCAR
// ======================================================

void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));

    printf("\nNome do item: ");
    scanf(" %[^\n]", novo->dados.nome);

    printf("Tipo: ");
    scanf(" %[^\n]", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = inicioLista;
    inicioLista = novo;

    printf("\nItem inserido na lista!\n");
}

void removerItemLista() {
    char nome[30];
    printf("\nNome do item a remover (lista): ");
    scanf(" %[^\n]", nome);

    No* atual = inicioLista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                inicioLista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("\nItem removido!\n");
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    printf("\nItem não encontrado!\n");
}

void listarLista() {
    printf("\n====== Itens na Lista Encadeada ======\n");
    No* aux = inicioLista;

    while (aux != NULL) {
        printf("%s - %s - Qtd: %d\n",
               aux->dados.nome,
               aux->dados.tipo,
               aux->dados.quantidade);

        aux = aux->proximo;
    }
}

int buscarLista(char* nomeBuscado) {
    comparacoes = 0;
    No* aux = inicioLista;

    while (aux != NULL) {
        comparacoes++;
        if (strcmp(aux->dados.nome, nomeBuscado) == 0)
            return 1;

        aux = aux->proximo;
    }

    return 0;
}


// ======================================================
//      DESAFIO FINAL — COMPONENTES DA TORRE
// ======================================================

// ---- Bubble Sort por nome ----
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++;

            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}

// ---- Insertion Sort por tipo ----
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = chave;
    }
}

// ---- Selection Sort por prioridade ----
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        int minIndice = i;

        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[minIndice].prioridade)
                minIndice = j;
        }

        if (minIndice != i) {
            Componente temp = v[i];
            v[i] = v[minIndice];
            v[minIndice] = temp;
        }
    }
}

// ---- Busca Binária por nome ----
int buscaBinariaPorNome(Componente v[], int n, char nome[]) {
    comparacoes = 0;

    int ini = 0, fim = n - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoes++;

        int cmp = strcmp(nome, v[meio].nome);

        if (cmp == 0)
            return meio;
        else if (cmp > 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

void mostrarComponentes(Componente v[], int n) {
    printf("\n===== Componentes =====\n");
    for (int i = 0; i < n; i++) {
        printf("%s | %s | Prioridade: %d\n",
               v[i].nome, v[i].tipo, v[i].prioridade);
    }
}


// ======================================================
//                     MENU PRINCIPAL
// ======================================================

void menuMochila() {
    int opc;

    do {
        printf("\n======== MOCHILA (Vetor/Lista) ========\n");
        printf("1 - Inserir item no vetor\n");
        printf("2 - Remover item do vetor\n");
        printf("3 - Listar itens do vetor\n");
        printf("4 - Buscar item no vetor\n");
        printf("5 - Inserir item na lista encadeada\n");
        printf("6 - Remover item da lista encadeada\n");
        printf("7 - Listar lista encadeada\n");
        printf("8 - Buscar item na lista encadeada\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        if (opc == 1) inserirItemVetor();
        else if (opc == 2) removerItemVetor();
        else if (opc == 3) listarItensVetor();
        else if (opc == 4) {
            char nome[30];
            printf("Nome para buscar: ");
            scanf(" %[^\n]", nome);
            int idx = buscarSequencialVetor(nome);
            printf(idx >= 0 ? "Encontrado!\n" : "Não encontrado!\n");
            printf("Comparações: %lld\n", comparacoes);
        }
        else if (opc == 5) inserirItemLista();
        else if (opc == 6) removerItemLista();
        else if (opc == 7) listarLista();
        else if (opc == 8) {
            char nome[30];
            printf("Nome: ");
            scanf(" %[^\n]", nome);
            int achou = buscarLista(nome);
            printf(achou ? "Encontrado!\n" : "Não encontrado!\n");
            printf("Comparações: %lld\n", comparacoes);
        }

    } while (opc != 0);
}



void menuComponentes() {
    Componente comp[20];
    int total = 0;
    int opc;

    do {
        printf("\n====== SISTEMA DA TORRE DE FUGA ======\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Listar componentes\n");
        printf("3 - Ordenar por nome (Bubble)\n");
        printf("4 - Ordenar por tipo (Insertion)\n");
        printf("5 - Ordenar por prioridade (Selection)\n");
        printf("6 - Buscar binária por nome\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        if (opc == 1) {
            if (total >= 20) {
                printf("\nLimite máximo atingido!\n");
                continue;
            }
            printf("Nome: ");
            scanf(" %[^\n]", comp[total].nome);
            printf("Tipo: ");
            scanf(" %[^\n]", comp[total].tipo);
            printf("Prioridade: ");
            scanf("%d", &comp[total].prioridade);
            total++;
        }

        else if (opc == 2)
            mostrarComponentes(comp, total);

        else if (opc == 3) {
            clock_t t = clock();
            bubbleSortNome(comp, total);
            t = clock() - t;
            mostrarComponentes(comp, total);
            printf("Comparações: %lld | Tempo: %.4f s\n",
                   comparacoes, ((float)t)/CLOCKS_PER_SEC);
        }

        else if (opc == 4) {
            clock_t t = clock();
            insertionSortTipo(comp, total);
            t = clock() - t;
            mostrarComponentes(comp, total);
            printf("Comparações: %lld | Tempo: %.4f s\n",
                   comparacoes, ((float)t)/CLOCKS_PER_SEC);
        }

        else if (opc == 5) {
            clock_t t = clock();
            selectionSortPrioridade(comp, total);
            t = clock() - t;
            mostrarComponentes(comp, total);
            printf("Comparações: %lld | Tempo: %.4f s\n",
                   comparacoes, ((float)t)/CLOCKS_PER_SEC);
        }

        else if (opc == 6) {
            char nome[30];
            printf("Buscar por nome: ");
            scanf(" %[^\n]", nome);

            int idx = buscaBinariaPorNome(comp, total, nome);

            if (idx >= 0)
                printf("\nItem encontrado: %s | Tipo: %s | Prioridade: %d\n",
                       comp[idx].nome, comp[idx].tipo, comp[idx].prioridade);
            else
                printf("\nItem NÃO encontrado!\n");

            printf("Comparações: %lld\n", comparacoes);
        }

    } while (opc != 0);
}



// ======================================================
//                       MAIN
// ======================================================

int main() {
    int opc;

    do {
        printf("\n================ SISTEMA COMPLETO ================\n");
        printf("1 - Mochila (vetor e lista encadeada)\n");
        printf("2 - Componentes da Torre de Fuga\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        if (opc == 1)
            menuMochila();

        else if (opc == 2)
            menuComponentes();

    } while (opc != 0);

    return 0;
}
