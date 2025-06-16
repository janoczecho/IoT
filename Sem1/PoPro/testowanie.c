#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Inicjalizacja generatora liczb losowych
    srand(time(NULL));

    // Losowanie liczby z zakresu 0-22
    int liczba = rand() % 23;

    // Wyświetlenie wyniku
    printf("Wylosowana liczba: %d\n", liczba);

    return 0;
}
