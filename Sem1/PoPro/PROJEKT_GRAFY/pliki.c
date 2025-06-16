#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "graf.h"

void przetworz_komende(const char* komenda);

// Deklaracja globalnej zmiennej graf z main.c
extern graf G;

// Funkcja sortująca tablicę uint64_t za pomocą sortowania bąbelkowego
void bubble_sort_uint64(uint64_t table[], int size) {
    int i, j;
    uint64_t temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - 1 - i; j++) {
            if (table[j] > table[j + 1]) {
                temp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = temp;
            }
        }
    }
}

// Funkcja sortująca tablicę wskaźników do wierzchołków po polu "etykieta"
void bubble_sort_wierzcholki(wierzcholek** wierzcholki, int size) {
    int i, j;
    wierzcholek* temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - 1 - i; j++) {
            if (wierzcholki[j]->etykieta > wierzcholki[j + 1]->etykieta) {
                temp = wierzcholki[j];
                wierzcholki[j] = wierzcholki[j + 1];
                wierzcholki[j + 1] = temp;
            }
        }
    }
}

// Zapisuje graf do pliku tekstowego - odpowiada funkcji 'Save' w main.c
void zapisz_do_pliku(const char* nazwaPliku) {

    char nazwaPlikuTXT[256];
    if (strstr(nazwaPliku, ".txt") == NULL) {
        snprintf(nazwaPlikuTXT, sizeof(nazwaPlikuTXT), "%s.txt", nazwaPliku);
    } else {
        snprintf(nazwaPlikuTXT, sizeof(nazwaPlikuTXT), "%s", nazwaPliku);
    }

    FILE* plik = fopen(nazwaPlikuTXT, "w");
    if (!plik) {
        printf("Blad: Nie mozna otworzyc pliku o nazwie: %s do zapisu.\n", nazwaPlikuTXT);
        return;
    }

    // Zbieranie wszystkich wierzchołkow do tablicy
    int liczbaWierzcholkow = 0;
    wierzcholek* temp = G.pierwszy;
    while (temp) {
        liczbaWierzcholkow++;
        temp = temp->next;
    }

    wierzcholek** wierzcholki = malloc(liczbaWierzcholkow * sizeof(wierzcholek*));
    if (!wierzcholki) {
        printf("Blad alokacji pamieci dla tablicy wierzcholkow.\n");
        fclose(plik);
        return;
    }

    temp = G.pierwszy;
    for (int i = 0; i < liczbaWierzcholkow; i++) {
        wierzcholki[i] = temp;
        temp = temp->next;
    }

    // Sortowanie wierzchołków po etykietach
    bubble_sort_wierzcholki(wierzcholki, liczbaWierzcholkow);

    // Iterowanie po posortowanej tablicy i zapis do pliku tekstowego
    for (int i = 0; i < liczbaWierzcholkow; i++) {
        wierzcholek* obecny = wierzcholki[i];

        // Zapisujemy etykietę wierzchołka
        fprintf(plik, "%llu:", (unsigned long long)obecny->etykieta);

        // Tworzymy dynamiczną listę sąsiadów
        uint64_t* sasiedzi_tab = NULL;
        int liczbaSasiedzi = 0;
        int pojemnosc = 0;

        // Przechodzimy przez listę sąsiedztwa
        for (int j = 0; j < obecny->ile_sasiad; j++) {
            typ etykieta_sasiedniego = obecny->sasiedzi[j]->etykieta;

            if (liczbaSasiedzi == pojemnosc) {
                // Zwiększamy pojemność o 0.75
                pojemnosc = (pojemnosc == 0) ? 10 : (int)(pojemnosc * 1.75);
                sasiedzi_tab = realloc(sasiedzi_tab, pojemnosc * sizeof(uint64_t));
                if (!sasiedzi_tab) {
                    printf("Blad alokacji pamieci dla listy sąsiedztwa.\n");
                    fclose(plik);
                    free(wierzcholki);
                    return;
                }
            }
            // Dodajemy etykietę sąsiada do listy
            sasiedzi_tab[liczbaSasiedzi++] = etykieta_sasiedniego;
        }

        // Sortowanie etykiet sąsiednich wierzchołków
        if (liczbaSasiedzi > 0) {
            bubble_sort_uint64(sasiedzi_tab, liczbaSasiedzi);
        }

        // Zapisujemy już posortowane etykiety sąsiadów do pliku tekstowego
        for (int j = 0; j < liczbaSasiedzi; j++) {
            fprintf(plik, " %llu", (unsigned long long)sasiedzi_tab[j]);
            if (j < liczbaSasiedzi - 1) fprintf(plik, ",");
        }

        fprintf(plik, "\n");
        free(sasiedzi_tab);
    }

    free(wierzcholki);
    fclose(plik);
    printf("Graf zostal zapisany do pliku o nazwie: %s.\n", nazwaPlikuTXT);
}

