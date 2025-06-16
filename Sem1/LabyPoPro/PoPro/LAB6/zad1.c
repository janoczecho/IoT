//Jan Czechowski

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int wyswietlWektor(int wektor[], int rozmiar)
{
    for (int i = 0; i < rozmiar; i++) {
        printf("\t%d", wektor[i]);
    }
    printf("\n");
}

int main(void)
{
    int ilosWierszy = 5;
    int iloscKolumn =10;
    srand(time(NULL));
    int tablica[ilosWierszy][iloscKolumn];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            tablica[i][j] = rand()%100;
        }
        
    }

    for (int i = 0; i < ilosWierszy; i++)
    {
        printf("Wektor %d: ", (i + 1));
        wyswietlWektor(tablica[i], iloscKolumn);
    }

    return 0;
}