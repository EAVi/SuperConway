#include <iostream>
#include "conway_macros.h"
#include "cuda_conway.h"
#include "conway.h"
#include "mpi.h"
#include <cstdio>
#include <cstdlib>

using namespace std;

int main(int argc, char * args[])
{
	const int seed = 1;
	srand(seed);
	int shift = 14;//the dimensions will be (2^shift)^2
	bool use_cuda = false;

	if(argc >= 2)
		shift = atoi(args[1]);
	if(argc >= 3)
		use_cuda = (bool)atoi(args[2]);

	char *a = (char*)malloc(sizeof(char) * BINARR_SIZE(CELL_SIZE(shift)));
	char *b = (char*)malloc(sizeof(char) * BINARR_SIZE(CELL_SIZE(shift)));

	//randomize the data
	for(int i = 0, csize = BINARR_SIZE(CELL_SIZE(shift)); i < csize; ++i)
		a[i] = (rand() % 256);

	//MPI values
	int np = 1;
	int rank = -1;
	double begin, end, diff;
	//process name
	int pnamelen = 0;
	char pname[MPI_MAX_PROCESSOR_NAME];

	MPI_Status status;
	MPI_Init(&argc, &args);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Get_processor_name(pname, &pnamelen);

	//do single step, and print each
	begin = MPI_Wtime();
	if (rank == 0) conway_print_bounded(shift, a, 0, 8, 0, 8);
	conway_mpi(shift, a, b, 1, use_cuda, np, rank);
	if (rank == 0) conway_print_bounded(shift, a, 0, 8, 0, 8);
	MPI_Barrier(MPI_COMM_WORLD);
	end = MPI_Wtime();
	diff = end - begin;

	free(a);
	free(b);

	if (rank == 0)
		printf("time elapsed %f\n", diff);
	MPI_Finalize();
	return 0;
}
