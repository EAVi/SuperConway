#include <iostream>
#include "conway_macros.h"
#include "cuda_conway.h"
#include "conway.h"
#include <cstdio>
#include <cstdlib>

using namespace std;

int main(int argc, char * args[])
{
	const int seed = 1;
	srand(seed);
	int shift = 14;//the dimensions will be (2^shift)^2
	char *a = (char*)malloc(sizeof(char) * BINARR_SIZE(CELL_SIZE(shift)));
	char *b = (char*)malloc(sizeof(char) * BINARR_SIZE(CELL_SIZE(shift)));

	//randomize the data
	for(int i = 0, csize = BINARR_SIZE(CELL_SIZE(shift)); i < csize; ++i)
		a[i] = (rand() % 256);

	//do single step, and print each
	conway_print_bounded(shift, a, 0, 8, 0, 8);
	cuda_launch_conway(shift, &a, &b);
	conway_print_bounded(shift, b, 0, 8, 0, 8);

	free(a);
	free(b);

	return 0;
}
