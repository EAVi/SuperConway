# SuperConway
Conway's Game of life, to be used on a CUDA cluster

[x] Of a grid of $2^n * 2^n$
[x] Using CUDA
[x] Using MPI

#### Arguments:
1. integer shift S, where $N = 2^S * 2^S$.
2. boolean usecuda. 

##### Running:
Here's what I use if I plan on running CUDA on multiple nodes:
```
mpirun -np 10 -hostfile hostfile --map-by ppr:1:node sconway 14 1
```
And if I do not plan on using CUDA:
```
mpirun -hostfile hostfile sconway 14 0
```
