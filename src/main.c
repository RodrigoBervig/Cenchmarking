#include "./Utilities/integerGenerator.h"
#include "./Utilities/testRunner.h"

int main(int argc, int **argv)
{
    genRandomFile("randomIntegers.txt", 1000009, 1000000);
    genOrderedFile("orderedIntegers.txt", 1000009, 1000000);

    rodaTestesRN();
    rodaTestesLSE();
    rodaTestesABP();

    return 0;
}
