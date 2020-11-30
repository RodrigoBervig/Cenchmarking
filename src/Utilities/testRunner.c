#include "testRunner.h"
#include "../Implementations/lse.h"
#include "../Implementations/abp.h"
#include "../Implementations/RN.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef unsigned long long int ull;

double insertLSE(int num, ull *comparacoes, char const *file, PtNo **list);
double insertABP(int num, ull *comparacoes, char const *file, pNodoA **arvore);
double insertRN(int num, ull *comparacoes, char const *file, RNtree **rnt);
double buscaABP(pNodoA *arvore, ull *comparacoes);
double buscaLSE(PtNo *list, ull *comparacoes);
double buscaRN(RNtree *rnt, ull *comparacoes);

int nElements[] = {5000, 10000, 100000, 1000000};
char *const files[][2] = {{"orderedIntegers.txt", "ORDENADA"}, {"randomIntegers.txt", "ALEATÓRIA"}};

ull comparacoes, totalComparacoes;
double timeSpent;

void resetControlVariables()
{
    comparacoes = totalComparacoes = 0;
    timeSpent = 0;
}

void printInsercaoStats(double timeSpent, ull totalComparacoes)
{
    printf("\t\t  %lf", timeSpent / 3);
    printf("\t\t %llu", totalComparacoes / 3);
}

void printConsultaStats(double timeSpent, ull comparacoes)
{
    printf("\t %lf", timeSpent);
    printf("\t %llu\n", comparacoes);
}

/*Funções para todos os testes*/

void rodaTestesLSE()
{
    PtNo *list;

    for (int k = 0; k < 2; k++)
    {
        printf("\n\n------------------------ LSE (ENTRADA %s) ------------------------\n", files[k][1]);
        printf("#Elementos \t Tempo \t\t #Operações \t TConsulta \t #OpsConsulta\n");
        for (int i = 0; i < 4; i++)
        {
            printf("%d", nElements[i]);

            for (int j = 0; j < 3; j++)
            {
                timeSpent += insertLSE(nElements[i], &comparacoes, files[k][0], &list);
                totalComparacoes += comparacoes;
                comparacoes = 0;
                if (j < 2)
                    list = destroi(list);
            }

            printInsercaoStats(timeSpent, totalComparacoes);

            resetControlVariables();

            //CONSULTA
            timeSpent = buscaLSE(list, &comparacoes);
            printConsultaStats(timeSpent, comparacoes);

            resetControlVariables();
            list = destroi(list);
        }
    }

    return;
}

void rodaTestesABP()
{
    resetControlVariables();
    pNodoA *arvore = NULL;

    for (int k = 0; k < 2; k++)
    {
        printf("\n\n------------------------ ABP (ENTRADA %s) ------------------------\n", files[k][1]);
        printf("#Elementos \t Tempo \t\t #Operações \t TConsulta \t #OpsConsulta\n");
        for (int i = 0; i < 4; i++)
        {
            printf("%d", nElements[i]);

            for (int j = 0; j < 3; j++)
            {
                timeSpent += insertABP(nElements[i], &comparacoes, files[k][0], &arvore);
                totalComparacoes += comparacoes;
                comparacoes = 0;
                if (j < 2)
                {
                    destroiABP(arvore);
                    arvore = NULL;
                }
            }
            printInsercaoStats(timeSpent, totalComparacoes);

            resetControlVariables();

            //CONSULTA
            timeSpent = buscaABP(arvore, &comparacoes);
            printConsultaStats(timeSpent, comparacoes);

            destroiABP(arvore);
            arvore = NULL;

            resetControlVariables();
        }
    }
}

void rodaTestesRN()
{
    resetControlVariables();
    RNtree *rnt = NULL;

    for (int k = 0; k < 2; k++)
    {
        printf("\n\n------------------------ RN (ENTRADA %s) ------------------------\n", files[k][1]);
        printf("#Elementos \t Tempo \t\t #Operações \t TConsulta \t #OpsConsulta\n");
        for (int i = 0; i < 4; i++)
        {
            printf("%d", nElements[i]);
            for (int j = 0; j < 3; j++)
            {
                timeSpent += insertRN(nElements[i], &comparacoes, files[k][0], &rnt);
                totalComparacoes += comparacoes;
                comparacoes = 0;
                if (j < 2)
                {
                    destroiRN(rnt);
                    rnt = NULL;
                }
            }
            printInsercaoStats(timeSpent, totalComparacoes);

            resetControlVariables();

            //CONSULTA
            timeSpent = buscaRN(rnt, &comparacoes);
            printConsultaStats(timeSpent, comparacoes);

            destroiRN(rnt);
            rnt = NULL;

            resetControlVariables();
        }
    }

    return;
}

/*Funções de inserção*/

double insertRN(int num, ull *comparacoes, char const *file, RNtree **rnt)
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
        *rnt = InsereRN(*rnt, dado, comparacoes);
    }

    end = clock();

    fclose(input);

    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

double insertABP(int num, ull *comparacoes, char const *file, pNodoA **arvore)
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
        *arvore = InsereArvore(*arvore, dado, comparacoes);
    }

    end = clock();

    fclose(input);

    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

double insertLSE(int num, ull *comparacoes, char const *file, PtNo **list)
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
        *list = insere_ord(*list, dado, comparacoes);
    }

    end = clock();
    fclose(input);

    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

/*Funções de consulta*/

double buscaRN(RNtree *rnt, ull *comparacoes)
{

    clock_t start, end;
    int aux;

    start = clock();

    for (int i = 1; i <= 1000; i++)
    {
        aux = ConsultaRN(rand() % 1000000, rnt, comparacoes);
    }

    end = clock();
    return (((double)end - (double)start)) / (double)CLOCKS_PER_SEC;
}

double buscaABP(pNodoA *arvore, ull *comparacoes)
{
    clock_t start, end;
    pNodoA *aux;

    start = clock();

    for (int i = 1; i <= 1000; i++)
    {
        aux = consultaABP(arvore, rand() % 1000000, comparacoes);
    }

    end = clock();
    return (((double)end - (double)start)) / (double)CLOCKS_PER_SEC;
}

double buscaLSE(PtNo *list, ull *comparacoes)
{
    clock_t start, end;
    PtNo *aux;

    start = clock();

    for (int i = 1; i <= 1000; i++)
    {
        aux = consulta(list, rand() % 1000000, comparacoes);
    }

    end = clock();
    return (((double)end - (double)start)) / (double)CLOCKS_PER_SEC;
}