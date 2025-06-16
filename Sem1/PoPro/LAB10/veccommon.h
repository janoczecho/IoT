#ifndef VECCOMMON_H
#define VECCOMMON_H

#include <stdio.h>

#define _VEC_MAX_LENGTH_ (5)
#define _VEC_OK (0)
#define _VEC_DIM (-1)
#define _VEC_NULL (-2)
#define _VEC_INPUT (-3)



typedef struct static_vector 
{
    double coordinates[_VEC_MAX_LENGTH_];
    unsigned int length;
}static_vector_t;

#endif //VECCOMMON_H
