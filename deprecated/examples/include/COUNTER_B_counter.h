#define COUNTER_B_USE_COMPILER_COUNTER 0
#ifndef COUNTER_B
	#if (COUNTER_B_USE_COMPILER_COUNTER) && defined(__COUNTER__)
		#define COUNTER_B __COUNTER__
		#define COUNTER_B_UPDATE() "COUNTER_B_counter_empty.h"
		#define COUNTER_B_TYPE "__COUNTER__"
	#else
		#define COUNTER_B 0
		#define COUNTER_B_UPDATE() "COUNTER_B_counter_update.h"
		#define COUNTER_B_TYPE "DRA_COUNTER"
	#endif
#endif
