#Makefile for the Supersieve function

#executable name
EXEC=sconway
#source files
OMPISRCS=main.cpp conway.cpp
CUDASRCS=cuda_conway.cu
#object files
OMPIOBJS=$(OMPISRCS:.cpp=.o)
CUDAOBJS=$(CUDASRCS:.cu=.o)

OBJS=$(OMPIOBJS)
OBJS+=$(CUDAOBJS)

$(EXEC): $(OMPIOBJS) $(CUDAOBJS)
	mpic++ -o $@ $(OBJS) -lcudart -L /usr/local/cuda/lib64 

$(OMPIOBJS):
	mpic++ -c $*.cpp

$(CUDAOBJS):
	nvcc -ccbin /usr/bin/gcc53 -c $*.cu

clean:
	rm $(OMPIOBJS) $(CUDAOBJS)
