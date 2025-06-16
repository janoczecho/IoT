#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int wiek;
    char *nazwisko;
}osoba;



int main(void){

    int ileOsob = 2;
    char nazwisko1[] = "Kowalski";
    char nazwisko2[] = "Nowak";
    osoba *osoby = (osoba *)malloc(ileOsob*sizeof(osoba));
    if (osoby == NULL)
    {
        puts("Blad alokacji");
        return 1;
    }

    osoby[0].wiek = 19;
    osoby[0].nazwisko = malloc(strlen(nazwisko1)*sizeof(char)+1);
    if (osoby[0].nazwisko==NULL)
    {
        puts("Blad alokacji");
        free(osoby);
        return 1;
    }
    strcpy(osoby[0].nazwisko,nazwisko1);

    osoby[1].wiek = 20;
    osoby[1].nazwisko = malloc(strlen(nazwisko2)*sizeof(char)+1);
    if (osoby[1].nazwisko==NULL)
    {
        puts("Blad alokacji");
        free(osoby[0].nazwisko);
        free(osoby);
        return 1;
    }
    strcpy(osoby[1].nazwisko,nazwisko2);

    FILE *plik = fopen("osoby_3.bin","wb");
    if (plik==NULL)
    {
        puts("Blad otwarcia pliku");
        free(osoby[0].nazwisko);
        free(osoby[1].nazwisko);
        free(osoby);
        return 1;
    }
    
    for (int i = 0; i < ileOsob; i++)
    {
        fwrite(&osoby[i].wiek,sizeof(int),1,plik);
        fwrite(osoby[i].nazwisko,sizeof(char),strlen(osoby[i].nazwisko) + 1,plik);
    }

    FILE *plikTekst = fopen("osoby3.txt", "w");
        if (plikTekst==NULL)
    {
        puts("Blad otwarcia pliku");
        free(osoby[0].nazwisko);
        free(osoby[1].nazwisko);
        free(osoby);
        fclose(plik);
        return 1;
    }

    for (int i = 0; i < ileOsob; i++)
    {
        fprintf(plikTekst,"%d\t",osoby[i].wiek);
        fprintf(plikTekst,"%s\n",osoby[i].nazwisko);
    }

    free(osoby[0].nazwisko);
    free(osoby[1].nazwisko);
    free(osoby);
    fclose(plik);
    fclose(plikTekst);
    return 0;
}