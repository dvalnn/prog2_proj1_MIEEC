/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

/**
 * @file plantas.h
 * @author Tiago Amorim  (up202004720@edu.fe.up.pt | https://github.com/dvalnn/prog2_proj1_MIEEC) 
           Lucas Freitas (up202006938@edu.fe.up.pt | )
 * @brief implementação das funções da biblioteca plantas.h - grupo g209
 * @date 2021-03-21
 * 
 */

#include "plantas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// * útil para dar print do nome do argumento c passado
#define str(c) #c

// * mensagens de erro
#define MEMORY_ALOC_ERROR_MSG "\n[ERRO] - Falha ao alocar memória.\n"
#define PLANTA_UPDATE_ERROR_MSG "\n[ERRO]  - Falha ao atualizar a planta\n"
#define COLECAO_CREATION_ERROR_MSG "\n[ERRO] - Falha ao criar a coleção\n"
#define PLANTA_CREATION_ERROR_MSG "\n[ERRO] - Falha ao criar a planta\n"

// * macros para evitar incluir <stdbool.h> desnecessariamente
#define TRUE 1
#define FALSE 0

// * flags para função colecao_pesquisa
#define PESQUISA_ID 0
#define PESQUISA_NOME 1

#define MAX_ALCUNHAS 10

/**
 * @brief 
 * 
 * @param haystack 
 * @param needle 
 * @param tipo_pesquisa 
 * @return int 
 */
int binSearch(const colecao *haystack, const char *needle, const char tipo_pesquisa) {
    int lower = 0;                      // limite inferior do vetor
    int upper = haystack->tamanho - 1;  // limite superior do vetor
    int current;
    int diff;  // resultado da comparação entre string

    while (lower <= upper) {
        current = (lower + upper) / 2;

        if (tipo_pesquisa == PESQUISA_NOME)
            diff = strcmp(haystack->plantas[current]->nome_cientifico, needle);
        else
            //-strcmp visto que ordenação por ID é decrescente
            diff = strcmp(haystack->plantas[current]->ID, needle);

        if (diff == 0) {
            return current;
        }

        else if (diff > 0) {
            upper = current - 1;
        }

        else {
            lower = current + 1;
        }
    }
    return -1;  // não encontrado
}

/**
 * @brief 
 *
 * @param haystack 
 * @param needle ID ou nome a pesquisar na string
 * @param tipo_pesquisa 0 para pesquisar por ID, 1 para pesquisar por nome
 * @return int retorna a posição da planta se existir,senão retorna -1
 */
int lSearch(const colecao *haystack, const char *needle, const char tipo_pesquisa) {
    if (tipo_pesquisa == PESQUISA_NOME) {
        for (int i = 0; i < haystack->tamanho; i++)
            if (!strcmp(haystack->plantas[i]->nome_cientifico, needle))
                return i;
    } else {
        for (int i = 0; i < haystack->tamanho; i++)
            if (!strcmp(haystack->plantas[i]->ID, needle))
                return i;
    }
    return -1;
}

/**
 * @brief 
 * 
 * @param haystack 
 * @param needle 
 * @param tipo_pesquisa 
 * @return int 
 */
int colecao_pesquisa(const colecao *haystack, const char *needle, const char tipo_pesquisa) {
    char sorted = FALSE;

    //verificação de se o tipo de ordenação coincide com o tipo de pesquisa desejado
    if (tipo_pesquisa == PESQUISA_ID) {
        if (!strcasecmp(haystack->tipo_ordem, "id"))
            sorted = TRUE;
    } else if (!strcasecmp(haystack->tipo_ordem, "nome"))
        sorted = TRUE;

    //caso os tipos de ordenação coincidam, utilizar pesquisa binária, senão pesquisa linear
    if (sorted)
        return binSearch(haystack, needle, tipo_pesquisa);
    else
        return lSearch(haystack, needle, tipo_pesquisa);
}

