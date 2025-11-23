/*
  Módulo: Priorização e Montagem da Torre de Resgate
  Autor: (Você)
  Objetivo: implementar bubble, insertion e selection sorts com contagem de comparações,
            medir tempo com clock(), e realizar busca binária por nome.
  Observações:
    - Usa fgets() para entrada de strings.
    - Máximo de 20 componentes.
    - Busca binária só é válida se os dados estiverem ordenados por nome.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define STRLEN_NOME 30
#define STRLEN_TIPO 20

typedef struct {
    char nome[STRLEN_NOME];
    char tipo[STRLEN_TIPO];
    int prioridade; // 1 a 10
} Componente;

/* ----- Prototipação ----- */
void limparBufferEntrada(void);
void cadastrarComponente(Componente comps[], int *n);
void mostrarComponentes(const Componente comps[], int n);
void bubbleSortNome(Componente comps[], int n, long *comparacoes);
void insertionSortTipo(Componente comps[], int n, long *comparacoes);
void selectionSortPrioridade(Componente comps[], int n, long *comparacoes);
int buscaBinariaPorNome(const Componente comps[], int n, const char chave[], long *comparacoes);
void medirTempo(void (*algoritmo)(Componente*, int, long*), Componente comps[], int n, long *comparacoes, double *segundos);

/* ----- Funções auxiliares ----- */

// Remove '\n' de fgets (se presente)
void trim_newline(char *s) {
    size_t l = strlen(s);
    if (l > 0 && s[l-1] == '\n') s[l-1] = '\0';
}

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/* ----- Cadastro e visualização ----- */

void cadastrarComponente(Componente comps[], int *n) {
    if (*n >= MAX_COMPONENTES) {
        printf("Limite de componentes (%d) atingido.\n", MAX_COMPONENTES);
        return;
    }

    Componente novo;
    printf("Nome do componente: ");
    if (fgets(novo.nome, STRLEN_NOME, stdin) == NULL) return;
    trim_newline(novo.nome);

    printf("Tipo (controle/suporte/propulsao/etc): ");
    if (fgets(novo.tipo, STRLEN_TIPO, stdin) == NULL) return;
    trim_newline(novo.tipo);

    char linha[32];
    int valido = 0;
    while (!valido) {
        printf("Prioridade (1 a 10): ");
        if (fgets(linha, sizeof(linha), stdin) == NULL) return;
        novo.prioridade = atoi(linha);
        if (novo.prioridade >= 1 && novo.prioridade <= 10) valido = 1;
        else printf("Prioridade inválida. Digite um número entre 1 e 10.\n");
    }

    comps[*n] = novo;
    (*n)++;
    printf("Componente cadastrado com sucesso!\n");
}

void mostrarComponentes(const Componente comps[], int n) {
    if (n == 0) {
        printf("[Nenhum componente cadastrado]\n");
        return;
    }
    printf("\n--- COMPONENTES (total: %d) ---\n", n);
    printf("%-3s | %-28s | %-12s | %-9s\n", " #", "NOME", "TIPO", "PRIORIDADE");
    printf("----+------------------------------+--------------+----------\n");
    for (int i = 0; i < n; ++i) {
        printf("%3d | %-28s | %-12s | %9d\n", i+1, comps[i].nome, comps[i].tipo, comps[i].prioridade);
    }
    printf("-------------------------------\n");
}

/* ----- Algoritmos de ordenação (com contagem de comparações) ----- */

/*
  Bubble Sort por nome (lexicográfico).
  Conta cada comparação entre strings (strcmp).
*/
void bubbleSortNome(Componente comps[], int n, long *comparacoes) {
    *comparacoes = 0;
    if (n <= 1) return;

    for (int i = 0; i < n - 1; ++i) {
        int trocou = 0;
        for (int j = 0; j < n - 1 - i; ++j) {
            (*comparacoes)++;
            if (strcmp(comps[j].nome, comps[j+1].nome) > 0) {
                Componente tmp = comps[j];
                comps[j] = comps[j+1];
                comps[j+1] = tmp;
                trocou = 1;
            }
        }
        if (!trocou) break; // otimização: se nenhuma troca, já ordenado
    }
}

/*
  Insertion Sort por tipo (lexicográfico).
  Conta comparações de strings (strcmp) realizadas ao "inserir".
*/
void insertionSortTipo(Componente comps[], int n, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < n; ++i) {
        Componente chave = comps[i];
        int j = i - 1;

        // enquanto j >=0 e comps[j].tipo > chave.tipo
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(comps[j].tipo, chave.tipo) > 0) {
                comps[j+1] = comps[j];
                j--;
            } else break;
        }
        comps[j+1] = chave;
    }
}

