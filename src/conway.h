#ifndef CONWAY_H
#define CONWAY_H

//do one iteration of the conway loop
void conway(int shift, char* source, char* destination, int ymin = -1, int ymax = -1, int numloops = 1);

//conway loop using MPI
void conway_mpi(int shift, char* source, char* destination, int numloops, bool use_cuda, int np, int rank);

//print conway's life
void conway_print(int shift, char* source);

//print specific area in conway's life
void conway_print_bounded(int shift, char* source, int x1, int x2, int y1, int y2);

#endif