/**
 * @brief verifica se o pointer é NULL e termina o programa caso a condição se verifique
 * 
 * @param ptr pointer a verificar
 * @param msg mensagem de erro a imprimir caso ptr seja NULL
 * @param ptrName nome do ptr a imprimir com a mensagem de erro
 * @return int 1 se ocorrer um erro, senão retorna 0
 */
int checkPtr(void *ptr, const char *msg, const char *ptrName) {
    if (!ptr) {
        printf("%s", msg);
        printf("\n[INFO] - Erro originado por: \"%s\"\n", ptrName);
        return 1;
    }
    return 0;
}

/**
 * @brief key para ao qsort utilizado em colecao_reordena - compara com base no ID das plantas
 * 
 * @param a planta "a" a ser comparadada
 * @param b planta "b" a ser comparada
 * @return strcmp(a, b)
 */
int qsortKey_ID(const void *a, const void *b) {
    //cast dos pointers void* para planta** e de seguida desreferenciação para planta*, de modo a poder aceder aos dados corretamente
    const planta *pa = *(planta **)a;
    const planta *pb = *(planta **)b;
    //valor do strcmp multilicado por -1 para que a ordenação seja decrescente
    return strcmp(pa->ID, pb->ID);
}

/**
 * @brief key para o qsort utilizado em colecao_reordena - compara com base no nome científico das plantas
 * 
 * @param a planta "a" a ser comparada
 * @param b planta "b" a ser comparada
 * @return strcmp(a, b)
 */
int qsortKey_nome(const void *a, const void *b) {
    //cast dos pointers void* para planta** e de seguida desreferenciação para planta*, de modo a poder aceder aos dados corretamente
    const planta *pa = *(planta **)a;
    const planta *pb = *(planta **)b;
    //valor do strcmp multilicado por -1 para que a ordenação seja decrescente
    return strcmp(pa->nome_cientifico, pb->nome_cientifico);
}

/**
 * @brief ordena a coleção usando qsort e a função key adequada
 * 
 * @param c Coleção a ordenar
 * @param tipo_ordem Ordem a ser introduzida na coleção
 * @return int 1 se ocorrer erro, senão retorna 0
 */
int colecao_ordena(colecao *c, const char *tipo_ordem) {
    if (!strcasecmp(tipo_ordem, "id"))
        qsort(c->plantas, c->tamanho, sizeof(planta *), qsortKey_ID);
    else if (!strcasecmp(tipo_ordem, "nome"))
        qsort(c->plantas, c->tamanho, sizeof(planta *), qsortKey_nome);
    else
        return -1;

    return 0;
}

/**
 * @brief Troca a posição das duas plantas inseridas
 * 
 * @param a planta** a
 * @param b planta** b
 */
