#ifndef CONWAY_MACROS_H
#define CONWAY_MACROS_H

/*Function-like Macros to help with performance*/

/*
	BINARRAY
        instead of a binarray structure, function-like macros will be used
        for accessing data
*/

#define BINARR_GET(i, sourceptr)(\
        ( (sourceptr[(i >> 3)] & (1 << (i & 7))) != 0 )\
        )
#define BINARR_SET(i, sourceptr,value)(\
        (value == 1)\
        ? sourceptr[(i >> 3)] |= (1 << (i & 7))\
        : sourceptr[(i >> 3)] &= ~(1 << (i & 7))\
        )

//return the number of bytes in the binarray
#define BINARR_SIZE(binsize) (1 + (binsize >> 3))


/*
	CELL
	The rest of the functions are for checking values in the cellular automata
*/
//find a linear index for a 2D representation
#define CELL_INDEX(x,y,shift) (\
	( ((x)>=0) && ((y)>=0) && ((x) < (1<<shift)) &&  ((y) < (1<<shift)) )\
	? ((y)<<(shift)) + (x)\
	: -1\
	)

//size of the square array, given a shift
#define CELL_SIZE(shift) (1<<(2*(shift)))

//check if cell is living
#define CHECK_CELL_LIVING(x,y,shift,sourceptr)(\
	(CELL_INDEX((x),(y),(shift)) != -1)\
	? (BINARR_GET(CELL_INDEX((x),(y),(shift)), sourceptr))\
	: (0)\
	)

//sum of neighbors
#define CELL_SUM(x,y,shift,sourceptr)(\
	CHECK_CELL_LIVING(x-1,y-1,shift,sourceptr)\
	+ CHECK_CELL_LIVING(x-1,y,shift,sourceptr)\
	+ CHECK_CELL_LIVING(x-1,y+1,shift,sourceptr)\
	+ CHECK_CELL_LIVING(x,y-1,shift,sourceptr)\
	+ CHECK_CELL_LIVING(x,y+1,shift,sourceptr)\
	+ CHECK_CELL_LIVING(x+1,y-1,shift,sourceptr)\
	+ CHECK_CELL_LIVING(x+1,y,shift,sourceptr)\
	+ CHECK_CELL_LIVING(x+1,y+1,shift,sourceptr)\
	)

//check if a is between(inclusive) b and c
#define BETWEEN(a,b,c) ((a)>=(b) && (a)<=(c))

//check what the cell will be in the next generation, as Conway's Game of Life defines
#define NEXT_CELL(x,y,shift,sourceptr,destptr)(\
	(CHECK_CELL_LIVING((x),(y),(shift),(sourceptr)))\
	?( BINARR_SET(\
		CELL_INDEX(x,y,shift),\
		destptr,\
		BETWEEN(CELL_SUM(x,y,shift,sourceptr),2,3)\
	))\
	:( BINARR_SET(\
		CELL_INDEX(x,y,shift),\
		destptr,\
		(CELL_SUM(x,y,shift,sourceptr) == 3)\
	))\
)

#endif
