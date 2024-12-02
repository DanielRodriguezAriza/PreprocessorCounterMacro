/*
	example_2.c
	Multiple Counters Example
*/

#include "include/COUNTER_A_counter.h"
#include "include/COUNTER_B_counter.h"

int main()
{
	int a1 = COUNTER_A;
	#include "include/COUNTER_A_counter_update.h"
	
	int a2 = COUNTER_A;
	#include "include/COUNTER_A_counter_update.h"
	
	int a3 = COUNTER_A;
	#include "include/COUNTER_A_counter_update.h"
	
	int b1 = COUNTER_B;
	#include "include/COUNTER_B_counter_update.h"
	
	int b2 = COUNTER_B;
	#include "include/COUNTER_B_counter_update.h"
	
	int b3 = COUNTER_B;
	#include "include/COUNTER_B_counter_update.h"
	
	return 0;
}
