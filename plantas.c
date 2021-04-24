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
#define FALSE 0
#define TRUE 1

// * flags para função colecao_pesquisa
#define PESQUISA_ID 0
#define PESQUISA_NOME 1

#define MAX_ALCUNHAS 50

/**
 * @brief pesquisa binária
 * 
 * @param haystack colecao a precorrer
 * @param needle nome ou id da planta a encontrar na colecao
 * @param tipo_pesquisa flag para o tipo de pesquisa a ser feita
 * @return int posição do elemento encontrado ou -1 caso não exista
 */
int colecao_bin_search(const colecao *haystack, const char *needle, const char tipo_pesquisa) {
    int lower = 0;                      // limite inferior do vetor
    int upper = haystack->tamanho - 1;  // limite superior do vetor
    int current;
    int diff;  // resultado da comparação entre string

    while (lower <= upper) {
        current = (lower + upper) / 2;

        if (tipo_pesquisa == PESQUISA_NOME)
            diff = strcmp(haystack->plantas[current]->nome_cientifico, needle);
        else
            diff = strcmp(haystack->plantas[current]->ID, needle);

        if (diff == 0) {
            return current;
        }
        // diff > 0 visto que as coleções estão ordenadas alfabeticamente e A < Z
        else if (diff > 0) {
            upper = current - 1;  //descartar metade superior do vetor
        }

        else {
            lower = current + 1;  //descartar metade inferior do vetor
        }
    }
    return -1;  // não encontrado
}

/**
 * @brief pesquisa linear
 *
 * @param haystack colecao a precorrer
 * @param needle nome ou id da planta a encontrar na colecao
 * @param tipo_pesquisa 0 para pesquisar por ID, 1 para pesquisar por nome
 * @return int posição do planta encontrada ou -1 caso não exista
 */
int colecao_lin_search(const colecao *haystack, const char *needle, const char tipo_pesquisa) {
    for (int i = 0; i < haystack->tamanho; i++) {
        if (tipo_pesquisa == PESQUISA_NOME) {
            if (!strcmp(haystack->plantas[i]->nome_cientifico, needle))
                return i;
        } else if (!strcmp(haystack->plantas[i]->ID, needle))
            return i;
    }
    return -1;
}

/**
 * @brief Pesquisa a coleção com o algoritmo de pesquisa adequado (pesquisa linear ou binária) 
 * 
 * @param haystack colecao a precorrer
 * @param needle nome ou id da planta a encontrar na colecao
 * @param tipo_pesquisa 0 para pesquisar por ID, 1 para pesquisar por nome
 * @return int posição do planta encontrada ou -1 caso não exista
 */
int colecao_pesquisa(const colecao *haystack, const char *needle, const char tipo_pesquisa) {
    //criação de um function pointer para seletção da função de pesquisa
    //por default, o método de pesquisa a usar é pesquisa linear
    int (*pesquisa_func)(const colecao *haystack, const char *needle, const char tipo_pesquisa);
    pesquisa_func = colecao_lin_search;

    //verificação de se o tipo de ordenação coincide com o tipo de pesquisa desejado
    if (tipo_pesquisa == PESQUISA_ID) {
        if (!strcasecmp(haystack->tipo_ordem, "id"))
            pesquisa_func = colecao_bin_search;
    
    } else if (!strcasecmp(haystack->tipo_ordem, "nome"))
        pesquisa_func = colecao_bin_search;

    //pesquisa a coleção com o método de pesquisa adequado
    return pesquisa_func(haystack, needle, tipo_pesquisa);
}

/**
 * @brief imprime uma mensagem de erro passada como argumento e retorna True caso o pointer passado seja NULL
 * 
 * @param ptr pointer a verificar
 * @param msg mensagem de erro a imprimir caso ptr seja NULL
 * @param ptrName nome do ptr a imprimir com a mensagem de erro
 * @return int 1 se ocorrer um erro, senão retorna 0
 */
