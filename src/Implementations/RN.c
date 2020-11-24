#include <stdio.h>
#include <stdlib.h>
#include "RN.h"

typedef unsigned long long int ull;

RNtree *InsereRN(RNtree *t, int key, ull *operacoes)
{
  RNtree *x = t;

  if (t == NULL)
  {
    // allocate memory
    NodoNULL = (RNtree *)malloc(sizeof(RNtree));
    x = (RNtree *)malloc(sizeof(RNtree));

    NodoNULL->red = 0;
    NodoNULL->esq = NodoNULL;
    NodoNULL->dir = NodoNULL;
    NodoNULL->key = 32000;
    NodoNULL->pai = NodoNULL;

    //root
    x->key = key;
    x->esq = x->dir = NodoNULL;
    x->red = 0;
    x->pai = NodoNULL;
    return x;
  }

  RNtree *p = x->pai; // father
  RNtree *v = p->pai; // grandfather

  while (x != NodoNULL) /* binary search the tree */
  {
    *operacoes += 1;
    v = p;
    p = x;
    if (key < x->key)
    {
      x = x->esq;
      *operacoes += 1;
    }
    else
      x = x->dir;
  };

  if (x != NodoNULL)
  {
    *operacoes += 1;
    return t;
  } // node is already present in the tree

  x = (RNtree *)malloc(sizeof(RNtree));
  x->key = key;
  x->esq = x->dir = NodoNULL;
  x->pai = p;
  x->red = 1;

  if (key < p->key)
  {
    *operacoes += 1;
    p->esq = x;
  }
  else
    p->dir = x;

  // Nodo Foi Inserido mas pode ter modificado as regras ent�o temos que verificar.

  return VerificaRN(t, key, operacoes);
};

int Consulta(int X, RNtree *T)
{
  if (T == NodoNULL)
    return 0;
  if (X == T->key)
    return 1;
  else if (X < T->key)
    return Consulta(X, T->esq);
  else if (X > T->key)
    return Consulta(X, T->dir);
  else
    return 0;
};

void destroiRN(RNtree *t)
{
  if (t == NULL)
    return;

  destroiRN(t->esq);
  destroiRN(t->dir);

  free(t);
};

