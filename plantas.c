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
	// planta *elemento;
	// strcpy(elemento->ID,ID); //? ID
	// strcpy(elemento->nome_cientifico,nome_cientifico); //? Nome cientifico

	// elemento->n_alcunhas = n_alcunhas;	//? número de alcunhas

	// //? Alcunhas

	// if(elemento->alcunhas != NULL) //Existem alcunhas
	// {
	// 	int *aux = elemento->alcunhas;
	// 	aux = calloc(n_alcunhas, sizeof(*aux)); //! calloc ou malloc?

	// 		if (aux == NULL)
	// 			{
	// 				printf("\n[FATAL] - Erro ao alocar memória.\n");
	// 				return NULL;
	// 			}

	// 		for(int i = 0; i < n_alcunhas;i++)
	// 			{
	// 				aux = elemento->alcunhas[i];
	// 				aux = calloc(strlen(aux),sizeof(char)); //! calloc ou malloc?

	// 					if (aux == NULL)
	// 						{
	// 							printf("\n[FATAL] - Erro ao alocar memória.\n");
	// 							return NULL;
	// 						}
	// 				strcpy(elemento->alcunhas[i], alcunhas[i]);
	// 			}
	// }
	// elemento->n_sementes = n_sementes;	//? número de sementes

	// // free(aux); ????

	// return elemento;
	return NULL;
}

colecao *colecao_nova(const char *tipo_ordem)
{

	if (strlen(tipo_ordem) > 4)
	{
		printf("\n[FATAL] - Tipo de ordenação inválido.\n");
		return NULL;
	}

	colecao *newCol;
	newCol = (colecao *)calloc(1, sizeof(*newCol));

	if (newCol == NULL)
	{
		printf("\n[FATAL] - Erro ao alocar memória.\n");
		return NULL;
	}

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