/*
  Selection Sort por prioridade (inteiro) - ordena do maior para o menor
  (maior prioridade primeiro) — você pode inverter conforme desejar.
  Conta comparações entre inteiros.
*/
void selectionSortPrioridade(Componente comps[], int n, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n - 1; ++i) {
        int idxMaior = i;
        for (int j = i + 1; j < n; ++j) {
            (*comparacoes)++;
            if (comps[j].prioridade > comps[idxMaior].prioridade) {
                idxMaior = j;
            }
        }
        if (idxMaior != i) {
            Componente tmp = comps[i];
            comps[i] = comps[idxMaior];
            comps[idxMaior] = tmp;
        }
    }
}

/* ----- Busca binária por nome (apenas após ordenação por nome) ----- */
/*
  Retorna índice (0..n-1) se encontrado, -1 se não encontrado.
  Conta comparações de strcmp (cada comparação com o meio).
*/
int buscaBinariaPorNome(const Componente comps[], int n, const char chave[], long *comparacoes) {
    int inicio = 0, fim = n - 1;
    *comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(chave, comps[meio].nome);
        if (cmp == 0) return meio;
        if (cmp > 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

/* ----- Medição de tempo para algoritmo de ordenação ----- */
/*
  Função genérica que mede o tempo (em segundos) de um algoritmo de ordenação
  com assinatura: void algoritmo(Componente*, int, long*)
*/
void medirTempo(void (*algoritmo)(Componente*, int, long*), Componente comps[], int n, long *comparacoes, double *segundos) {
    clock_t t0 = clock();
    algoritmo(comps, n, comparacoes);
    clock_t t1 = clock();
    *segundos = ((double)(t1 - t0)) / CLOCKS_PER_SEC;
}

/* ----- Programa principal com menu ----- */

int main(void) {
    Componente componentes[MAX_COMPONENTES];
    int total = 0;
    int opcao;
    int ordenadoPorNome = 0; // flag para permitir busca binária

    setbuf(stdout, NULL); // para evitar buffering inesperado em alguns terminais

    do {
        printf("\n=== MONTAGEM DA TORRE DE RESGATE ===\n");
        printf("1 - Cadastrar componente (max %d)\n", MAX_COMPONENTES);
        printf("2 - Mostrar componentes\n");
        printf("3 - Ordenar por NOME (Bubble Sort)\n");
        printf("4 - Ordenar por TIPO (Insertion Sort)\n");
        printf("5 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6 - Busca binária por NOME (requer ordenado por nome)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida.\n");
            limparBufferEntrada();
            continue;
        }
        limparBufferEntrada(); // retira '\n' restante

        if (opcao == 1) {
            cadastrarComponente(componentes, &total);
            ordenadoPorNome = 0;
        } else if (opcao == 2) {
            mostrarComponentes(componentes, total);
        } else if (opcao == 3) {
            long comps = 0;
            double tempo = 0.0;
            medirTempo(bubbleSortNome, componentes, total, &comps, &tempo);
            printf("\n[Bubble Sort por NOME] Comparacoes: %ld | Tempo: %.6f s\n", comps, tempo);
            mostrarComponentes(componentes, total);
            ordenadoPorNome = 1;
        } else if (opcao == 4) {
            long comps = 0;
            double tempo = 0.0;
            medirTempo(insertionSortTipo, componentes, total, &comps, &tempo);
            printf("\n[Insertion Sort por TIPO] Comparacoes: %ld | Tempo: %.6f s\n", comps, tempo);
            mostrarComponentes(componentes, total);
            ordenadoPorNome = 0;
        } else if (opcao == 5) {
            long comps = 0;
            double tempo = 0.0;
            medirTempo(selectionSortPrioridade, componentes, total, &comps, &tempo);
            printf("\n[Selection Sort por PRIORIDADE (maior->menor)] Comparacoes: %ld | Tempo: %.6f s\n", comps, tempo);
            mostrarComponentes(componentes, total);
            ordenadoPorNome = 0;
        } else if (opcao == 6) {
            if (!ordenadoPorNome) {
                printf("Atenção: para usar busca binária é necessário ordenar por NOME primeiro (opção 3).\n");
            } else {
                char chave[STRLEN_NOME];
                printf("Digite o NOME do componente-chave para buscar: ");
                if (fgets(chave, STRLEN_NOME, stdin) == NULL) continue;
                trim_newline(chave);

                long comparacoes = 0;
                int idx = buscaBinariaPorNome(componentes, total, chave, &comparacoes);
                if (idx >= 0) {
                    printf("\nComponente-CHAVE encontrado no índice %d (1-based %d):\n", idx, idx+1);
                    printf("Nome: %s | Tipo: %s | Prioridade: %d\n", componentes[idx].nome, componentes[idx].tipo, componentes[idx].prioridade);
                } else {
                    printf("\nComponente-CHAVE não encontrado.\n");
                }
                printf("Comparacoes na busca binaria: %ld\n", comparacoes);
            }
        } else if (opcao == 0) {
            printf("Encerrando módulo da torre...\n");
        } else {
            printf("Opcao inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
