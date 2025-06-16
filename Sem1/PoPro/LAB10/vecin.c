#include "vecin.h"

int vec_fromkeyboard(static_vector_t *v )
{
    if (v==NULL) return _VEC_NULL;
    
    v->length=0;
    
    long L;
    printf("Input vector length:\n");
    if (scanf("%ld",&L)!=1) return _VEC_INPUT;
    
    if ((L<=0)||(L>_VEC_MAX_LENGTH_)) return _VEC_DIM;

    v->length=(unsigned int)L;
    
    for (unsigned int ii=0;ii<v->length;ii++)
    {
        double D;
        printf("Input coordinate no. %u:\n",ii+1);
        if (scanf("%lf",&D)!=1) return _VEC_INPUT;
        v->coordinates[ii]=D;
    }

    printf("OK!\n");
    return _VEC_OK;

}