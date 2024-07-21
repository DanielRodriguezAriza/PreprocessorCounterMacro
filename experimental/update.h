#define UPDATE_DIGIT_0

#ifdef UPDATE_DIGIT_0
    #if DIGIT_0 == 0
        #undef DIGIT_0
        #define DIGIT_0 1
    #elif DIGIT_0 == 1
        #undef DIGIT_0
        #define DIGIT_0 2
    #elif DIGIT_0 == 2
        #undef DIGIT_0
        #define DIGIT_0 3
    #elif DIGIT_0 == 3
        #undef DIGIT_0
        #define DIGIT_0 4
    #elif DIGIT_0 == 4
        #undef DIGIT_0
        #define DIGIT_0 5
    #elif DIGIT_0 == 5
        #undef DIGIT_0
        #define DIGIT_0 6
    #elif DIGIT_0 == 6
        #undef DIGIT_0
        #define DIGIT_0 7
    #elif DIGIT_0 == 7
        #undef DIGIT_0
        #define DIGIT_0 8
    #elif DIGIT_0 == 8
        #undef DIGIT_0
        #define DIGIT_0 9
    #elif DIGIT_0 == 9
        #undef DIGIT_0
        #define DIGIT_0 0
        #define UPDATE_DIGIT_1
    #endif
#endif

#ifdef UPDATE_DIGIT_1
    #if DIGIT_1 == 0
        #undef DIGIT_1
        #define DIGIT_1 1
    #elif DIGIT_1 == 1
        #undef DIGIT_1
        #define DIGIT_1 2
    #elif DIGIT_1 == 2
        #undef DIGIT_1
        #define DIGIT_1 3
    #elif DIGIT_1 == 3
        #undef DIGIT_1
        #define DIGIT_1 4
    #elif DIGIT_1 == 4
        #undef DIGIT_1
        #define DIGIT_1 5
    #elif DIGIT_1 == 5
        #undef DIGIT_1
        #define DIGIT_1 6
    #elif DIGIT_1 == 6
        #undef DIGIT_1
        #define DIGIT_1 7
    #elif DIGIT_1 == 7
        #undef DIGIT_1
        #define DIGIT_1 8
    #elif DIGIT_1 == 8
        #undef DIGIT_1
        #define DIGIT_1 9
    #elif DIGIT_1 == 9
        #undef DIGIT_1
        #define DIGIT_1 0
        #define UPDATE_DIGIT_2
    #endif
#endif

#ifdef UPDATE_DIGIT_2
    #if DIGIT_2 == 0
        #undef DIGIT_2
        #define DIGIT_2 1
    #elif DIGIT_2 == 1
        #undef DIGIT_2
        #define DIGIT_2 2
    #elif DIGIT_2 == 2
        #undef DIGIT_2
        #define DIGIT_2 3
    #elif DIGIT_2 == 3
        #undef DIGIT_2
        #define DIGIT_2 4
    #elif DIGIT_2 == 4
        #undef DIGIT_2
        #define DIGIT_2 5
    #elif DIGIT_2 == 5
        #undef DIGIT_2
        #define DIGIT_2 6
    #elif DIGIT_2 == 6
        #undef DIGIT_2
        #define DIGIT_2 7
    #elif DIGIT_2 == 7
        #undef DIGIT_2
        #define DIGIT_2 8
    #elif DIGIT_2 == 8
        #undef DIGIT_2
        #define DIGIT_2 9
    #elif DIGIT_2 == 9
        #undef DIGIT_2
        #define DIGIT_2 0
        #define UPDATE_DIGIT_0
    #endif
#endif


#undef UPDATE_DIGIT_0
#undef UPDATE_DIGIT_1
#undef UPDATE_DIGIT_2
