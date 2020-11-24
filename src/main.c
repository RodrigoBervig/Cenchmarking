#include "./Utilities/randomIntGen.h"
#include "./Implementations/lse.h"
#include "./Implementations/abp.h"
#include "./Implementations/RN.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef unsigned long long int ull;

void genOrderedFile(char const *file, int num, int limit);

double insertLDE(int num, ull *operacoes, char const *file);
double insertABP(int num, ull *operacoes, char const *file, pNodoA **arvore);
double buscaABP(pNodoA *arvore, ull *operacoes);
void rodaTestesLDE();
void rodaTestesABP();

int main(int argc, int **argv)
{
    genRandomFile("randomIntegers.txt", 1000009, 1000000);
    genOrderedFile("orderedIntegers.txt", 1000009, 1000000);

    //rodaTestesLDE();
    rodaTestesABP();

    return 0;
}

void rodaTestesLDE()
{
    int times[] = {5000, 10000, 100000, 1000000};
    double time = 0;
    ull operacao = 0, totalOperacoes = 0;

    printf("TESTE ELEMENTOS ORDENADOS LSE:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            time += insertLDE(times[i], &operacao, "orderedIntegers.txt");
            totalOperacoes += operacao;
            operacao = 0;
        }
        printf("Tempo médio para inserir %d elementos ordenados na LSE: %.2lf\n", times[i], time / 3);
        printf("Número médio de instruções para inserir %d elementos orenados na LSE: %llu\n", times[i], totalOperacoes / 3);
        time = 0;
        operacao = totalOperacoes = 0;
    }

    printf("TESTE ELEMENTOS ALEATÓRIOS LSE:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            time += insertLDE(times[i], &operacao, "randomIntegers.txt");
            totalOperacoes += operacao;
            operacao = 0;
        }
        printf("Tempo médio para inserir %d elementos aleatórios na LSE: %.2lf\n", times[i], time / 3);
        printf("Número médio de instruções para inserir %d elementos aleatórios na LSE: %llu\n", times[i], totalOperacoes / 3);
        time = 0;
        operacao = totalOperacoes = 0;
    }

    return;
}

double insertLDE(int num, ull *operacoes, char const *file)
{
    clock_t start, end;
    PtNo *list;
    FILE *input;
    int dado = 0;

    list = cria_lista();

    if ((input = fopen(file, "r")) == NULL)
    {
        printf("Erro ao tentar abrir o arquivo com inteiros aleatórios\n");
    }

    start = clock();
    for (int i = 0; i < num; i++)
    {
        fscanf(input, "%d", &dado);
        //printf("%d\n", dado);
        list = insere_ord(list, dado, operacoes);
        // printf("%ld\n", *operacoes);
    }

    end = clock();
    fclose(input);

    list = destroi(list);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

void rodaTestesABP()
{
    int times[] = {5000, 10000, 100000, 1000000};
    double time = 0;
    ull operacao = 0, totalOperacoes = 0;
    pNodoA *arvore = NULL;

    printf("\t\t\t\tTESTE ELEMENTOS ORDENADOS ABP:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            time += insertABP(times[i], &operacao, "orderedIntegers.txt", &arvore);
            totalOperacoes += operacao;
            operacao = 0;
        }
        printf("Tempo médio para inserir %d elementos ordenados na ABP: %.2lf\n", times[i], time / 1);
        printf("Número médio de instruções para inserir %d elementos ordenados na ABP: %llu\n", times[i], totalOperacoes / 1);

        operacao = totalOperacoes = 0;

        time = buscaABP(arvore, &operacao);
        printf("Tempo médio de para consultar uma ABP com %d elementos ordenados: %lf\n", times[i], time);
        printf("Número médio de instruções para consultar %d elementos em uma ABP com elementos ordenados: %llu\n\n\n", times[i], operacao / 10);
        time = 0;
        operacao = totalOperacoes = 0;
        destroiABP(arvore);
        arvore = NULL;
    }

    //****************************************************************************************//

    printf("\t\t\t\tTESTE ELEMENTOS ALEATÓRIOS ABP:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            time += insertABP(times[i], &operacao, "randomIntegers.txt", &arvore);
            totalOperacoes += operacao;
            operacao = 0;
        }
        printf("Tempo médio para inserir %d elementos aleatórios na ABP: %.2lf\n", times[i], time / 3);
        printf("Número médio de instruções para inserir %d elementos aleatórios na ABP: %llu\n", times[i], totalOperacoes / 3);
        time = 0;
        operacao = totalOperacoes = 0;

        time = buscaABP(arvore, &operacao);
        printf("Tempo médio para consultar uma ABP com %d elementos aleatórios: %lf\n", times[i], time);
        printf("Número médio de instruções para consultar %d elementos em uma ABP com elementos aleatórios: %llu\n\n", times[i], operacao / 10);
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

void genOrderedFile(char const *fileName, int num, int limit)
{
    FILE *output;

    if ((output = fopen(fileName, "w")) == NULL)
    {
        printf("Error while opening random integer output file\n");
        return;
    }

    for (int i = 0; i <= num; i++)
    {
        fprintf(output, "%d ", i);
    }
}