void swap_plantas(planta **a, planta **b) {
    planta *aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

/**
 * @brief 
 * 
 * @param old apontador com os dados antigos a serem atualizados
 * @param new apontador com os novos dados
 * @return int: -1 se ocorrer erro, caso contrário devolve 1 
 */
int planta_atualiza(planta *old, planta *new) {
    //atualizar numero de sementes
    old->n_sementes += new->n_sementes;

    if (!new->n_alcunhas)
        return 1;

    //alocar espaço no vetor alcunhas para os novos char*, é alocado espaço em excesso para facilitar a atualização
    old->alcunhas = (char **)realloc(old->alcunhas, sizeof(old->alcunhas) * (old->n_alcunhas + new->n_alcunhas));
    if (checkPtr(old->alcunhas, MEMORY_ALOC_ERROR_MSG, str(old->alcunhas)))
        return -1;

    //precorrer o vetor com as novas alcunhas
    for (int i = 0; i < new->n_alcunhas; i++) {
        int novaAlcunha = TRUE;
        for (int j = 0; j < old->n_alcunhas; j++) {
            //se a alcunha existir, flag = FALSE
            if (!strcmp(new->alcunhas[i], old->alcunhas[j])) {
                novaAlcunha = FALSE;
                break;
            }
        }
        //adicionar nova alcunha ao vetor
        if (novaAlcunha) {
            old->alcunhas[old->n_alcunhas] = (char *)calloc(1, strlen(new->alcunhas[i]) + 1);

            if (checkPtr(old->alcunhas[i], MEMORY_ALOC_ERROR_MSG, str(old->alcunhas[i])))
                return -1;

            strcpy(old->alcunhas[old->n_alcunhas], new->alcunhas[i]);
            old->n_alcunhas++;
        }
    }
    //realocar o vetor com o tamanho certo
    old->alcunhas = (char **)realloc(old->alcunhas, sizeof(old->alcunhas) * old->n_alcunhas);
    if (checkPtr(old->alcunhas, MEMORY_ALOC_ERROR_MSG, str(old->alcunhas)))
        return -1;

    return 1;
}

planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes) {
    //validação dos argumentos passados para a função
    if (strlen(ID) >= 10 || strlen(nome_cientifico) >= MAX_NAME || n_alcunhas < 0 || n_sementes < 0) {
        printf("\n[ERRO] - Argumentos inválidos.\n");
        return NULL;
    }

    // aloca e inicializa a 0 espaço para 1 elemento do tamanho apontado por novaPlanta.
    planta *novaPlanta = (planta *)calloc(1, sizeof(*novaPlanta));
    // inicializa o vetor novaPlanta->alcunhas com tamanho 0 (NULL)
    novaPlanta->alcunhas = NULL;

    strcpy(novaPlanta->ID, ID);
    strcpy(novaPlanta->nome_cientifico, nome_cientifico);
    novaPlanta->n_sementes = n_sementes;
    novaPlanta->n_alcunhas = n_alcunhas;

    //Não existem alcunhas - retorna nova planta com novaPlanta->alcunhas = NULL
    if (!alcunhas || !n_alcunhas)
        return novaPlanta;
    //existem alcunhas, aloca espaço para o vetor **alcunhas
    novaPlanta->alcunhas = (char **)calloc(novaPlanta->n_alcunhas, sizeof(novaPlanta->alcunhas));

    for (int i = 0; i < novaPlanta->n_alcunhas; i++) {
        if (!alcunhas[i])
            break;
        novaPlanta->alcunhas[i] = (char *)calloc(1, (strlen(alcunhas[i]) + 1));
        if (checkPtr(novaPlanta->alcunhas[i], MEMORY_ALOC_ERROR_MSG, str(novaPlanta->alcunhas[i])))
            return NULL;
        strcpy(novaPlanta->alcunhas[i], alcunhas[i]);
    }

    return novaPlanta;
}

colecao *colecao_nova(const char *tipo_ordem) {
    if (!strcasecmp(tipo_ordem, "id") && !strcasecmp(tipo_ordem, "nome")) {
        printf("\n[ERRO] - Argumento inválido.\n");
        return NULL;
    }

    colecao *newCol;
    newCol = (colecao *)calloc(1, sizeof(*newCol));

    if (checkPtr(newCol, MEMORY_ALOC_ERROR_MSG, str(newCol)))
        return NULL;

    newCol->plantas = NULL;
    newCol->tamanho = 0;
    strcpy(newCol->tipo_ordem, tipo_ordem);

    return newCol;
}

