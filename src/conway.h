#ifndef CONWAY_H
#define CONWAY_H

//do one iteration of the conway loop
void conway(int shift, char* source, char* destination);

//overload do some number of loops
void conway(int shift, char* source, char* destination, int numloops);

//print conway's life
void conway_print(int shift, char* source);

#endif
