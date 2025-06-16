#include <stdio.h>

struct pixel
{
    int N;
    int *x;
    int *y;
    unsigned char *R;
    unsigned char *G;
    unsigned char *B;
};

struct pixel pierwszy;

void FunkcjaZapisująca(FILE *plik, struct pixel *pierwszy){
    fprintf(plik,"%d\n",pierwszy->N);
    for (int i = 0; i < pierwszy->N; i++)
    {
        fprintf(plik,"%d\n",pierwszy->x[i]);
        fprintf(plik,"%d\n",pierwszy->y[i]);
        fprintf(plik,"%d\n",pierwszy->R[i]);
        fprintf(plik,"%d\n",pierwszy->G[i]);
        fprintf(plik,"%d\n",pierwszy->B[i]);
    }
    
}