int planta_insere(colecao *c, planta *p) {
    if (!p)
        return -1;

    // caso especial: a coleção está vazia
    if (!c->plantas) {
        c->tamanho = 1;
        c->plantas = (planta **)calloc(1, sizeof(c->plantas));

        if (checkPtr(c->plantas, MEMORY_ALOC_ERROR_MSG, str(c->plantas)))
            return -1;

        c->plantas[0] = p;
        return 0;
    }

    int pos = 0;
    // planta existe, só necessita de ser atualizada.

    if ((pos = colecao_pesquisa(c, p->ID, PESQUISA_ID)) != -1)
        return planta_atualiza(c->plantas[pos], p);

    //planta nao existe, é necessário inserir na posição certa.
    //alocar memória para vetor com 1 elemento extra
    c->plantas = (planta **)realloc(c->plantas, sizeof(c->plantas) * (c->tamanho + 1));
    if (checkPtr(c->plantas, MEMORY_ALOC_ERROR_MSG, str(c->plantas)))
        return -1;

    //inserir na última posição
    c->plantas[c->tamanho] = p;
    c->tamanho += 1;

    // ordenar as plantas --- acaba
    colecao_ordena(c, c->tipo_ordem);

    return 0;
}

int colecao_tamanho(colecao *c) {
    if (c)
        return c->tamanho;
    return -1;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem) {
    FILE *file;
    file = fopen(nome_ficheiro, "r");
    if (file == NULL)
        return NULL;

    char id[10] = {'\0'};
    char nome[MAX_NAME] = {'\0'};
    int n_sementes = 0;

    colecao *importada = colecao_nova(tipo_ordem);
    if (checkPtr(importada, COLECAO_CREATION_ERROR_MSG, str(colecao))) {
        fclose(file);
        file = NULL;
        return NULL;
    }

    char flag;
    int n_alcunhas;
    char **alcunhas = (char **)calloc(MAX_ALCUNHAS, sizeof(*alcunhas));
    char aux[MAX_NAME / 2] = {0};
    int linha = 0;

    // %9[^,] e  %199[^,] leem tudo até encontrar uma "," para um field with máximo de 9 e 199 char, respetivamente.
    // %*c lê e discarta o char "," que é usado para separar as strings.
    while (fscanf(file, "%9[^,] %*c %199[^,] %*c %d%c", id, nome, &n_sementes, &flag) == 4) {  //4 é o número de variáveis a serem lidas

        n_alcunhas = 0;
        linha++;
        planta *nova;
        // há alcunhas
        if (flag == ',') {
            // >= 1 em vez de == 2, caso não haja \n ou espaço após o valor final do ficheiro
            while (fscanf(file, "%99[^,\n]%c", aux, &flag) >= 1) {
                alcunhas[n_alcunhas] = (char *)calloc(1, strlen(aux) + 1);
                strcpy(alcunhas[n_alcunhas], aux);
                n_alcunhas++;
                if (flag != ',' || n_alcunhas == MAX_ALCUNHAS)
                    break;
            }
            nova = planta_nova(id, nome, alcunhas, n_alcunhas, n_sementes);
            for (int i = 0; i < n_alcunhas; i++) {
                free(alcunhas[i]);
                alcunhas[i] = NULL;
            }
        } else
            nova = planta_nova(id, nome, NULL, n_alcunhas, n_sementes);

        if (checkPtr(nova, PLANTA_CREATION_ERROR_MSG, str(planta * nova)))
            printf("\n[INFO] planta %s %s na linha %d do ficheiro %s não foi criada\n", id, nome, linha, nome_ficheiro);
        else {
            char tmp = planta_insere(importada, nova);
            if (tmp == -1)
                printf("\n[INFO] planta %s %s na linha %d do ficheiro %s não foi criada\n", id, nome, linha, nome_ficheiro);
            if (tmp)
                planta_apaga(nova);
        }
    }
    free(alcunhas);
    colecao_ordena(importada, importada->tipo_ordem);

    fclose(file);
    file = NULL;
    return importada;
}

