#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int wiek;
    char *imie;
}osoba;


int main(void){
    int ileOsob = 2;
    osoba osoby[ileOsob];

    osoby[0].wiek = 19;
    osoby[1].wiek = 20;
    osoby[0].imie = malloc(strlen("Janek")+1);
    if (osoby[0].imie == NULL)
    {
        puts("Blad alokacji pamieci");
        return 1;
    }
    strcpy(osoby[0].imie,"Janek");


    osoby[1].imie = malloc(strlen("Julka")+1);
    if (osoby[1].imie == NULL)
    {
        puts("Blad alokacji pamieci");
        free(osoby[0].imie);
        return 1;
    }
    strcpy(osoby[1].imie,"Julka");


    FILE *plik = fopen("osoby_2.bin", "wb");
    if (plik==NULL)
    {
        puts("Blad otwarcia pliku");
        return 1;
    }

    for (int i = 0; i < ileOsob; i++)
    {
        fwrite(&osoby[i].wiek,sizeof(int), 1, plik);
        fwrite(osoby[i].imie,sizeof(char),strlen(osoby[i].imie)+1, plik);
    }
    

    fclose(plik);
    for (int i = 0; i < ileOsob; i++)
    {
        free(osoby[i].imie);
    }
    
    return 0;
}