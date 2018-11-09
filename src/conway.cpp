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

void conway(int shift, char* source, char* destination, int numloops)
{
	for(int i = 0; i < numloops; ++i)
		conway(shift, source, destination);
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
	printf("\n");
}

void conway_print_bounded(int shift, char* source, int x1, int x2, int y1, int y2)
{
        int dimension_size = (1 << shift);
        int total_size = CELL_SIZE(shift);
        for(int y = y1; y < y2; ++y)
        {
                for(int x = x1; x < x2; ++x)
                {
                        if(CHECK_CELL_LIVING(x,y,shift,source))
                                printf("#");
                        else printf("-");
                }
                printf("\n");
        }
        printf("\n");

}
