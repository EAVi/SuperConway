#ifndef SCALE_H
#define SCALE_H

/*
	Scale macros based off of the scale.cpp in EAVi/SuperSieve
*/

//returns the starting point for the processor's workload
#define ASSIGN_MIN(size, np, rank) ((size)*(rank)/(np))

//returns the terminator for the processor's workload (;i < max ; ++i)
#define ASSIGN_MAX(size, np, rank) (ASSIGN_MIN(size,np,(rank) + 1))

//returns the size of the processor's workload
#define ASSIGN_SIZE(size,np, rank) (ASSIGN_MAX(size,np, rank) - ASSIGN_MIN(size,np,rank))

//find the processor based on index
#define ASSIGN_FIND(size, np, index) (((index + 1) * np - 1) / size)

#endif
