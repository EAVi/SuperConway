#include <iostream>
#include "conway_macros.h"
#include "cuda_conway.h"
#include "conway.h"
#include <cstdio>
#include <cstdlib>

using namespace std;

int main(int argc, char * args[])
{
	int seed = 1;
	srand(seed);
	int shift = 12;//the dimensions will be (2^shift)^2
	char *a = (char*)malloc(sizeof(char) * CELL_SIZE(shift));
	char *b = (char*)malloc(sizeof(char) * CELL_SIZE(shift));

	//randomize the data
	for(int i = 0, csize = CELL_SIZE(shift); i < csize; ++i)
		a[i] = rand() % 2;
	
	//do some number of steps, and print each
	conway(shift, a, b);

	free(a);
	free(b);

	return 0;
}
