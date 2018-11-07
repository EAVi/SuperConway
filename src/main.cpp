#include <iostream>
#include "conway_macros.h"
#include "conway.h"

using namespace std;

int main(int argc, char * args[])
{
	int shift = 2;//
	char a[16] = {
		0,1,0,0,
		0,0,1,0,
		1,1,1,0,
		0,0,0,0};
	char b[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	conway(shift, a, b);
	conway_print(shift, a);
	
	return 0;
}