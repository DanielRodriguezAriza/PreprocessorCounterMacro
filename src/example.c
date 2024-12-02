#include <stdio.h>
#include "counter.h"

#define p(x) printf("%d\n", x);

int main()
{
	int x0 = MY_COUNTER;
	#include "update.h"
	
	int x1 = MY_COUNTER;
	#include "update.h"
	
	int x2 = MY_COUNTER;
	#include "update.h"
	
	int x3 = MY_COUNTER;
	#include "update.h"
	
	int x4 = MY_COUNTER;
	#include "update.h"
	
	int x5 = MY_COUNTER;
	#include "update.h"
	
	int x6 = MY_COUNTER;
	#include "update.h"
	
	int x7 = MY_COUNTER;
	#include "update.h"
	
	int x8 = MY_COUNTER;
	#include "update.h"
	
	int x9 = MY_COUNTER;
	#include "update.h"
	
	int x10 = MY_COUNTER;
	#include "update.h"
	
	int x11 = MY_COUNTER;
	#include "update.h"
	
	p(x0);
	p(x1);
	p(x2);
	p(x3);
	p(x4);
	p(x5);
	p(x6);
	p(x7);
	p(x8);
	p(x9);
	p(x10);
	p(x11);
	
	return 0;
}
