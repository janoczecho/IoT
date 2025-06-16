#include <stdio.h>
#include <stdlib.h>

int main(void){
    int n;
    int suma = 0;
    printf("Podaj liczbe elementow tablicy:\n");
    scanf("%d", &n);
    int *tablica = (int *)malloc(n * sizeof(int));
    if (tablica==NULL)
    {
        puts("Blad alokacji pamieci");
        return 1;
    }
    
    for (int i = 0; i < n; i++)
    {
        printf("Podaj %d liczbe:\n",i+1);
        scanf("%d", &tablica[i]);
    }
    puts("Wprowadzone zostaly te liczby:");
    for (int i = 0; i < n; i++)
    {
        printf("Liczba %d to: %d\n", i+1, tablica[i]);
        suma += tablica[i];
    }
    puts("Suma liczb to:");
    printf("%d", suma);
    free(tablica);
    return 0;
}