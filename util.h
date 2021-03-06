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

static char *concat(char *str1, char *str2) {
    char *output = (char*)malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(output, str1);
    strcat(output, str2);
    return output;
}


#endif