#include "conway.h"
#include "conway_macros.h"
#include "scale.h"
#include "cuda_conway.h"

#include "mpi.h"
#include <cstdio>

void conway(int shift, char* source, char* destination, int numloops, int ymin, int ymax)
{
	int dimension_size = (1 << shift);
	if ((ymin == -1)||(ymax == -1))
	{
		ymin = 0;
		ymax = dimension_size;
	}

	int total_size = BINARR_SIZE(CELL_SIZE(shift));
	for(int i = 0; i < numloops; ++i)
		for(int y = ymin; y < ymax; ++y)
			for(int x = 0; x < dimension_size; ++x)
				NEXT_CELL(x,y,shift,source,destination);
	
	//copy the destination back to the source
	for(int i = 0; i < total_size; ++i)
		source[i] = destination[i];
}

void conway_print(int shift, char* source)
{
	int dimension_size = (1 << shift);
	int total_size = CELL_SIZE(shift);
	for(int y = 0; y < dimension_size; ++y)
	{
		for(int x = 0; x < dimension_size; ++x)
		{
			if(CHECK_CELL_LIVING(x,y,shift,source))
				printf("#");
			else printf("-");
		}
		printf("\n");
	}
	printf("\n");
}

void conway_mpi(int shift, char* source, char* destination, int numloops, bool use_cuda, int np, int rank)
{
	//divide the array along the x axis to a multiple of 8 bits
	int dimension = (1 << shift);
	int csize = BINARR_SIZE(CELL_SIZE(shift));
	int dimensionbyte = (1 << (shift - 3));
	int xmin = (ASSIGN_MIN(dimensionbyte,np,rank)) << 3;
	int xmax = (ASSIGN_MAX(dimensionbyte,np,rank)) << 3;
	char* metadata = (char*)malloc(sizeof(char) * csize);//array for holding temporary data

	//clear destination
	for(int i = 0; i < csize; ++i)
		destination[i] = 0;

	if(use_cuda && (np == 1)) //memory initialization and other overhead can be avoided assuming it's a single node calling CUDA
	{
		cuda_launch_conway(shift, &source, numloops, 0, dimension);
		return;
	}
	else if(np == 1) //MPI_Allreduce overhead avoided if it's a single node
	{
		conway(shift, source, destination, numloops);
		return;
	}

	for (int i = 0; i < numloops; ++i)
	{
		if(use_cuda)
			cuda_launch_conway(shift, &source, 1, xmin, xmax);
		else conway(shift, source, destination, 1, xmin, xmax);

		//reduce to a metadata array, and copy back
		MPI_Allreduce(source, metadata, csize, MPI_CHAR, MPI_BOR, MPI_COMM_WORLD);
		for(int j = 0; j < csize; ++j)
			source[j] = metadata[j];
	}
	free(metadata);
}

void conway_print_bounded(int shift, char* source, int x1, int x2, int y1, int y2)
{
        int dimension_size = (1 << shift);
        int total_size = CELL_SIZE(shift);
        for(int y = y1; y < y2; ++y)
        {
                for(int x = x1; x < x2; ++x)
                {
                        if(CHECK_CELL_LIVING(x,y,shift,source))
                                printf("#");
                        else printf("-");
                }
                printf("\n");
        }
        printf("\n");

}
