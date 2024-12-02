#ifdef COUNTER_B
	#if COUNTER_B < 1000
		#include "COUNTER_B_counter_1000.h"
	#elif COUNTER_B < 2000
		#include "COUNTER_B_counter_2000.h"
	#elif COUNTER_B < 3000
		#include "COUNTER_B_counter_3000.h"
	#elif COUNTER_B < 4000
		#include "COUNTER_B_counter_4000.h"
	#elif COUNTER_B < 5000
		#include "COUNTER_B_counter_5000.h"
	#elif COUNTER_B < 6000
		#include "COUNTER_B_counter_6000.h"
	#elif COUNTER_B < 7000
		#include "COUNTER_B_counter_7000.h"
	#elif COUNTER_B < 8000
		#include "COUNTER_B_counter_8000.h"
	#elif COUNTER_B < 9000
		#include "COUNTER_B_counter_9000.h"
	#elif COUNTER_B <= 10000
		#include "COUNTER_B_counter_10000.h"
	#endif
#endif
