#include <stdio.h>

typedef struct{
    char *nazwisko;
    int wiek;
}dane;

void f(dane *t, int N, FILE *fp){
    for (int i = 0; i < N; i++)
    {
        fwrite(t[i].wiek,sizeof(t[i].wiek),1,fp);
        
        fwrite(t[i].nazwisko,)
    }
    
}