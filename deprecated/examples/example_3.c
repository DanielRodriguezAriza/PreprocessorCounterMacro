/*
	example_3.c
	Assigning counter result to macros vs to variables
	
	Just like BOOST's macro counter, this macro counter should not be used with macros, as it will contain the same value for all macros defined to the counter.
	
	The problem comes from the need to include the update file.
	
	Even including the update file after each macro definition does not fix the problem, it will always be defined to the last value of the counter.
	
	This happens because all we're doing with the define is defining the macros to the same macro as the counter's macro, meaning that once it is used in the program, it will be as if we had called the counter macro in place.
	
	This happens because the preprocessor does not contain state the same way a regular program does.
	
	The __COUNTER__ macro offered by most compilers does not have this problem since it is stateful.
	
	A way to fix this problem is to include the update file before usage of the macro, which defeats the purpose of defining macros to the value of the counter, as it does not actually save the state at the point in which the macro was initially called.
	
	NOTE: Macro expansion does not fix this problem.
*/

#include "include/MY_COUNTER_counter.h"

#define MACRO1 MY_COUNTER
#include "include/MY_COUNTER_counter_update.h"

#define MACRO2 MY_COUNTER
#include "include/MY_COUNTER_counter_update.h"

#define MACRO3 MY_COUNTER
#include "include/MY_COUNTER_counter_update.h"

#include "example_3.h"

int main()
{
	int var1 = MY_COUNTER;
	#include "include/MY_COUNTER_counter_update.h"
	
	int var2 = MY_COUNTER;
	#include "include/MY_COUNTER_counter_update.h"
	
	int var3 = MY_COUNTER;
	#include "include/MY_COUNTER_counter_update.h"
	
	printf("\nVariables:\nvar1 = %d\nvar2 = %d\nvar3 = %d\n", var, var2, var3);
	printf("\nMacros:\nMACRO1 = %d\nMACRO2 = %d\nMACRO3 = %d\n", MACRO1, MACRO2, MACRO3);
	
	return 0;
}
