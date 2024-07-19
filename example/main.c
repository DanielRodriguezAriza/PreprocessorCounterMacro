#include "my_counter.h"

/*
	Compile with:
		gcc main.c -E -P
	
	to see the results of the used macros.
*/

int main()
{
	/* Counter usage BOOST style */
	int x1 = MY_COUNTER;
	#include UPDATE_MY_COUNTER()
	
	int y1 = MY_COUNTER;
	#include UPDATE_MY_COUNTER()
	
	int z1 = MY_COUNTER;
	#include UPDATE_MY_COUNTER()
	char const *str1 = MY_COUNTER_TYPE;
	
	/* Counter usage single include style */
	int x2 =
		#include MY_COUNTER_GET()
	;
	
	int y2 =
		#include MY_COUNTER_GET()
	;
	
	int z2 =
		#include MY_COUNTER_GET()
	;
	
	char const *str2 = MY_COUNTER_TYPE;
	
	return 0;
}
