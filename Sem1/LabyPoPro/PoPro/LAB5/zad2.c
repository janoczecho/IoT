//Jan Czechowski
#include <stdio.h>

int a = 8;

void info(char *nazwa_bloku, int zmienna) {
    printf("W bloku %s zmienna a = %d\n", nazwa_bloku, zmienna);    //Zwracanie wartosci zmiennej 'a' powiązanej z nazwą bloku
}

void funkcja() {
    info("funkcji", a);
}

int suma(int x, int y) {
    return x + y;
}

void czy_parzysta(const int);

int liczba_zwiekszona(int x) {
    return ++x;
}

void zwieksz_liczbe(int a) {
    ++a;
}

void zwieksz_przez_adres(int* x) {
    (*x)++;
}

int main() {
    int a = 20;

    info("main", a);
    funkcja();

    int b = 9;
    int wynik = suma(a, b);

    printf("\na + b = %d\n\n", wynik);  // Wypisuje: sume 'a' i 'b' przy uzyciu funkcji suma

    czy_parzysta(a);
    czy_parzysta(b);

    printf("\na + 1 = %d\n", liczba_zwiekszona(a));     // Zwiększenie wartości 'a' o 1 przy uzyciu funkcji 'liczba_zwiekszona' i wyświetlenie wyniku
    zwieksz_liczbe(a);  //Próba zwiekszenia lokalnej wartosci 'a' przez funkcje 'zwieksz_liczbe'
    printf("Zmienna 'a' po wywolaniu zwieksz_liczbe = %d\n", a);    //'a' w funkcji main sie nie zmienia, wiec wypisuje "20"

    zwieksz_przez_adres(&a);    //zwiekszenie 'a' przy uzyciu wskaznika, wiec zmienna 'a' w funckji main sie zwieksza
    printf("Zmienna 'a' po zwieksz_przez_adres = %d\n", a);     //wypisuje zwiekszone 'a' rowne 21

    return 0;
}

void czy_parzysta(const int x) {
    if(x % 2 == 0)
        printf("Liczba %d jest parzysta!\n", x);    //sprawdzanie czy liczba jest parzysta poprzez sprawdzanie czy reszta z dzielenia przez 2 jest rowna 0 i wypisywanie komunikatu o parzystosci liczby
    else
        printf("Liczba %d jest nieparzysta!\n", x);     //jesli liczba jest nieparzysta to wypisuje komunikat ze liczba jest nieparzysta
}