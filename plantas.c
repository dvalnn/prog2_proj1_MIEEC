/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

/**
 * @file plantas.h
 * @author Tiago Amorim (up202004720@edu.fe.up.pt) Lucas Freitas (up202006938@edu.fe.up.pt)
 * @brief implementação das funções da biblioteca plantas.h
 * @date 2021-03-21
 * 
 */

#include "plantas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes)
{
	//validação dos argumentos passados para a função
	if (strlen(ID) >= 10 || strlen(nome_cientifico) >= MAX_NAME || n_alcunhas < 0 || n_sementes < 0)
	{
		printf("\n[FATAL] - Argumentos inválidos.\n");
		return NULL;
	}

	planta *novaPlanta = calloc(1, sizeof(*novaPlanta)); // aloca e inicializa a 0 espaço para 1 elemento do tamanho apontado por novaPlanta.
	novaPlanta->alcunhas = NULL;						 // inicializa o vetor novaPlanta->alcunhas com tamanho 0 (NULL)

	strcpy(novaPlanta->ID, ID);
	strcpy(novaPlanta->nome_cientifico, nome_cientifico);
	novaPlanta->n_sementes = n_sementes;
	novaPlanta->n_alcunhas = n_alcunhas;

	//Não existem alcunhas - retorna nova planta com novaPlanta->alcunhas = NULL
	if (novaPlanta->n_alcunhas == 0)
		return novaPlanta;

	novaPlanta->alcunhas = calloc(novaPlanta->n_alcunhas, sizeof(novaPlanta->alcunhas));

	for (int i = 0; i < novaPlanta->n_alcunhas; i++)
	{
		novaPlanta->alcunhas[i] = calloc(1, strlen(alcunhas[i]) + 1);
		checkPtr(novaPlanta->alcunhas[i], MEMORY_ALOC_ERROR_MSG, str(novaPlanta->alcunhas[i]));
		strcpy(novaPlanta->alcunhas[i], alcunhas[i]);
	}

	return novaPlanta;
}

colecao *colecao_nova(const char *tipo_ordem)
{

	if (strlen(tipo_ordem) > 4)
	{
		printf("\n[FATAL] - Argumento inválido.\n");
		return NULL;
	}

	colecao *newCol;
	newCol = (colecao *)calloc(1, sizeof(*newCol));

	checkPtr(newCol, MEMORY_ALOC_ERROR_MSG, str(newCol));

	newCol->plantas = NULL;
	newCol->tamanho = 0;
	strcpy(newCol->tipo_ordem, tipo_ordem);

	return newCol;
}

int planta_insere(colecao *c, planta *p)
{
	return -1;
}

int colecao_tamanho(colecao *c)
{
	return -1;
}

colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem)
{
	return NULL;
}

planta *planta_remove(colecao *c, const char *nomep)
{
	return NULL;
}

int planta_apaga(planta *p)
{
	// if (p = NULL)
	// 	return -1;
	// //IMCOMPLETO -- NECESSITA DE REVISÃO
	// for (int i = 0; i < p->n_alcunhas; i++)
	// 	free(p->alcunhas[i]);
	// free(p->alcunhas);
	// free(p);

	return -1;	
}

int colecao_apaga(colecao *c)
{
	//IMCOMPLETO -- NECESSITA DE REVISÃO
	free(c);
	c = NULL;

	return 0;
}

int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam)
{
	return NULL;
}

int colecao_reordena(colecao *c, const char *tipo_ordem)
{
	return -1;
}

void checkPtr(void *ptr, const char *msg, const char *ptrName)
{
	if (ptr == NULL)
	{
		printf("%s", msg);
		printf("\n[INFO] - Erro originado por: \"%s\"\n", ptrName);
		exit(0);
	}
}