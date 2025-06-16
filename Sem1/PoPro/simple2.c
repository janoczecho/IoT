#include <stdio.h>  //wlacza biblioteke standardowa stdio.h
#include <stdlib.h> //wlacza biblioteke standardowa stdlib.h
int main(int argc, char ** argv) {  //definicja funckji glownen programu
        int how_many;   //definiuje zmienna calkowita 'how_many', ta zmienna odpowiada za to jakie elemnty tablicy 'table' beda dodawane do sumy(elemnty o indeksach <= 'how_many')   
        printf("Podaj najwyzszy indeks: \n");   //wypisuje prosbe o podanie najwyzszego indeksu 
        scanf("%d", &how_many); //podanie najwyzszego indeksu
        int table[10];  //definicja tablicy 'table' o rozmiarze 10, ktora przechowuje 10 liczb calkowitych
        table[0]=1; //Przypisuje konkretna wartosc do elementu tablicy 'table' na konretnym indeksie
        table[1]=5; //Przypisuje konkretna wartosc do elementu tablicy 'table' na konretnym indeksie
        table[2]=9; //Przypisuje konkretna wartosc do elementu tablicy 'table' na konretnym indeksie
        table[3]=0; //Przypisuje konkretna wartosc do elementu tablicy 'table' na konretnym indeksie
        table[4]=-30;   //Przypisuje konkretna wartosc do elementu tablicy 'table' na konretnym indeksie
        table[5]=30;    //Przypisuje konkretna wartosc do elementu tablicy 'table' na konretnym indeksie
        table[6]=100;   //Przypisuje konkretna wartosc do elementu tablicy 'table' na konretnym indeksie
        table[7]=20;    //Przypisuje konkretna wartosc do elementu tablicy 'table' na konretnym indeksie
        table[8]=70;    //Przypisuje konkretna wartosc do elementu tablicy 'table' na konretnym indeksie
        table[9]=90;    //Przypisuje konkretna wartosc do elementu tablicy 'table' na konretnym indeksie

        float sum = 0;    //definiuje zmienna zmiennoprzecinkowa, ktora będzie słuzyc do przechowywania sumy wybranych elementów tablicy i jest zainicjowana na 0

        int i=0;    //Deklaruje zmienna petli 'i', ktora bedzie uzywana jako licznik w pętli
        for (i = 0; i <= how_many; i++) {   //Rozpoczyna petle for, która będzie iterować od i = 0 do i = how_many
            sum += table[i];    //W każdej iteracji do zmiennej 'sum' dodawana jest wartosc elementu table[i]
        }
    float average = sum / (how_many + 1);   //oblicza srednia z how_many + 1 pierwszych elemntow tablicy 'table
    printf("Average: %f\n", average);   //Wypisuje wynik sredniej w formacie zmiennoprzecinkowym
}

/*
Odpowiedzi na pytania do zadania 3.4:
1. program da poprawny wynik dla wartosci 'how_many' rownych od 0 do 9
2. w linijce liczacej srednia trzeba do zmiennej 'how_many' dodac 1 oraz zmienic format zmiennej 'average' z liczby calkowitej na liczbe zmiennoprzecinkowa
3. należy poprawic wypisywanie wyniku zamieniajac %d na %f aby program wypisywal liczbe zmiennoprzecinkowa
*/