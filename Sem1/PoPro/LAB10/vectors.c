







#include "vecout.h"
#include "veccalc.h"
#include "vecin.h"


int main()
{
    static_vector_t v1,v2,v3;
    
    printf("\n\n\nSTART:\n");
    printf("Author: Jan Czechowski\n");

    printf("Define v1:\n");
    switch(vec_fromkeyboard(&v1))
    {
        case _VEC_OK:
            break;
        case _VEC_NULL:
            printf("Error: NULL pointer\n");
            return 0;
        case _VEC_DIM:
            printf("Error: invalid vector length\n");
            return 0;
        case _VEC_INPUT:
            printf("Error: not a number\n");
            return 0;
        default:
            printf("Error: unknown\n");
            return 0;
     }
    
    printf("\nDefine v2:\n");
    switch(vec_fromkeyboard(&v2))
    {
        case _VEC_OK:
            break;
        case _VEC_NULL:
            printf("Error: NULL pointer\n");
            return 0;
        case _VEC_DIM:
            printf("Error: invalid vector length\n");
            return 0;
        case _VEC_INPUT:
            printf("Error: not a number\n");
            return 0;
        default:
            printf("Error: unknown\n");
            return 0;
     }
    
    //(b) display v1 and v2 here using functions defined in vecout.h
    printf("\nVector v1 (horizontal):\n");
    vec_print_horizontally(&v1);
 
    printf("\nVector v1 (vertical):\n");
    vec_print_vertically(&v1);
 
    printf("\nVector v2 (horizontal):\n");
    vec_print_horizontally(&v2);
 
    printf("\nVector v2 (vertical):\n");
    vec_print_vertically(&v2);
    double dot_product=0.0;
    //(c) calculate dot product of v1 and v2 using functions defined in veccalc.h. Provide full error handling. 
    {
        case _VEC_OK:
            printf("\nv1 * v2 = %f\n", dot_product);
            break;
        case _VEC_NULL:
            printf("Error: NULL pointer\n");
            return 0;
        case _VEC_DIM:
            printf("Error: dimension mismatch\n");
            return 0;
        default:
            printf("Error: unknown\n");
            return 0;
    }


    //(d) calculate v3=v1+v2 using functions defined in veccalc.h. Provide full error handling. 
    switch(vec_add(&v1, &v2, &v3))
    {
        case _VEC_OK:
            printf("\nv1 + v2 = ");
            vec_print_horizontally(&v3);
            break;
        case _VEC_NULL:
            printf("Error: NULL pointer\n");
            return 0;
        case _VEC_DIM:
            printf("Error: dimension mismatch\n");
            return 0;
        default:
            printf("Error: unknown\n");
            return 0;
    }

    //(e) use vec_print_to_compare to inspect whether the sum is correct
    printf("\nComparison of v1, v2, and v3:\n");
    vec_print_to_compare(&v1, &v2, &v3);
    
    

    return 0;
}


//Task 3:
//Answer 1:
//Answer 2:




