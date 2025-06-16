// Lab. 9, zadanie 1
//
// Kinga Konieczna i Jan Czechowski
// 337072 i 337066
// 09.12.2024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data_base_entry {
    int id;
    char name[64];
    double salary;
    char *periodic_assessment;
};

void zapisz_baze_do_pliku(const char *nazwa_pliku, struct data_base_entry *baza, int liczba_rekordow) {
    FILE *plik = fopen(nazwa_pliku, "w");
    if (plik == NULL) {
        printf("Error! Nie mozna otworzyc pliku do zapisu.\n");
        exit(1);
    }

    for (int i = 0; i < liczba_rekordow; i++) {
        fprintf(plik, "ID: %d\n", baza[i].id);
        fprintf(plik, "Imie i nazwisko: %s\n", baza[i].name);
        fprintf(plik, "Wynagrodzenie: %.2lf\n", baza[i].salary);
        fprintf(plik, "Ocena okresowa: %s\n", baza[i].periodic_assessment);
        fprintf(plik, "---------------------------------\n");
    }

    fclose(plik);
}

void zwolnij_pamiec(struct data_base_entry *baza, int liczba_rekordow) {
    for (int i = 0; i < liczba_rekordow; i++) {
        free(baza[i].periodic_assessment);
    }
}

int main() {
    int liczba_rekordow = 3;
    struct data_base_entry baza[3];

    baza[0].id = 1;
    strcpy(baza[0].name, "Tadeusz Barcinski");
    baza[0].salary = 4500.50;
    baza[0].periodic_assessment = malloc(strlen("Bardzo dobry pracownik, zaangazowany w projekty.") + 1);
    if (baza[0].periodic_assessment != NULL) {
        strcpy(baza[0].periodic_assessment, "Bardzo dobry pracownik, zaangazowany w projekty.");
    }

    baza[1].id = 2;
    strcpy(baza[1].name, "Jacek Chmielewski");
    baza[1].salary = 5200.75;
    baza[1].periodic_assessment = malloc(strlen("Doskonałe umiejetnosci komunikacyjne, zawsze na czas.") + 1);
    if (baza[1].periodic_assessment != NULL) {
        strcpy(baza[1].periodic_assessment, "Doskonałe umiejetnosci komunikacyjne, zawsze na czas.");
    }

    baza[2].id = 3;
    strcpy(baza[2].name, "Marek Zygmunciak");
    baza[2].salary = 8420.00;
    baza[2].periodic_assessment = malloc(strlen("Potrzebuje poprawy w zakresie punktualnosci.") + 1);
    if (baza[2].periodic_assessment != NULL) {
        strcpy(baza[2].periodic_assessment, "Potrzebuje poprawy w zakresie punktualnosci.");
    }

    zapisz_baze_do_pliku("baza_danych.txt", baza, liczba_rekordow);

    printf("Baza danych zostala zapisana w pliku 'baza_danych.txt'.\n");

    zwolnij_pamiec(baza, liczba_rekordow);

    return 0;
}
