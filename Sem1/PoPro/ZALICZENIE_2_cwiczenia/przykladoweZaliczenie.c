#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int wiek;
    char *nazwisko;
}osoba;

int main(void){
    int n = 2;
    int wiek1 = 19;
    int wiek2 = 20;
    char nazwisko1[] = "Czechowski";
    char nazwisko2[] = "Orzel";

    osoba *lista = (osoba *)malloc(n * sizeof(osoba));
    if (lista==NULL)
    {
        puts("Blad alokacji pamieci");
        return 1;
    }

    lista[0].wiek = wiek1;
    lista[0].nazwisko = (char *)malloc((strlen(nazwisko1)+1)*sizeof(char));
    if (lista[0].nazwisko==NULL)
    {
        puts("Blad alokacji pamieci");
        for (int i = 0; i < n; i++)
        {
            free(lista[i].nazwisko);
        }
        free(lista);
        return 1;
    }
    strcpy(lista[0].nazwisko,nazwisko1);

    lista[1].wiek = wiek2;
    lista[1].nazwisko = (char *)malloc((strlen(nazwisko2)+1)*sizeof(char));
    if (lista[1].nazwisko==NULL)
    {
        puts("Blad alokacji pamieci");
        for (int i = 0; i < n; i++)
        {
            free(lista[i].nazwisko);
        }
        free(lista);
        return 1;
    }
    strcpy(lista[1].nazwisko,nazwisko2);

    FILE *plik = fopen("osoby.bin", "wb");
    if (plik==NULL)
    {
        puts("Blad otwarcia pliku");
        for (int i = 0; i < n; i++)
        {
            free(lista[i].nazwisko);
        }
        free(lista);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        int len = strlen(lista[i].nazwisko) + 1;
        fwrite(&lista[i].wiek, sizeof(int), 1, plik);
        fwrite(lista[i].nazwisko, sizeof(char), len, plik);
    }

    fclose(plik);

    for (int i = 0; i < n; i++)
    {
        free(lista[i].nazwisko);
    }
    free(lista);
    return 1;
}