planta *planta_remove(colecao *c, const char *nomep) {
    if (!c)
        return NULL;

    int pos = 0;
    if ((pos = colecao_pesquisa(c, nomep, PESQUISA_NOME)) == -1)
        return NULL;

    //criar uma cópia da panta a remover, para não perder os dados
    planta *removida = planta_nova(c->plantas[pos]->ID,
                                   c->plantas[pos]->nome_cientifico,
                                   c->plantas[pos]->alcunhas,
                                   c->plantas[pos]->n_alcunhas,
                                   c->plantas[pos]->n_sementes);

    //decrementar o tamanho do vetor
    c->tamanho--;
    //a planta a remover não está na última posição, é necessário trocar
    if (pos != c->tamanho)
        swap_plantas(&c->plantas[pos], &c->plantas[c->tamanho]);

    //remover a planta do final
    planta_apaga(c->plantas[c->tamanho]);
    c->plantas[c->tamanho] = NULL;

    //realoca o espaço do vetor para 1 elemento a menos;
    c->plantas = (planta **)realloc(c->plantas, sizeof(c->plantas) * (c->tamanho));
    if (checkPtr(c->plantas, MEMORY_ALOC_ERROR_MSG, str(c->plantas)))
        return NULL;

    //caso a planta não tenha sido da última ou da penúltima posição do vetor, é necessário reordenar
    if (pos != c->tamanho || pos != c->tamanho - 1)
        colecao_ordena(c, c->tipo_ordem);

    //retorna a cópia criada da planta removida da colecao
    return removida;
}

int planta_apaga(planta *p) {
    //se p for NULL, não é preciso dar free a nada
    if (!p)
        return -1;
    //free todos os elementos char* do vetor char **alcunhas
    for (int i = 0; i < p->n_alcunhas; i++)
        free(p->alcunhas[i]);

    //free char **alcunhas
    free(p->alcunhas);

    free(p);

    //deixar o pointer como NULL, para evitar comportamentos imprevistos
    p = NULL;
    return 0;
}

int colecao_apaga(colecao *c) {
    //se c for NULL, n é preciso dar free a nada
    if (!c)
        return -1;

    //free todos os planta* do vetor planta **plantas da coleção c
    for (int i = 0; i < c->tamanho; i++)
        planta_apaga(c->plantas[i]);

    //free pointer **plantas
    free(c->plantas);

    free(c);

    //deixar o pointer como NULL, para evitar comportamentos imprevistos
    c = NULL;
    return 0;
}

int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam) {
    if (!c)
        return NULL;

    int *posicoes = calloc(c->tamanho, sizeof(*posicoes));
    *tam = 0;

    for (int i = 0; i < c->tamanho; i++) {
        if (!strcmp(c->plantas[i]->nome_cientifico, nomep)) {
            posicoes[*tam] = i;
            (*tam)++;
            continue;
        }
        if (c->plantas[i]->n_alcunhas != 0) {
            for (int j = 0; j < c->plantas[i]->n_alcunhas; i++)
                if (!strcmp(c->plantas[i]->alcunhas[j], nomep)) {
                    posicoes[*tam] = i;
                    (*tam)++;
                    continue;
                }
        }
    }

    if (!(*tam)) {
        free(posicoes);
        return NULL;
    } else
        return posicoes;
}

int colecao_reordena(colecao *c, const char *tipo_ordem) {
    if (!c)
        return -1;

    if (strcasecmp(tipo_ordem, "id") != 0 && strcasecmp(tipo_ordem, "nome") != 0)
        return -1;

    if (!strcasecmp(tipo_ordem, c->tipo_ordem))
        return 0;

    //Algoritmo de ordenação da coleção baseado no qsort da stdlib de C
    //De acordo com o tipo de ordenação da coleção, o qsort é chamado com a função key adequada
    return colecao_ordena(c, tipo_ordem);
}

//* undef dos macros criados para não passarem para os restantes ficheiros
#undef str

#undef MEMORY_ALOC_ERROR_MSG
#undef PLANTA_UPDATE_ERROR_MSG
#undef COLECAO_CREATION_ERROR_MSG
#undef PLANTA_CREATION_ERROR_MSG

#undef TRUE
#undef FALSE

#undef PESQUISA_ID
#undef PESQUISA_NOME

#undef MAX_ALCUNHAS