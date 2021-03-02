#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* returns integer from [min, max] */
inline uint32_t rand_int(uint32_t min, uint32_t max) {
    return (rand() % (max - min + 1)) + min;
}

/* converts a 2d array index into a linear one */
inline uint32_t square_to_linear(uint32_t row, uint32_t col, uint32_t width) {
    return row * width + col;
}

#endif