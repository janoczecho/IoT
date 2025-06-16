#include "veccalc.h"
#include <math.h>


#define _vec_emit_error(x) {if (err!=NULL) *err=x; }


double  vec_length(const static_vector_t *v, int *err )
{
    if (v==NULL)
    {
        _vec_emit_error(_VEC_NULL)
        return 0.0;
    }

    if ((v->length==0)||(v->length>_VEC_MAX_LENGTH_))
    {
         _vec_emit_error(_VEC_DIM)
        return 0.0;
    }

    double temp=0.0;
    for(unsigned int ii=0;ii<v->length;ii++) temp+=v->coordinates[ii] * v->coordinates[ii]; 
    
    _vec_emit_error(_VEC_OK)
    return sqrt(temp);

}

double  vec_dotproduct(const static_vector_t *v1, const static_vector_t *v2, int *err)
{
    if ((v1==NULL)||(v2==NULL))
    {
        _vec_emit_error(_VEC_NULL)
        return 0.0;
    }

    if ((v1->length==0)||(v1->length>_VEC_MAX_LENGTH_))
    {
         _vec_emit_error(_VEC_DIM)
        return 0.0;
    }

    if (v1->length!=v2->length)
    {
         _vec_emit_error(_VEC_DIM)
        return 0.0;
    }

    double temp=0.0;
    for(unsigned int ii=0;ii<v1->length;ii++) temp+=v1->coordinates[ii] * v2->coordinates[ii]; 
    _vec_emit_error(_VEC_OK)
    return temp;

}

void    vec_sum(const static_vector_t *v1, const static_vector_t *v2,  static_vector_t *v, int *err)
{
    if ((v1==NULL)||(v2==NULL)||(v==NULL))
    {
        _vec_emit_error(_VEC_NULL)
        return ;
    }

    if ((v1->length==0)||(v1->length>_VEC_MAX_LENGTH_))
    {
         _vec_emit_error(_VEC_DIM)
        return ;
    }

    if (v1->length!=v2->length)
    {
         _vec_emit_error(_VEC_DIM)
        return ;
    }

    v->length=v1->length;
    for(unsigned int ii=0;ii<v1->length;ii++) v->coordinates[ii]=v1->coordinates[ii] + v2->coordinates[ii]; 
    _vec_emit_error(_VEC_OK)
}
