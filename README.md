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
#### Performance:
The amount of time to calculate the next generation is as followed.
The CPU is an Intel i7-7700k, the GPU is a GTX 1050 Ti.

| Number of cells | 1 CPU | 1 GPU | 4 CPU cores | 40 CPU cores | 10 GPUs |
| --- | --- | --- | --- | --- | --- |
| 2<sup>28</sup> | 46.098278 s  | 7.219610 s | 17.623471 s | 4.051098 s | 2.493765 s |