int check_ptr(void *ptr, const char *msg, const char *ptrName) {
    if (!ptr) {
        printf("%s", msg);
        printf("\n[INFO] - Erro originado por: \"%s\"\n", ptrName);
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief key para ao qsort utilizado em colecao_reordena - compara com base no ID das plantas
 * 
 * @param a planta "a" a ser comparadada
 * @param b planta "b" a ser comparada
 * @return strcmp(a, b)
 */
int qsort_key_ID(const void *a, const void *b) {
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
int qsort_key_nome(const void *a, const void *b) {
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
    int (*key_func)(const void *, const void *);

    if (!strcasecmp(tipo_ordem, "id"))
        key_func = qsort_key_ID;
    else if (!strcasecmp(tipo_ordem, "nome"))
        key_func = qsort_key_nome;
    else
        return -1;

    qsort(c->plantas, c->tamanho, sizeof(planta *), key_func);

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
 * @brief atualiza uma planta existente na coleção com novas sementes e/ou alcunhas
 * 
 * @param old apontador com os dados antigos a serem atualizados
 * @param new apontador com os novos dados
 * @return int: -1 se ocorrer erro, caso contrário devolve 1 
 */
int planta_atualiza(planta *old, planta *new) {
    //atualizar numero de sementes
    old->n_sementes += new->n_sementes;

    //caso não existam novas alcunhas não é necessário fazer mais nada
    if (!new->n_alcunhas)
        return 1;

    //alocar espaço no vetor alcunhas para os novos char*, é alocado espaço em excesso para facilitar a atualização
    old->alcunhas = (char **)realloc(old->alcunhas, sizeof(old->alcunhas) * (old->n_alcunhas + new->n_alcunhas));
    if (check_ptr(old->alcunhas, MEMORY_ALOC_ERROR_MSG, str(old->alcunhas)))
        return -1;

    //precorrer o vetor com as novas alcunhas
    for (int i = 0; i < new->n_alcunhas; i++) {
        int nova_alcunha = TRUE;
        for (int j = 0; j < old->n_alcunhas; j++) {
            //se a alcunha existir, flag = FALSE
            if (!strcmp(new->alcunhas[i], old->alcunhas[j])) {
                nova_alcunha = FALSE;
                break;
            }
        }
        //adicionar nova alcunha ao vetor
        if (nova_alcunha) {
            old->alcunhas[old->n_alcunhas] = (char *)calloc(1, strlen(new->alcunhas[i]) + 1);

            if (check_ptr(old->alcunhas[i], MEMORY_ALOC_ERROR_MSG, str(old->alcunhas[i])))
                return -1;

            strcpy(old->alcunhas[old->n_alcunhas], new->alcunhas[i]);
            old->n_alcunhas++;
        }
    }
    //realocar o vetor com o tamanho certo
    old->alcunhas = (char **)realloc(old->alcunhas, sizeof(old->alcunhas) * old->n_alcunhas);
    if (check_ptr(old->alcunhas, MEMORY_ALOC_ERROR_MSG, str(old->alcunhas)))
        return -1;

    return 1;
}
planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes) {
    //validação dos argumentos passados para a função
    if (!ID || !nome_cientifico || strlen(ID) >= 10 || strlen(nome_cientifico) >= MAX_NAME || n_alcunhas < 0 || n_sementes < 0) {
        printf("\n[ERRO] - Argumentos inválidos.\n");
        return NULL;
    }

    // aloca e inicializa a 0 espaço para 1 elemento do tamanho apontado por novaPlanta.
    planta *nova_planta = (planta *)calloc(1, sizeof(*nova_planta));
    // inicializa o vetor novaPlanta->alcunhas com tamanho 0 (NULL)
    nova_planta->alcunhas = NULL;

    strcpy(nova_planta->ID, ID);
    strcpy(nova_planta->nome_cientifico, nome_cientifico);
    nova_planta->n_sementes = n_sementes;
    nova_planta->n_alcunhas = n_alcunhas;

    //Não existem alcunhas - retorna nova planta com novaPlanta->alcunhas = NULL
    if (!alcunhas || !n_alcunhas)
        return nova_planta;
    //existem alcunhas, aloca espaço para o vetor **alcunhas
    nova_planta->alcunhas = (char **)calloc(nova_planta->n_alcunhas, sizeof(nova_planta->alcunhas));

    //precorrer as alcunhas dadas para inserir
    for (int i = 0; i < nova_planta->n_alcunhas; i++) {
        if (!alcunhas[i])
            break;
        //alocar espaço igual ao tamanho da string a ser inserida
        nova_planta->alcunhas[i] = (char *)calloc(1, (strlen(alcunhas[i]) + 1));
        if (check_ptr(nova_planta->alcunhas[i], MEMORY_ALOC_ERROR_MSG, str(nova_planta->alcunhas[i])))
            return NULL;
        strcpy(nova_planta->alcunhas[i], alcunhas[i]);
    }

    return nova_planta;
}

colecao *colecao_nova(const char *tipo_ordem) {
    //verificação da validade do argumento passado
    if (!tipo_ordem || (!strcasecmp(tipo_ordem, "id") && !strcasecmp(tipo_ordem, "nome"))) {
        printf("\n[ERRO] - Argumento inválido.\n");
        return NULL;
    }
    //alocar de espaço para uma coleção vazia
    colecao *new_col;
    new_col = (colecao *)calloc(1, sizeof(*new_col));
    //verificar se a alocação foi bem sucedida
    if (check_ptr(new_col, MEMORY_ALOC_ERROR_MSG, str(new_col)))
        return NULL;
    //inicialização do vetor plantas a NULL, visto que a coleção está vazia
    new_col->plantas = NULL;
    new_col->tamanho = 0;
    strcpy(new_col->tipo_ordem, tipo_ordem);

    return new_col;
}

int planta_insere(colecao *c, planta *p) {
    if (!c || !p)
        return -1;

    // caso especial: a coleção está vazia
    if (!c->plantas) {
        c->tamanho = 1;
        c->plantas = (planta **)calloc(1, sizeof(c->plantas));

        if (check_ptr(c->plantas, MEMORY_ALOC_ERROR_MSG, str(c->plantas)))
            return -1;

        c->plantas[0] = p;
        return 0;
    }
    //verificar a existência da planta.
    //strcasecmp utilizados para verificar qual o tipo de ordenação da coleção e chamar coleção_pesquisa
    //com o método de pesquisa mais rápido
    int pos = 0;
    if (!strcasecmp(c->tipo_ordem, "id"))
        pos = colecao_pesquisa(c, p->ID, PESQUISA_ID);
    else
        pos = colecao_pesquisa(c, p->nome_cientifico, PESQUISA_NOME);

    // planta existe, só necessita de ser atualizada.
    if (pos != -1)
        return planta_atualiza(c->plantas[pos], p);

    //planta nao existe, é necessário inserir no final e reordenar o vetor.
    //alocar memória para vetor com 1 elemento extra
    c->plantas = (planta **)realloc(c->plantas, sizeof(c->plantas) * (c->tamanho + 1));
    if (check_ptr(c->plantas, MEMORY_ALOC_ERROR_MSG, str(c->plantas)))
        return -1;

    c->plantas[c->tamanho] = p;
    c->tamanho += 1;

    colecao_ordena(c, c->tipo_ordem);

    return 0;
}

int colecao_tamanho(colecao *c) {
    if (c)
        return c->tamanho;
    return -1;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem) {
    if (!nome_ficheiro || !tipo_ordem) {
        printf("\n[ERRO] - Argumento inválido.\n");
        return NULL;
    }

    FILE *file;
    file = fopen(nome_ficheiro, "r");
    if (!file)
        return NULL;

    //declaração e inicialização de variáveis auxiliares
    char id[10] = {'\0'};
    char nome[MAX_NAME] = {'\0'};
    int n_sementes = 0;

    //criação de uma nova coleção vazia
    colecao *importada = colecao_nova(tipo_ordem);
    if (check_ptr(importada, COLECAO_CREATION_ERROR_MSG, str(colecao))) {
        fclose(file);
        file = NULL;
        return NULL;
    }

    //mais algumas variáveis auxiliares, flag guarda o character lido imediatamente após o número de sementes
    char flag;
    int linha = 0;
    int n_alcunhas;

    //alocar memória para vetor alcunhas auxiliar para guardar as alcunhas lidas -- vetor alocado para o máximo definido de alcunhas
    //para reduzir a quantidade total de operações de alocação de memória
    char **alcunhas = (char **)calloc(MAX_ALCUNHAS, sizeof(*alcunhas));

    // %9[^,] e  %199[^,] leem tudo até encontrar uma "," para um field with máximo de 9 e 199 char, respetivamente.
    // %*c lê e discarta o char "," que é usado para separar as strings.
    while (fscanf(file, "%9[^,] %*c %199[^,] %*c %d%c", id, nome, &n_sementes, &flag) == 4) {  //4 é o número de variáveis a serem lidas

        n_alcunhas = 0;
        linha++;
        planta *nova;
        // há alcunhas
        if (flag == ',') {
            // >= 1 em vez de == 2, caso não haja \n ou espaço após o valor final do ficheiro
            // nesta situação fscanf recebe EOF após ler a alcunha de modo que retorna 1 em vez de 2
            while (fscanf(file, "%99m[^,\n]%c", &alcunhas[n_alcunhas], &flag) >= 1) {
                n_alcunhas++;

                //não há mais alcunhas a ler no ficheiro, ou o número máximo permitido foi alcançado
                //no segundo caso, o comportamento do programa é indefinido
                if (flag != ',' || n_alcunhas == MAX_ALCUNHAS)
                    break;
            }
            //criação de uma planta nova com as informação lida do ficheiro
            nova = planta_nova(id, nome, alcunhas, n_alcunhas, n_sementes);

            //libertação da memória em alocada no vetor,
            //para não provocar problemas de memória na próxima iteração do loop
            for (int i = 0; i < n_alcunhas; i++) {
                free(alcunhas[i]);
                alcunhas[i] = NULL;
            }
        } else
            nova = planta_nova(id, nome, NULL, n_alcunhas, n_sementes);

        if (check_ptr(nova, PLANTA_CREATION_ERROR_MSG, str(planta * nova)))
            printf("\n[INFO] planta %s %s na linha %d do ficheiro %s não foi criada nem inserida no vetor com sucesso\n", id, nome, linha, nome_ficheiro);
        else {
            //planta criada é inserida na coleção, caso seja repetida a planta antiga é atualizada e a nova é apagada
            //em caso de erro, é imprimida uma mensagem de erro e a planta nova é apagada
            char tmp = planta_insere(importada, nova);
            if (tmp == -1)
                printf("\n[INFO] planta %s %s na linha %d do ficheiro %s não foi inserida no vetor com sucesso\n", id, nome, linha, nome_ficheiro);
            if (tmp)
                planta_apaga(nova);
        }
    }
    //libertação de memória do vetor **alcunhas alocado antes do loop ser iniciado
    free(alcunhas);

    fclose(file);
    file = NULL;
    return importada;
}

planta *planta_remove(colecao *c, const char *nomep) {
    if (!c || !nomep)
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
    if (check_ptr(c->plantas, MEMORY_ALOC_ERROR_MSG, str(c->plantas)))
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
    if (!c || !nomep)
        return NULL;
    //alocar memória para o vetor para guardar as posições encontradas
    int *posicoes = calloc(c->tamanho, sizeof(*posicoes));
    *tam = 0;

    for (int i = 0; i < c->tamanho; i++) {
        //pesquisa linear da coleção para encontrar todas as ocorrências
        if (!strcmp(c->plantas[i]->nome_cientifico, nomep)) {
            posicoes[*tam] = i;
            (*tam)++;
            continue;
        }
        //caso existam, pesquisa linear de todas as alcunhas da planta
        if (c->plantas[i]->n_alcunhas != 0) {
            for (int j = 0; j < c->plantas[i]->n_alcunhas; i++)
                if (!strcmp(c->plantas[i]->alcunhas[j], nomep)) {
                    posicoes[*tam] = i;
                    (*tam)++;
                    continue;
                }
        }
    }
    //caso não tenham sido encontradas quaisquer ocorrências
    //libertar o espaço alocado para o vetor e retornar NULL
    if (!(*tam)) {
        free(posicoes);
        return NULL;
    } else
        return posicoes;
}

int colecao_reordena(colecao *c, const char *tipo_ordem) {
    if (!c || !tipo_ordem)
        return -1;

    if (strcasecmp(tipo_ordem, "id") != 0 && strcasecmp(tipo_ordem, "nome") != 0)
        return -1;

    if (!strcasecmp(tipo_ordem, c->tipo_ordem))
        return 0;

    //Algoritmo de ordenação da coleção baseado no qsort da stdlib de C
    //De acordo com o tipo de ordenação da coleção, o qsort é chamado com a função key adequada
    return colecao_ordena(c, tipo_ordem);
}

//* undefine dos macros criados para não afetarem para os restantes ficheiros
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