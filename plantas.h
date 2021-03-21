/*****************************************************************/
/*          Biblioteca plantas | PROG2 | MIEEC | 2020/21         */
/*****************************************************************/

/**
 * @file plantas.h
 * @author Tiago Amorim (up202004720@edu.fe.up.pt) Lucas Freitas (up202006938@edu.fe.up.pt)
 * @brief declarações das funções da biblioteca do vetor colecao e dos elementos planta
 * @date 2021-03-21
 * 
 */

#ifndef PLANTAS_H
#define MAX_NAME 200

/**
 * @brief registo para armazenar elementos do vetor dinamico. ||  
 *        Este registo contem duas strings (ID e nome_cientifico), dois inteiros (n_alcunhas e n_sementes) 
 *        e um vetor de apontadores para char (alcunhas)
 *      
 */
typedef struct planta
{
  /** identificacao unica no catalogo **/
  char ID[10];

  /** designacao cientifica */
  char nome_cientifico[MAX_NAME];

  /** lista de nomes locais correntes dados a especie **/
  char **alcunhas;

  /** numero total de alcunhas da planta **/
  int n_alcunhas;

  /** numero de sementes guardadas no cofre **/
  int n_sementes;

} planta;

/**
 * @brief colecao contem um vetor de apontadores do tipo planta, o tamanho desse vetor e o tipo de ordenacao da colecao
 * 
 */
typedef struct colecao
{
  /** apontador para o array de plantas armazenadas (vetor de apontadores do tipo planta) **/
  planta **plantas;

  /** tamanho do vetor de plantas **/
  long tamanho;

  /** indicacao do campo para ordenacao crescente do vetor: ‘nome’ - para nome_cientifico; ‘id’ - para campo de identificacao unica **/
  char tipo_ordem[5];

} colecao;

/**
 * @brief cria uma nova planta com os valores dos parametros
 * 
 * @param ID string de 10 carateres contendo o identificador unico da planta
 * @param nome_cientifico string de MAX_NAME carateres contendo o nome cientifico da planta
 * @param alcunhas etor (de strings) contendo as possiveis alcunhas da planta; pode ser NULL caso nao existam alcunhas para a planta
 * @param n_alcunhas inteiro contendo o tamanho (numero de alcunhas) do vetor alcunhas
 * @param n_sementes inteiro contendo o numero de sementes da planta a guardar na colecao
 * @return retorna o apontador para a planta criada ou NULL se ocorrer algum erro ou se algum dos parametros nao estiver dentro da gama de valores valida
 */
planta *planta_nova(const char *ID, const char *nome_cientifico, char **alcunhas, int n_alcunhas, int n_sementes);

/**
 * @brief cria uma nova colecao vazia
 * 
 * @param tipo_ordem string contendo o tipo de ordenacao da nova colecao; ‘nome’ - para nome_cientifico ou ‘id’ - para campo de identificacao unica
 * @return colecao* - apontador para a colecao ou NULL se ocorreu algum erro
 */
colecao *colecao_nova(const char *tipo_ordem);

/**
 * @brief insere uma planta na colecao, na posicao correta de acordo com o tipo_ordem - observacoes: caso a planta ja exista (tenha o mesmo ID) deve atualizar o numero de sementes e acrescentar as novas alcunhas (garantindo que nao ha alcunhas repetidas)
 * 
 * @param c apontador para a colecao
 * @param p planta a inserir
 * @return int - 0 se a planta nao existia e foi inserida com sucesso, 1 se a planta ja existia e apenas foi atualizada e -1 se ocorrer um erro
 */
int planta_insere(colecao *c, planta *p);

/**
 * @brief indica o numero de plantas na colecao
 * 
 * @param c apontador para a colecao
 * @return int -  numero de plantas da colecao ou -1 em caso de erro
 */
int colecao_tamanho(colecao *c);

/**
 * @brief cria uma colecao, le o conteudo do ficheiro de texto de nome nome_ficheiro e importa-o para a colecao criada - observacao: A colecao deve ser ordenada de acordo com tipo_ordem.
 * 
 * @param nome_ficheiro nome do ficheiro de texto contendo a colecao a importar
 * @param tipo_ordem tipo de ordenacao da nova colecao; ‘nome’ - para nome_cientifico ou ‘id’ - para campo de identificacao unica
 * @return colecao* - apontador para a colecao criada. Em caso de erro retorna NULL.
 */
colecao *colecao_importa(const char *nome_ficheiro, const char *tipo_ordem);

/**
 * @brief remove da colecao a planta com nome cientifico dado por nomep e corrige a colecao no elemento retirado
 * 
 * @param c apontador para a colecao
 * @param nomep nome cientifico da planta a remover
 * @return planta* - apontador para a planta removida da colecao ou NULL se ocorrer um erro (ou a planta nao existir na colecao)
 */
planta *planta_remove(colecao *c, const char *nomep);

/**
 * @brief elimina uma planta, libertando toda a memoria por ela ocupada
 * 
 * @param p apontador para a planta
 * @return int - 0 se remocao ocorrer com sucesso e -1 em caso de erro
 */
int planta_apaga(planta *p);

/**
 * @brief elimina uma colecao, libertando toda a memoria por ela ocupada
 * 
 * @param c apontador para a colecao 
 * @return int - 0 se bem sucedida e -1 em caso de insucesso
 */
int colecao_apaga(colecao *c);

/**
 * @brief pesquisa todas as plantas que contenham a totalidade de nomep no nome cientifico ou nas alcunhas e retorna um vetor com as posicoes dessas plantas na colecao 
 * 
 * @param c apontador para a colecao 
 * @param nomep nome a procurar
 * @param tam apontador para o tamanho do vetor retornado/numero total de plantas encontradas
 * @return int* - etor de indices/posicoes das plantas encontradas. O tamanho deste vetor e retornado por referencia no parametro tam.
 */
int *colecao_pesquisa_nome(colecao *c, const char *nomep, int *tam);

/**
 * @brief reordena a colecao de acordo com o tipo_ordem; ‘nome’ - ordena alfabeticamente por nome_cientifico; ‘id’ - ordena alfabeticamente pelo campo de identificacao unica
 *        e atualiza o campo tipo_ordem da colecao para o novo tipo_ordem
 * 
 * @param c apontador para a colecao 
 * @param tipo_ordem tipo de ordenacao a ser executada
 * @return int - 1 se for necessario reordenar e a reordenacao ocorrer com sucesso, 0 se nao for necessario reordenar e -1 em caso de erro
 */
int colecao_reordena(colecao *c, const char *tipo_ordem);

#define PLANTAS_H
#endif
