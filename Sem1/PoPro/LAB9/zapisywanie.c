// Lab. 9, zadanie 1
//
// Kinga Konieczna i Jan Czechowski
// 337072 i 337066
// 09.12.2024

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

bool porownajTablice(double *a, double *b, int size) {
    for (int i = 0; i < size; i++) {
        if (fabs(a[i] - b[i]) > 0.0000000001) {
            return false;
        }
    }
    return true;
}

int main() {
    const int SIZE = 100;
    double s[SIZE], s_txt[SIZE], s_bin[SIZE];
    FILE *file;

    if ((file = fopen("sqrt.txt", "w")) == NULL) {
        fprintf(stderr, "Blad! Nie mozna otworzyc pliku tekstowego do zapisu.\n");
        exit(1);
    }
    for (int i = 0; i < SIZE; i++) {
        s[i] = sqrt(i + 1);
        if (fprintf(file, "%.10f\n", s[i]) < 0) {
            fprintf(stderr, "Blad podczas zapisu do pliku tekstowego.\n");
            fclose(file);
            exit(1);
        }
    }
    fclose(file);

    if ((file = fopen("sqrt.bin", "wb")) == NULL) {
        fprintf(stderr, "Blad! Nie mozna otworzyc pliku binarnego do zapisu.\n");
        exit(1);
    }
    if (fwrite(s, sizeof(double), SIZE, file) != SIZE) {
        fprintf(stderr, "Blad podczas zapisu do pliku binarnego.\n");
        fclose(file);
        exit(1);
    }
    fclose(file);

    if ((file = fopen("sqrt.txt", "r")) == NULL) {
        fprintf(stderr, "Blad! Nie mozna otworzyc pliku tekstowego do odczytu.\n");
        exit(1);
    }
    for (int i = 0; i < SIZE; i++) {
        if (fscanf(file, "%lf", &s_txt[i]) != 1) {
            fprintf(stderr, "Blad odczytu danych z pliku tekstowego.\n");
            fclose(file);
            exit(1);
        }
    }
    fclose(file);

    if ((file = fopen("sqrt.bin", "rb")) == NULL) {
        fprintf(stderr, "Blad! Nie mozna otworzyc pliku binarnego do odczytu.\n");
        exit(1);
    }
    if (fread(s_bin, sizeof(double), SIZE, file) != SIZE) {
        fprintf(stderr, "Blad odczytu danych z pliku binarnego.\n");
        fclose(file);
        exit(1);
    }
    fclose(file);

    if (porownajTablice(s, s_txt, SIZE)) {
        printf("Tablice s i s_txt sa identyczne.\n");
    } else {
        printf("Tablice s i s_txt roznia sie.\n");
    }

    if (porownajTablice(s, s_bin, SIZE)) {
        printf("Tablice s i s_bin sa identyczne.\n");
    } else {
        printf("Tablice s i s_bin roznia sie.\n");
    }

    return 0;
}

/*
    Wyjaśnienie różnic:
    1. Plik tekstowy ("sqrt.txt") przechowuje liczby w postaci ciągów znaków z ograniczoną dokładnością 
    (%.10f). Odczytane wartości mogą minimalnie różnić się od wartości w oryginalnej tablicy "s".
    2. Plik binarny ("sqrt.bin") przechowuje liczby w postaci binarnej zgodnej z reprezentacją w pamięci 
    (typ "double"). Dzięki temu odczytane wartości są identyczne z oryginalnymi.
    3. Porównanie tablic wykorzystuje tolerancję (0.000001), aby uwzględnić drobne błędy numeryczne 
    wynikające z konwersji liczby do tekstu i z powrotem.

    Wielkości plików:
    - Plik tekstowy jest większy, ponieważ każda liczba zajmuje więcej miejsca w postaci tekstowej.
    - Plik binarny jest mniejszy, bo każda liczba "double" zajmuje stałe 8 bajtów.

    Wnioski:
    - Plik tekstowy jest łatwiejszy do odczytu przez człowieka, ale powoduje utratę precyzji.
    - Plik binarny zachowuje precyzję, ale jest mniej czytelny dla człowieka.
*/