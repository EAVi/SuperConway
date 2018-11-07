#include "conway.h"
#include "conway_macros.h"
#include <cstdio>

void conway(int shift, char* source, char* destination)
{
	int dimension_size = (1 << shift);
	int total_size = CELL_SIZE(shift);
	for(int y = 0; y < dimension_size; ++y)
		for(int x = 0; x < dimension_size; ++x)
			NEXT_CELL(x,y,shift,source,destination);
	
	//copy the destination back to the source
	for(int i = 0; i < total_size; ++i)
		source[i] = destination[i];
}

void conway_print(int shift, char* source)
{
	int dimension_size = (1 << shift);
	int total_size = CELL_SIZE(shift);
	for(int y = 0; y < dimension_size; ++y)
	{
		for(int x = 0; x < dimension_size; ++x)
		{
			if(CHECK_CELL_LIVING(x,y,shift,source))
				printf("#");
			else printf("-");
		}
		printf("\n");
	}
}