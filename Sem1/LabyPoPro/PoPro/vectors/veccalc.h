#ifndef VECCALC_H
#define VECCALC_H


#include "veccommon.h"

double  vec_length(const static_vector_t *v, int *err );
double  vec_dotproduct(const static_vector_t *v1, const static_vector_t *v2, int *err);
void    vec_sum(const static_vector_t *v1, const static_vector_t *v2, static_vector_t *v, int *err);


#endif //VECCALC_H

