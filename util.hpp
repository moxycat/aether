#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/* returns integer from [min, max] */
inline uint32_t rand_int(uint32_t min, uint32_t max) {
    return (rand() % (max - min + 1)) + min;
}


#endif
