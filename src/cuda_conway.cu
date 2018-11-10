#include "cstdio"
#include "cuda_conway.h"
#include "conway_macros.h"
#include "scale.h"
#include "cuda_conway.cuh"

bool cuda_launch_conway(int shift, char** a, char** b)
{
	if ((a == NULL) || (*a == NULL) || (b == NULL) || (*b == NULL))
	{
		printf("NULL pointer passed\n");
		return false;
	}
	
	//size constants
	int csize = BINARR_SIZE(CELL_SIZE(shift));
	int dimension = (1 << shift);
	int csizemem = (csize * sizeof(char));

	//device problem distribution
	int blocksize = 128;
	int numblocks = (blocksize + dimension - 1)/dimension;
	
	char* device_source = NULL;
	char* device_destination = NULL;
	
	//allocate memory
	CHECKERR( cudaMallocManaged(&device_source, csizemem) );
	CHECKERR( cudaMallocManaged(&device_destination, csizemem) );
	
	//copy a into source
	CHECKERR( cudaMemcpy(device_source, *a, csizemem, cudaMemcpyHostToDevice) );
	
	cuda_conway<<<numblocks,blocksize>>>(shift, device_source, device_destination);
	
	//copy result from device
	CHECKERR( cudaMemcpy(*b, device_destination, csizemem, cudaMemcpyDeviceToHost) );
	
	//free
	CHECKERR( cudaFree(device_source) );
	CHECKERR( cudaFree(device_destination) );
	
	return true;
}

__global__
void cuda_conway(int shift, char * a, char * b)
{
/*
	data will be partitioned by x value on MPI, and partitioned by y value on CUDA
	this will make memory accesses on the GPU more linear and less likely to hit a cache fault,
	resulting in probably unnoticeable speedup
*/
	int dimension = (1 << shift);
	int gridid = blockIdx.x * blockDim.x + threadIdx.x;
	int griddim = blockDim.x * gridDim.x;

	int ymin = ASSIGN_MIN(dimension, griddim, gridid);
	int ymax = ASSIGN_MAX(dimension, griddim, gridid);
	for(int y = ymin; y < ymax; ++y)
		for(int x = 0; x < dimension; ++x)
			NEXT_CELL(x,y,shift,a,b);
}
