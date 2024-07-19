#define COUNTER_A_USE_COMPILER_COUNTER 0
#ifndef COUNTER_A
	#if (COUNTER_A_USE_COMPILER_COUNTER) && defined(__COUNTER__)
		#define COUNTER_A __COUNTER__
		#define COUNTER_A_UPDATE() "COUNTER_A_counter_empty.h"
		#define COUNTER_A_TYPE "__COUNTER__"
	#else
		#define COUNTER_A 0
		#define COUNTER_A_UPDATE() "COUNTER_A_counter_update.h"
		#define COUNTER_A_TYPE "DRA_COUNTER"
	#endif
#endif
