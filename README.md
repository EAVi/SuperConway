# SuperConway
Conway's Game of life, to be used on a CUDA cluster

- [x] Using CUDA
- [x] Using MPI

#### Arguments:
1. integer shift S, where the number of cells _n_ = 2<sup>S</sup> * 2<sup>S</sup>.
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
| 2<sup>28</sup> | 46.098278 s  | 3.999100 s | 17.623471 s | 4.051098 s |  2.186178 s |
| 2<sup>30</sup> | 149.100078 s | 16.671971 s | 40.468941 s |  13.633362 s | 2.009627 s |

#### Complexity:
The complexity clearly is &in; __&Theta;__(_n_), where the number of cells _n_ = 2<sup>S</sup> * 2<sup>S</sup>.
