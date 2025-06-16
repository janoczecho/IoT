#include "vecout.h"

void vec_print_horizontally(const static_vector_t *v )
{
    if (v==NULL) 
    {
        printf("Vector is NULL\n");
        return;
    }

    if (v->length==0) 
    {
        printf("Vector is EMPTY\n");
        return;
    }

    if (v->length>_VEC_MAX_LENGTH_) 
    {
        printf("Error: invalid length\n");
        return;
    }

    for (unsigned int ii=0;ii<v->length;ii++) printf("%f ",v->coordinates[ii]);
    printf("\n");
   
}


void vec_print_vertically(const static_vector_t *v )
{
if (v==NULL) 
    {
        printf("Vector is NULL\n");
        return;
    }

    if (v->length==0) 
    {
        printf("Vector is EMPTY\n");
        return;
    }

    if (v->length>_VEC_MAX_LENGTH_) 
    {
        printf("Error: invalid length\n");
        return;
    }

    for (unsigned int ii=0;ii<v->length;ii++) printf("%f\n",v->coordinates[ii]);
    printf("\n");
 
}


void vec_print_to_compare(const static_vector_t *v1,const static_vector_t *v2, const static_vector_t *v3  )
{
    if (v1==NULL) 
    {
        printf("Error: v1 is NULL\n");
        return;
    }

    if (v2==NULL) 
    {
        printf("Error: v2 is NULL\n");
        return;
    }

    if (v1->length!=v2->length)
    {
        printf("Error: vectors must have the same length\n");
        return;
    }

    if ((v3!=NULL)&&(v1->length!=v3->length))
    {
        printf("Error: vectors must have the same length\n");
        return;
    }

    if (v1->length>_VEC_MAX_LENGTH_) 
    {
        printf("Error: invalid length\n");
        return;
    }

    if (v1->length==0) 
    {
        printf("Vectors are EMPTY\n");
        return;
    }


    for (unsigned int ii=0;ii<v1->length;ii++) 
    {
        printf("%20f %20f",v1->coordinates[ii],v2->coordinates[ii]);
        if (v3!=NULL) printf("%20f\n",v3->coordinates[ii]); else printf("\n");
    }
    
    printf("\n");

}
