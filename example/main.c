#include "MY_COUNTER_counter.h"

/*
	Compile with:
		gcc main.c -E -P
	
	to see the results of the used macros.
*/

int main()
{
	/* Counter usage BOOST style */
	int x1 = MY_COUNTER;
	#include MY_COUNTER_UPDATE()
	
	int y1 = MY_COUNTER;
	#include MY_COUNTER_UPDATE()
	
	int z1 = MY_COUNTER;
	#include MY_COUNTER_UPDATE()
	char const *str1 = MY_COUNTER_TYPE;
	
	/* Counter usage single include style */
	/*
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
	*/
	
	return 0;
}
