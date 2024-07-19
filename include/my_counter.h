#ifndef MY_COUNTER
	#ifdef __COUNTER__
		#define MY_COUNTER __COUNTER__
		#define UPDATE_MY_COUNTER() "my_counter_empty.h"
		#define MY_COUNTER_TYPE "__COUNTER__"
	#else
		#define MY_COUNTER 0
		#define UPDATE_MY_COUNTER() "my_counter.h"
		#define MY_COUNTER_TYPE "MY_COUNTER"
	#endif
	#define MY_COUNTER_GET() "my_counter_get.h"
#else
	#if MY_COUNTER < 1000
		#include "my_counter_1000.h"
	#elif MY_COUNTER < 2000
		#include "my_counter_2000.h"

	#elif MY_COUNTER < 3000
		#include "my_counter_3000.h"

	#elif MY_COUNTER < 4000
		#include "my_counter_4000.h"

	#elif MY_COUNTER < 5000
		#include "my_counter_5000.h"

	#elif MY_COUNTER < 6000
		#include "my_counter_6000.h"

	#elif MY_COUNTER < 7000
		#include "my_counter_7000.h"

	#elif MY_COUNTER < 8000
		#include "my_counter_8000.h"

	#elif MY_COUNTER < 9000
		#include "my_counter_9000.h"

	#endif
#endif
