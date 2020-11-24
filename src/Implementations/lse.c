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
  PtNo *novo;
  PtNo *ant = NULL;
  PtNo *ptaux = l;

  novo = (PtNo *)malloc(sizeof(PtNo));

  novo->info = dado;

  while ((ptaux != NULL) && (ptaux->info < dado))
  {
    ant = ptaux;
    ptaux = ptaux->prox;
    *operacoes += 2;
  }

  if (ant == NULL)
  {
    *operacoes += 1;
    novo->prox = l;
    l = novo;
  }
  else
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
  free(l);
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
  PtNo *ptaux;
  if (l == NULL)
    puts("lista vazia");
  else
    for (ptaux = l; ptaux != NULL; ptaux = ptaux->prox)
      printf("%d \n", ptaux->info);
}