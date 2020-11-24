#include "testRunner.h"
#include "../Utilities/randomIntGen.h"
#include "../Implementations/lse.h"
#include "../Implementations/abp.h"
#include "../Implementations/RN.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef unsigned long long int ull;

double insertLSE(int num, ull *operacoes, char const *file, PtNo **list);
double insertABP(int num, ull *operacoes, char const *file, pNodoA **arvore);
double insertRN(int num, ull *operacoes, char const *file, RNtree **rnt);
double buscaABP(pNodoA *arvore, ull *operacoes);
double consultaLSE(PtNo *list, ull *operacoes);

int nElements[] = {5000, 10000, 100000, 1000000};

void rodaTestesLSE()
{
    double time = 0;
    ull operacao = 0, totalOperacoes = 0;
    PtNo *list;

    printf("TESTE ELEMENTOS ORDENADOS LSE:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            time += insertLSE(nElements[i], &operacao, "orderedIntegers.txt", &list);
            totalOperacoes += operacao;
            operacao = 0;
            if (j < 2)
                list = destroi(list);
        }
        printf("Tempo médio para inserir %d elementos ordenados na LSE: %.2lf\n", nElements[i], time / 3);
        printf("Número médio de instruções para inserir %d elementos orenados na LSE: %llu\n", nElements[i], totalOperacoes / 3);

        time = 0;
        operacao = totalOperacoes = 0;

        //CONSULTA
        time = consultaLSE(list, &operacao);
        printf("Tempo médio de para consultar uma LSE com %d elementos ordenados: %lf\n", nElements[i], time);
        printf("Número médio de instruções para consultar elementos em uma LSE com %d elementos ordenados: %llu\n\n\n", nElements[i], operacao / 1000);

        time = operacao = 0;
        list = destroi(list);
    }

    printf("TESTE ELEMENTOS ALEATÓRIOS LSE:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            time += insertLSE(nElements[i], &operacao, "randomIntegers.txt", &list);
            totalOperacoes += operacao;
            operacao = 0;
            if (j < 2)
                list = destroi(list);
        }
        printf("Tempo médio para inserir %d elementos aleatórios na LSE: %.2lf\n", nElements[i], time / 3);
        printf("Número médio de instruções para inserir %d elementos aleatórios na LSE: %llu\n", nElements[i], totalOperacoes / 3);

        time = 0;
        operacao = totalOperacoes = 0;

        //CONSULTA
        time = consultaLSE(list, &operacao);
        printf("Tempo médio de para consultar uma LSE com %d elementos aleatórios: %lf\n", nElements[i], time);
        printf("Número médio de instruções para consultar elementos em uma LSE com %d elementos aleatórios: %llu\n\n\n", nElements[i], operacao / 1000);

        time = operacao = 0;
        list = destroi(list);
    }

    return;
}

double consultaLSE(PtNo *list, ull *operacoes)
{
    clock_t start, end;
    PtNo *aux;

    start = clock();

    for (int i = 1; i <= 1000; i++)
    {
        aux = consulta(list, rand() % 1000000, operacoes);
    }

    end = clock();
    return (((double)end - (double)start)) / (double)CLOCKS_PER_SEC;
}

double insertLSE(int num, ull *operacoes, char const *file, PtNo **list)
{
    clock_t start, end;
    FILE *input;
    int dado = 0;

    *list = cria_lista();

    if ((input = fopen(file, "r")) == NULL)
    {
        printf("Erro ao tentar abrir o arquivo com inteiros aleatórios\n");
    }

    start = clock();
    for (int i = 0; i < num; i++)
    {
        fscanf(input, "%d", &dado);
        *list = insere_ord(*list, dado, operacoes);
    }

    end = clock();
    fclose(input);

    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

void rodaTestesABP()
{
    double time = 0;
    ull operacao = 0, totalOperacoes = 0;
    pNodoA *arvore = NULL;

    printf("\t\t\t\tTESTE ELEMENTOS ORDENADOS ABP:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            time += insertABP(nElements[i], &operacao, "orderedIntegers.txt", &arvore);
            totalOperacoes += operacao;
            operacao = 0;
            if (j < 2)
                destroiABP(arvore);
            arvore = NULL;
        }
        printf("Tempo médio para inserir %d elementos ordenados na ABP: %.2lf\n", nElements[i], time / 1);
        printf("Número médio de instruções para inserir %d elementos ordenados na ABP: %llu\n", nElements[i], totalOperacoes / 1);

        operacao = totalOperacoes = 0;

        //CONSULTA
        time = buscaABP(arvore, &operacao);
        printf("Tempo médio de para consultar uma ABP com %d elementos ordenados: %lf\n", nElements[i], time);
        printf("Número médio de instruções para consultar elementos em uma ABP com %d elementos ordenados: %llu\n\n\n", nElements[i], operacao / 10);
        time = 0;
        operacao = 0;
        destroiABP(arvore);
        arvore = NULL;
    }

    //****************************************************************************************//

    printf("\t\t\t\tTESTE ELEMENTOS ALEATÓRIOS ABP:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            time += insertABP(nElements[i], &operacao, "randomIntegers.txt", &arvore);
            totalOperacoes += operacao;
            operacao = 0;
            if (j < 2)
                destroiABP(arvore);
            arvore = NULL;
        }
        printf("Tempo médio para inserir %d elementos aleatórios na ABP: %.2lf\n", nElements[i], time / 3);
        printf("Número médio de instruções para inserir %d elementos aleatórios na ABP: %llu\n", nElements[i], totalOperacoes / 3);
        time = 0;
        operacao = totalOperacoes = 0;

        //CONSULTA
        time = buscaABP(arvore, &operacao);
        printf("Tempo médio para consultar uma ABP com %d elementos aleatórios: %lf\n", nElements[i], time);
        printf("Número médio de instruções para consultar elementos em uma ABP com %d elementos aleatórios: %llu\n\n", nElements[i], operacao / 10);
        time = 0;
        operacao = totalOperacoes = 0;
        destroiABP(arvore);
        arvore = NULL;
    }
}

