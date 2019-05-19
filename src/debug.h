// File name    :   "debug.h"
// Author       :   Liuchuyao Xu (Raymond)
// Description  :   Macros for enabling/disabling debug printf().


// Comment the line below to disable debug printf().
#define DEBUG

#ifdef  DEBUG
    #include <stdio.h>
    #define  DEBUG_PRINT(fmt, ...) printf(fmt, __VA_ARGS__)
#else
    #define  DEBUG_PRINT(fmt, ...) if(0)
#endif
        