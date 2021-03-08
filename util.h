#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdlib.h>
#include <string.h>

/*
    generate a random integer within a closed interval
    [min, max]
*/
inline int rand_int(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

#endif