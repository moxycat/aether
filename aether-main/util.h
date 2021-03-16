#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdlib.h>
#include <math.h>

/*
    generate a random integer within a closed interval
    [min, max]
*/
inline int rand_int(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

inline int numlen(int n) {
    return (int)ceil(log10((double)n));
}

#endif