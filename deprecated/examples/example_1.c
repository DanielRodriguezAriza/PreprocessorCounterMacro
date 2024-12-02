/*
	example_1.c
	Basic Counter Example
*/

#include "include/MY_COUNTER_counter.h"

int main()
{
	int x1 = MY_COUNTER;
	#include "include/MY_COUNTER_counter_update.h"
	
	int y1 = MY_COUNTER;
	#include "include/MY_COUNTER_counter_update.h"
	
	int z1 = MY_COUNTER;
	#include "include/MY_COUNTER_counter_update.h"
	
	char const *str1 = MY_COUNTER_TYPE;
	
	return 0;
}
