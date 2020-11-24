#include "./Utilities/randomIntGen.h"
#include "./Utilities/testRunner.h"
#include "./Implementations/lse.h"
#include "./Implementations/abp.h"
#include "./Implementations/RN.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void genOrderedFile(char const *file, int num, int limit);

int main(int argc, int **argv)
{
    genRandomFile("randomIntegers.txt", 1000009, 1000000);
    genOrderedFile("orderedIntegers.txt", 1000009, 1000000);

    rodaTestesRN();
    rodaTestesLSE();
    rodaTestesABP();

    return 0;
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

    fclose(output);
}