RNtree *VerificaRN(RNtree *t, int key, ull *operacoes)
{
  RNtree *x = t;
  RNtree *p = x->pai;
  RNtree *v = p->pai;
  while (x->key != key) /* binary search tree */
  {
    *operacoes += 1;
    v = p;
    p = x;
    if (key < x->key)
    {
      x = x->esq;
      ull *operacoes;
    }
    else
      x = x->dir;
  };

  // caso 2
  if (p->red)
  {
    *operacoes += 1;
    if (v != NodoNULL) // pai n�o � raiz
    {
      *operacoes += 1;
      if (p->key < v->key) // p � filho a esquerda
      {
        *operacoes += 1;
        // Caso 2.1
        if (v->dir->red) // tio � vermelho
        {
          *operacoes += 1;
          v->dir->red = 0; // tio vira preto
          if (p->red)
          {
            p->red = 0;
            *operacoes += 1;
          } // troca a cor do pai
          else
            p->red = 1;
          if (v->pai == NodoNULL) // av� � raiz
          {
            *operacoes += 1;
            p->dir->red = 0;
            p->red = 0;
            v->red = 0;
          };
        }
        else
        {
          if ((x->key < p->key) && (p->key < v->key)) // Caso 2.2(A)
          {
            *operacoes += 1;
            // rotacao a direita
            RotacaoSimplesDir(v);
            if (p->red)
            {
              p->red = 0; // troca a cor do pai
              *operacoes += 1;
            }
            else
              p->red = 1;
            if (v->red)
            {
              v->red = 0; // troca a cor do vo
              *operacoes += 1;
            }
            else
              v->red = 1;
          }
          else
          {
            if ((x->key > p->key) && (p->key > v->key)) // Caso 2.2(B)
            {
              *operacoes += 1;
              RotacaoSimplesEsq(v);
              if (p->red)
              {
                p->red = 0; // troca a cor do pai
                *operacoes += 1;
              }
              else
                p->red = 1;
              if (v->red)
              {
                v->red = 0; // troca a cor do vo
                *operacoes += 1;
              }
              else
                v->red = 1;
            }
            else
            {
              if (p->key < v->key) // Caso 2.2(C)
              {
                *operacoes += 1;
                RotacaoSimplesEsq(p);
                RotacaoSimplesDir(v); // rotacao Dupla a direita
                if (x->red)
                {
                  x->red = 0; // troca a cor do novo
                  *operacoes += 1;
                }
                else
                  x->red = 1;
                if (v->red)
                {
                  v->red = 0; // troca a cor do vo
                  *operacoes += 1;
                }
                else
                  v->red = 1;
              }
              else // Caso 2.2(D)
              {
                RotacaoSimplesDir(p);
                RotacaoSimplesEsq(v); // rotacao Dupla a esquerda
                if (x->red)
                {
                  x->red = 0; // troca a cor do novo
                  *operacoes += 1;
                }
                else
                  x->red = 1;
                if (v->red)
                {
                  v->red = 0; // troca a cor do vo
                  *operacoes += 1;
                }
                else
                  v->red = 1;
              };
            };
          };
        };
      }
      else
      {
        // Caso 2.1
        if (v->esq->red) // tio � vermelho
        {
          *operacoes += 1;
          v->esq->red = 0; // tio vira preto
          if (p->red)
          {
            p->red = 0; // troca a cor do pai
            *operacoes += 1;
          }
          else
            p->red = 1;
          if (v->pai == NodoNULL) // av� � raiz
          {
            *operacoes += 1;
            p->dir->red = 0;
            p->red = 0;
            v->red = 0;
          };
        }
        else
        {
          if ((x->key < p->key) && (p->key < v->key)) // Caso 2.2(A)
          {
            *operacoes += 1;
            // rotacao a direita
            RotacaoSimplesDir(v);
            if (p->red)
            {
              p->red = 0; // troca a cor do pai
              *operacoes += 1;
            }
            else
              p->red = 1;
            if (v->red)
            {
              v->red = 0; // troca a cor do vo
              *operacoes += 1;
            }
            else
              v->red = 1;
          }
          else
          {
            if ((x->key > p->key) && (p->key > v->key)) // Caso 2.2(B)
            {
              RotacaoSimplesEsq(v); // --- aqui
              if (p->red)
              {
                p->red = 0; // troca a cor do pai
                *operacoes += 1;
              }
              else
                p->red = 1;
              if (v->red)
              {
                v->red = 0; // troca a cor do vo
                *operacoes += 1;
              }
              else
                v->red = 1;
            }
            else
            {
              if (p->key < v->key) // Caso 2.2(C)
              {
                *operacoes += 1;
                RotacaoSimplesEsq(p);
                RotacaoSimplesDir(v); // rotacao Dupla a direita
                if (x->red)
                {
                  x->red = 0; // troca a cor do novo
                  *operacoes += 1;
                }
                else
                  x->red = 1;
                if (v->red)
                {
                  v->red = 0; // troca a cor do vo
                  *operacoes += 1;
                }
                else
                  v->red = 1;
              }
              else // Caso 2.2(D)
              {
                *operacoes += 1;
                RotacaoSimplesDir(p);
                RotacaoSimplesEsq(v); // rotacao Dupla a esquerda
                if (x->red)
                {
                  x->red = 0; // troca a cor do novo
                  *operacoes += 1;
                }
                else
                  x->red = 1;
                if (v->red)
                {
                  v->red = 0; // troca a cor do vo
                  *operacoes += 1;
                }
                else
                  v->red = 1;
              };
            };
          };
        };
      };
    };
  };
  t->red = 0;
  x->red = 1;
  return t;
};

RNtree *RotacaoSimplesDir(RNtree *t)
{
  RNtree *aux;

  aux = t->esq;
  t->esq = aux->dir;
  aux->dir = t;

  return aux; /* nova raiz */
};

RNtree *RotacaoSimplesEsq(RNtree *t)
{
  RNtree *aux;

  aux = t->dir;
  t->dir = aux->esq;
  aux->esq = t;

  return aux; /* nova raiz */
};

void Desenha(RNtree *t, int nivel)
{
  int x;

  if (t != NodoNULL)
  {
    for (x = 1; x <= nivel; x++)
      printf("=");
    if (t->red)
      printf("%d Red\n", t->key);
    else
      printf("%d Black\n", t->key);
    if (t->esq != NodoNULL)
      Desenha(t->esq, (nivel + 1));
    if (t->dir != NodoNULL)
      Desenha(t->dir, (nivel + 1));
  }
  else
    printf("Arvore Vazia\n");
};

RNtree *Maior(RNtree *t)
{
  while (t != NodoNULL)
    t = t->dir;
  return t->pai;
};

RNtree *Menor(RNtree *t)
{
  while (t != NodoNULL)
    t = t->esq;
  return t->pai;
};
