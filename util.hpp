#ifndef _UTIL_HPP_
#define _UTIL_HPP_


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>



using namespace std;

/* returns integer from [min, max] */
inline uint32_t rand_int(uint32_t min, uint32_t max) {
    return (rand() % (max - min + 1)) + min;
}


static char *concat(const char *str1, const char *str2) {
    char *output = (char*)malloc(strlen(str1) + strlen(str2) + 1);	//for music and sound
    strcpy(output, str1);
    strcat(output, str2);
    return output;
}

#endif
