#include <stdio.h>
int main(void){
    typedef struct
    {
        char imie[50];
        int wiek;
    }osoba;
    osoba osoba1 = {"Janek", 19};
    osoba osoba2 = {"Maria", 15};
    osoba osoba3 = {"Julka", 20};

    FILE *plik = fopen("dane.txt","w");
    fprintf(plik,"%s \t %s\n","Imie","Wiek");
    fprintf(plik,"--------------\n");
    fprintf(plik,"%s \t %d\n",osoba1.imie,osoba1.wiek);
    fprintf(plik,"%s \t %d\n",osoba2.imie,osoba2.wiek);
    fprintf(plik,"%s \t %d\n",osoba3.imie,osoba3.wiek);

    fclose(plik);

    plik = fopen("dane.txt","r");
    char linia[100];
    while (fgets(linia,sizeof(linia),plik) != NULL)
    {
        printf("%s",linia);
    }
    
    fclose(plik);
    return 0;
}