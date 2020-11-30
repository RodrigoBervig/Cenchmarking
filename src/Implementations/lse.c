#include <stdio.h>
#include <stdlib.h> //necessaria para o malloc
#include <string.h> //necessaria para o strcmp
#include "lse.h"

typedef unsigned long long int ull;

PtNo *cria_lista(void)
{
  return NULL;
}

PtNo *insere_ord(PtNo *l, int dado, ull *operacoes)
{
  PtNo *novo;      //novo elemento
  PtNo *ptaux = l; //ponteiro auxiliar para percorrer a lista
  PtNo *ant = l;   //ponteiro auxiliar para a posição anterior

  /*aloca um novo nodo */
  novo = (PtNo *)malloc(sizeof(PtNo));

  /*insere a informação no novo nodo*/
  novo->info = dado;

  /*procurando a posição de inserção*/
  while ((ptaux != NULL) && ptaux->info <= dado) //se info.titulo < dados.titulo então strcmp retorna um valor menor que zero
  {
    ant = ptaux;
    ptaux = ptaux->prox;
    *operacoes += 2;
  }

  /*encaeia o elemento*/
  if (ant == NULL) /*o anterior não existe, logo o elemento será inserido na primeira posição*/
  {
    if (l == NULL)
    {
      novo->size = 1;
    }
    novo->prox = l;
    l = novo;
    *operacoes += 1;
  }
  else /*elemento inserido no meio da lista*/
  {
    novo->prox = ant->prox;
    ant->prox = novo;
  }

  return l;
}

PtNo *destroi(PtNo *l)
{
  PtNo *ptaux;
  while (l != NULL)
  {
    ptaux = l;
    l = l->prox;
    free(ptaux);
  }
  return NULL;
}

PtNo *consulta(PtNo *l, int dado, ull *operacoes)
{
  while ((l != NULL) && (l->info != dado))
  {
    *operacoes += 2;
    l = l->prox;
  }

  return l;
}

void imprime(PtNo *l)
{
  int tam = 0;
  PtNo *ptaux;
  if (l == NULL)
    puts("lista vazia");
  else
    for (ptaux = l; ptaux != NULL; ptaux = ptaux->prox)
    {
      printf("%d \n", ptaux->info);
      tam++;
    }
  printf("%d\n", tam);
}