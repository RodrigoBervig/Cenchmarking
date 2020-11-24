#include <stdio.h>
#include <stdlib.h>
#include "abp.h"

typedef unsigned long long int ull;

pNodoA *InsereArvore(pNodoA *a, tipoinfo ch, ull *operacoes)
{
    pNodoA *root = a;

    pNodoA *y = NULL;
    pNodoA *b = (pNodoA *)malloc(sizeof(pNodoA));
    b->info = ch;
    b->esq = NULL;
    b->dir = NULL;

    while (a != NULL)
    {
        y = a;
        *operacoes += 1;
        if (ch < a->info)
        {
            *operacoes += 1;
            a = a->esq;
        }
        else
        {
            a = a->dir;
        }
    }

    if (y == NULL)
        return b;

    if (ch < y->info)
    {
        y->esq = b;
    }
    else
    {
        y->dir = b;
    }

    return root;
}

void preFixadoE(pNodoA *a)
{
    if (a != NULL)
    {
        printf("%d - ", a->info);
        preFixadoE(a->esq);
        preFixadoE(a->dir);
    }
}

pNodoA *consultaABP(pNodoA *a, tipoinfo chave, ull *operacoes)
{
    while (a != NULL)
    {
        //printf("here");
        *operacoes += 1;
        if (a->info == chave)
        {
            *operacoes += 1;
            return a; //achou entao retorna o ponteiro para o nodo
        }
        else if (a->info > chave)
        {
            a = a->esq;
            *operacoes += 1;
        }
        else
        {
            a = a->dir;
        }
    }
    return NULL; //se nao achou
}

void destroiABP(pNodoA *a)
{
    if (a == NULL)
        return;

    destroiABP(a->esq);
    destroiABP(a->dir);

    free(a);
}
