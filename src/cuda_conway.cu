#include "cstdio"
#include "cuda_conway.h"
#include "cuda_conway.cuh"

bool cuda_launch_conway(int shift, char** a, char** b)
{
	if (a == NULL || *a == NULL || b = NULL || *b = NULL)
	{
		printf("NULL pointer passed\n");
		return false;
	}
	
	//size constants
	int csize = CELL_SIZE(shift);
	int csizemem = (csize * sizeof(char));
	int width = (1 << shift);
	
	char* device_source = NULL;
	char* device_destination = NULL;
	
	//allocate memory
	CHECKERR( cudaMallocManaged(&device_source, csizemem) );
	CHECKERR( cudaMallocManaged(&device_destination, csizemem) );
	
	//copy a into source
	CHECKERR( cudaMemcpy(device_source, *a, csizemem, cudaMemcpyHostToDevice) );
	
	cuda_conway<<<1,1>>>(shift, device_source, device_destination);
	
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
	int size = CELL_SIZE(shift);
	int dimension = (1 << shift);
	for(int y = 0; y < dimension; ++y)
		for(int x = 0; x < dimension; ++x)
			NEXT_CELL(x,y,shift,source,destination);
}