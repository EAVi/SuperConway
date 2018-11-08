#ifndef CUDA_CONWAY_CUH
#define CUDA_CONWAY_CUH

#define CHECKERR(functioncall){\
	cudaError_t err = functioncall;\
	if (err != cudaSuccess)\
	{\
		printf("function \"#functioncall\" failed (%i)", err);\
		return false;\
	}\
	}

__global__
void cuda_conway(int shift, char * a, char * b);

#endif
