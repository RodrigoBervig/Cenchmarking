#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void initializeSeed()
{
	unsigned int randval;
	FILE *f;

	f = fopen("/dev/random", "r");
	fread(&randval, sizeof(randval), 1, f);
	fclose(f);

	srand(randval);
}

int genRandomFile(char const *fileName, int num, int limit)
{
	initializeSeed();

	FILE *output;

	if ((output = fopen(fileName, "w")) == NULL)
	{
		printf("Error while opening random integer output file\n");
		return 0;
	}

	while (num--)
	{
		fprintf(output, "%d ", rand() % limit);
	}
};