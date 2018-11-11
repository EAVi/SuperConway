# SuperConway
Conway's Game of life, to be used on a CUDA cluster

- [x] Using CUDA
- [x] Using MPI

#### Arguments:
1. integer shift S, where _n_ = <sup>S</sup> * 2<sup>S</sup>.
2. boolean usecuda, will call CUDA on 1, will use CPU on 0.

##### Running:
Here's what I use if I plan on running CUDA on multiple nodes:
```
mpirun -np 10 -hostfile hostfile --map-by ppr:1:node sconway 14 1
```
And if I do not plan on using CUDA:
```
mpirun -hostfile hostfile sconway 14 0
```
