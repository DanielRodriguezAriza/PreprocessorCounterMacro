#define MY_COUNTER_USE_COMPILER_COUNTER 0
#ifndef MY_COUNTER
	#if (MY_COUNTER_USE_COMPILER_COUNTER) && defined(__COUNTER__)
		#define MY_COUNTER __COUNTER__
		#define MY_COUNTER_UPDATE() "MY_COUNTER_counter_empty.h"
		#define MY_COUNTER_TYPE "__COUNTER__"
	#else
		#define MY_COUNTER 0
		#define MY_COUNTER_UPDATE() "MY_COUNTER_counter_update.h"
		#define MY_COUNTER_TYPE "DRA_COUNTER"
	#endif
#endif
