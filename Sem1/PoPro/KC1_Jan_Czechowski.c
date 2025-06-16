//Jan Czechowski 337066

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int wiersze = 4; //deklaracja i definiowanie stalej odpowiadajacej za ilosc wierszy
const int kolumny = 3; //deklaracja i definiowanie stalej odpowiadajacej za ilosc kolumn

int laczenie(char tablica1[wiersze][kolumny], char tablica2[wiersze][kolumny], char PolaczonaTablica[wiersze*2][kolumny*2])
{
    for (int i = 0; i < wiersze; i++)
    {
        for (int j = 0; j < kolumny; j++)
        {
            PolaczonaTablica[i][j] = tablica1[i][j]; //uzupenianie nowej tablicy elementami tablicy 1
        } 
    }
    for (int i = 0; i < wiersze; i++)
    {
        for (int j = 0; j < kolumny; j++)
        {
            PolaczonaTablica[i+wiersze][j+kolumny] = tablica2[i][j];  //uzupenianie nowej tablicy elementami tablicy 2
        } 
    }
    if (sizeof(*PolaczonaTablica) == sizeof(*tablica1)+sizeof(*tablica2)) // sprawdzanie czy git
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

void wyswietlanie(char PolaczonaTablica[wiersze*2][kolumny*2]){
    for (int i = 0; i < wiersze*2; i++)
    {
        for (int j = 0; j < kolumny*2; j++)
        {
            printf("%c\t", PolaczonaTablica[i][j]); // wyswietlanbie po kolei elementow
        }
        puts("\n");
    }
}

int main(void){
    srand(time(NULL));
    char tab1[wiersze][kolumny]; //deklaracja i definiowanie tablicy pierwszej
    char tab2[wiersze][kolumny]; //deklaracja i definiowanie tablicy drugiej
    char nowaTablica[wiersze*2][kolumny*2]; //deklaracja i definiowanie nowej tablicy
    for (int i = 0; i < wiersze; i++)
    {
        for (int j = 0; j < kolumny; j++)
        {
            tab1[i][j] = rand() % 26 + 'A'; //uzupelnianie losowo literami tablicy 1
            tab2[i][j] = rand() % 26 + 'A'; //uzupelnianie losowo literami tablicy 2
        }
    }
    laczenie(tab1,tab2,nowaTablica); //wywolanie funkcji laczacej
    wyswietlanie(nowaTablica); //wywolanie funkcji wyswietlajacej
    
return 0;

}