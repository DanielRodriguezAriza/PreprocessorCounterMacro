#include <stdio.h>

#define CAT(x,y) CAT_INTERNAL(x,y)
#define CAT_INTERNAL(x,y) x##y

#define CAT2(x,y) CAT(x,y)
#define CAT3(x1,x2,x3) CAT2(x1, CAT(x2,x3))


#define MY_COUNTER CAT3(DIGIT_2, DIGIT_1, DIGIT_0)

#define DIGIT_0 0
#define DIGIT_1 0
#define DIGIT_2 0


void p(int x)
{
    printf("%d\n", x);
}


int main()
{
    int x = MY_COUNTER;
    #include "update.h"
    
    int y = MY_COUNTER;
    #include "update.h"
    
    int z = MY_COUNTER;
    #include "update.h"
    
    p(x);
    p(y);
    p(z);
    
    return 0;
}
