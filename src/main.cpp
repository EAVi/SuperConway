#include <iostream>
#include "conway.h"

using namespace std;

int main(int argc, char * args[])
{
	int shift = 2;//
	char a[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	char b[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	cout << CELL_INDEX(0,1,shift) << ',' << CELL_SUM(1,1,shift,a) << ',' << CHECK_CELL_LIVING(0,0,shift,a);
	NEXT_CELL(0,0,shift,a,b);
	NEXT_CELL(1,1,shift,a,b);
	return 0;
}