// Zapisuje graf w formacie binarnym - odpowiada funkcji 'DUMP' w main.c
void zapisz_etykiety(const char* nazwaPliku) {

    char nazwaPlikuBIN[256];
    if (strstr(nazwaPliku, ".bin") == NULL) {
        snprintf(nazwaPlikuBIN, sizeof(nazwaPlikuBIN), "%s.bin", nazwaPliku);
    } else {
        snprintf(nazwaPlikuBIN, sizeof(nazwaPlikuBIN), "%s", nazwaPliku);
    }

    FILE* plik = fopen(nazwaPlikuBIN, "wb");
    if (!plik) {
        printf("Blad: Nie mozna otworzyc pliku o nazwie: %s do zapisu.\n", nazwaPlikuBIN);
        return;
    }

    // Zliczamnie wierzchołków
    int liczbaWierzcholkow = 0;
    wierzcholek* obecny = G.pierwszy;
    while (obecny) {
        liczbaWierzcholkow++;
        obecny = obecny->next;
    }

    // Jeśli nie ma wierzchołków to kończymy
    if (liczbaWierzcholkow == 0) {
        fclose(plik);
        printf("Graf zapisany w formacie binarnym do pliku o nazwie: %s (pusty graf).\n", nazwaPlikuBIN);
        return;
    }

    // Alokacja dynamicznej tablicy etykiet
    uint64_t* tabEtykiet = malloc(liczbaWierzcholkow * sizeof(uint64_t));
    if (!tabEtykiet) {
        printf("Blad alokacji pamieci przy zapisie etykiet.\n");
        fclose(plik);
        return;
    }

    // Kopiowanie etykiet wierzchołków do tablicy
    obecny = G.pierwszy;
    for (int i = 0; i < liczbaWierzcholkow; i++) {
        tabEtykiet[i] = obecny->etykieta;
        obecny = obecny->next;
    }

    // Sortowanie tablicy etykiet (rosnąco)
    bubble_sort_uint64(tabEtykiet, liczbaWierzcholkow);

    // Zapis do pliku binarnego
    fwrite(tabEtykiet, sizeof(uint64_t), liczbaWierzcholkow, plik);

    free(tabEtykiet);
    fclose(plik);

    printf("Graf zapisany w formacie binarnym do pliku o nazwie: %s.\n", nazwaPlikuBIN);
}

// Wypisuje etykiety wierzchołków grafu - odpowiada funkcji 'PRINT' w main.c
void wypisz_etykiety() {
    // Najpierw zliczamy wierzchołki
    int liczbaWierzcholkow = 0;
    wierzcholek* obecny = G.pierwszy;
    while (obecny) {
        liczbaWierzcholkow++;
        obecny = obecny->next;
    }

    if (liczbaWierzcholkow == 0) {
        // brak wierzchołków do wypisania
        return;
    }

    // Alokacja tablicy do przechowania etykiet
    uint64_t* tabEtykiet = malloc(liczbaWierzcholkow * sizeof(uint64_t));
    if (!tabEtykiet) {
        printf("Blad alokacji pamieci przy wypisywaniu etykiet.\n");
        return;
    }

    // Ponownie ustawiamy wskaźnik i kopiujemy etykiety
    obecny = G.pierwszy;
    for (int i = 0; i < liczbaWierzcholkow; i++) {
        tabEtykiet[i] = obecny->etykieta;
        obecny = obecny->next;
    }

    // Sortujemy etykiety rosnąco
    bubble_sort_uint64(tabEtykiet, liczbaWierzcholkow);

    // Wypisujemy posortowane etykiety
    for (int i = 0; i < liczbaWierzcholkow; i++) {
        printf("%llu\n", (unsigned long long)tabEtykiet[i]);
    }

    free(tabEtykiet);
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
        // Usuwa znak nowej linii z końca komendy
        komenda[strcspn(komenda, "\n")] = '\0';
        // Wywołuje funkcję przetwarzającą komendę
        przetworz_komende(komenda);
    }

    fclose(plik);
}
