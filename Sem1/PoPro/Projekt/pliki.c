#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "pliki.h"
// #include "graf.h"

// Deklaracja globalnego wskaźnika na graf
extern Wierzcholek* graf;

// Deklaracja funkcji przetwarzającej komendy w main.c
extern void przetworz_komende(const char* komenda);

// Funkcja sortująca tablicę uint64_t za pomocą sortowania bąbelkowego
void bubble_sort_uint64(uint64_t table[], int size)
{
    int i, j;
    uint64_t temp;
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - 1 - i; j++)
        {
            if (table[j] > table[j + 1])
            {
                // Zamiana miejscami
                temp = table[j + 1];
                table[j + 1] = table[j];
                table[j] = temp;
            }
        }
    }
}

// Zapisuje graf do pliku tekstowego - odpowiada funkcji 'SAVE' w main.c
void zapisz_do_pliku(const char* nazwaPliku) {
    FILE* plik = fopen(nazwaPliku, "w");
    if (!plik) {
        printf("Blad: Nie mozna otworzyc pliku o nazwie: %s do zapisu.\n", nazwaPliku);
        return;
    }

    Wierzcholek* obecny = graf;
    while (obecny) {
        // Zapisujemy etykietę wierzchołka
        fprintf(plik, "%llu:", (unsigned long long)obecny->etykieta);

        // Tworzymy dynamiczną listę sąsiadów
        uint64_t* sasiedzi = NULL;
        int liczbaSasiedzi = 0;
        int pojemnosc = 0;

        // Przechodzimy przez listę sąsiedztwa
        Wezel* sasiedztwo = obecny->listaSasiedztwa;
        while (sasiedztwo) {
            // Sprawdzamy, czy trzeba zwiększyć pojemność tablicy
            if (liczbaSasiedzi == pojemnosc) {
                pojemnosc = (pojemnosc == 0) ? 10 : pojemnosc * 1.75; // Zwiększ pojemność o 0,75
                sasiedzi = realloc(sasiedzi, pojemnosc * sizeof(uint64_t));
                if (!sasiedzi) {
                    printf("Blad alokacji pamieci dla listy sąsiedztwa.\n");
                    fclose(plik);
                    return;
                }
            }

            // Dodajemy etykietę sąsiada do listy
            sasiedzi[liczbaSasiedzi++] = sasiedztwo->etykieta;
            sasiedztwo = sasiedztwo->nastepny;
        }

        // Sortowanie etykiet sąsiednich wierzchołków
        if (liczbaSasiedzi > 0) {
            bubble_sort_uint64(sasiedzi, liczbaSasiedzi);
        }
        // Zapisujemy już posortowane etykiety sąsiadów do pliku tekstowego
        for (int i = 0; i < liczbaSasiedzi; i++) {
            fprintf(plik, " %llu", (unsigned long long)sasiedzi[i]);
            if (i < liczbaSasiedzi - 1) fprintf(plik, ",");
        }

        fprintf(plik, "\n");

        // Zwalniamy dynamiczną pamięć dla sąsiadów
        free(sasiedzi);
        obecny = obecny->nastepny;
    }

    fclose(plik);
    printf("Graf zostal zapisany do pliku o nazwie: %s.\n", nazwaPliku);
}

// Zapisuje graf w formacie binarnym - odpowiada funkcji 'DUMP' w main.c
void zapisz_etykiety(const char* nazwaPliku) {
    FILE* plik = fopen(nazwaPliku, "wb");
    if (!plik) {
        printf("Blad: Nie mozna otworzyc pliku o nazwie: %s do zapisu.\n", nazwaPliku);
        return;
    }

    Wierzcholek* obecny = graf;
    while (obecny) {
        // Używamy fwrite do zapisu uint64_t bez formatowania
        fwrite(&obecny->etykieta, sizeof(uint64_t), 1, plik);
        obecny = obecny->nastepny;
    }

    fclose(plik);
    printf("Graf zapisany w formacie binarnym do pliku o nazwie: %s.\n", nazwaPliku);
}

// Wypisuje etykiety wierzchołków grafu - odpowiada funkcji 'PRINT' w main.c
void wypisz_etykiety() {
    Wierzcholek* obecny = graf;
    while (obecny) {
        printf("%llu\n", (unsigned long long)obecny->etykieta);
        obecny = obecny->nastepny;
    }
}

// Uruchamia polecenia z pliku skryptu - odpowiada funkcji 'Run' w main.c
void uruchom_skrypt(const char* nazwaPliku) {
    FILE* plik = fopen(nazwaPliku, "r");
    if (!plik) {
        printf("Blad: Nie mozna otworzyc pliku o nazwie: %s.\n", nazwaPliku);
        return;
    }

    char komenda[256];
    while (fgets(komenda, sizeof(komenda), plik)) {
        // Przekazujemy komendę do funkcji przetwarzającej w main.c
        przetworz_komende(komenda);
    }

    fclose(plik);
}