double buscaABP(pNodoA *arvore, ull *operacoes)
{
    clock_t start, end;
    pNodoA *aux;

    start = clock();

    for (int i = 1; i <= 1000; i++)
    {
        aux = consultaABP(arvore, rand() % 1000000, operacoes);
    }

    end = clock();
    return (((double)end - (double)start)) / (double)CLOCKS_PER_SEC;
}

double insertABP(int num, ull *operacoes, char const *file, pNodoA **arvore)
{
    clock_t start, end;
    FILE *input;
    int dado = 0;

    if ((input = fopen(file, "r")) == NULL)
    {
        printf("Erro ao tentar abrir o arquivo %s\n", file);
    }

    start = clock();

    for (int i = 0; i < num; i++)
    {
        fscanf(input, "%d", &dado);
        *arvore = InsereArvore(*arvore, dado, operacoes);
    }

    end = clock();

    fclose(input);

    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

void rodaTestesRN()
{
    double time = 0;
    ull operacao = 0, totalOperacoes = 0;
    RNtree *rnt = NULL;

    printf("\t\t\tTESTE ELEMENTOS ORDENADOS RN:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            time += insertRN(nElements[i], &operacao, "orderedIntegers.txt", &rnt);
            totalOperacoes += operacao;
            operacao = 0;
            if (j < 2)
                destroiRN(rnt);
            rnt = NULL;
        }
        printf("Tempo médio para inserir %d elementos ordenados na RN: %.2lf\n", nElements[i], time / 3);
        printf("Número médio de instruções para inserir %d elementos ordenados na RN: %llu\n\n\n", nElements[i], totalOperacoes / 3);

        time = 0;
        operacao = totalOperacoes = 0;
    }
    /* //CONSULTA
        time = consultaLSE(rnt, &operacao);
        printf("Tempo médio de para consultar uma RN com %d elementos ordenados: %lf\n", nElements[i], time);
        printf("Número médio de instruções para consultar elementos em uma RN com %d elementos ordenados: %llu\n\n\n", nElements[i], operacao / 1000);
        */
    time = operacao = 0;
    destroiRN(rnt);
    rnt = NULL;

    printf("\t\t\tTESTE ELEMENTOS ALEATÓRIOS RN\n");
    /**********************************************************************/
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            time += insertRN(nElements[i], &operacao, "randomIntegers.txt", &rnt);
            totalOperacoes += operacao;
            operacao = 0;
            if (j < 2)
                destroiRN(rnt);
            rnt = NULL;
        }
        printf("Tempo médio para inserir %d elementos aleatórios na RN: %.2lf\n", nElements[i], time / 3);
        printf("Número médio de instruções para inserir %d elementos aleatórios na RN: %llu\n", nElements[i], totalOperacoes / 3);

        time = 0;
        operacao = totalOperacoes = 0;

        /* //CONSULTA
        time = consultaLSE(rnt, &operacao);
        printf("Tempo médio de para consultar uma RN com %d elementos ordenados: %lf\n", nElements[i], time);
        printf("Número médio de instruções para consultar elementos em uma RN com %d elementos ordenados: %llu\n\n\n", nElements[i], operacao / 1000);
        */
        time = operacao = 0;
        destroiRN(rnt);
        rnt = NULL;
    }
}

double insertRN(int num, ull *operacoes, char const *file, RNtree **rnt)
{
    clock_t start, end;
    FILE *input;
    int dado = 0;

    if ((input = fopen(file, "r")) == NULL)
    {
        printf("Erro ao tentar abrir o arquivo %s\n", file);
    }

    start = clock();

    for (int i = 0; i < num; i++)
    {
        fscanf(input, "%d", &dado);
        *rnt = InsereRN(*rnt, dado, operacoes);
    }

    end = clock();

    fclose(input);

    return ((double)(end - start)) / CLOCKS_PER_SEC;
}