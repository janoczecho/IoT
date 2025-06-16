#include <stdio.h>
#include <string.h>
#include <stdint.h> //to jest do uint64_t
#include <stdlib.h> // do zamiany napisów na uint64
//#include "graf.h"
#include "pliki.h"



// Struktura do przechowywania polecenia i argumentów
//arg1,arg2 - kolejne argumenty, arg_liczba - liczba argumentów - ułatwia obługiwanie A: i R: 
//polecenie to np. Save, Print, Dump, A, R
typedef struct {
    char polecenie[10];
    char arg1[20];
    char arg2[20];
    int arg_liczba;
} input;

void Interfejs();
uint64_t zamiana_stringa_na_uint64(const char *str);
input podziel_polecenie(char *wpisane_dane);


int main() {
    Interfejs();
    return 0;
}


// Funkcja do dzielenia polecenia na części
//przechodzimy znak po znaku przez dane wprowadzone przez użytkownika
//arg_lcz - licznik informujący czy przechodzimy przez polecenie, arg1 czy arg2
input podziel_polecenie(char *wpisane_dane) {
    input wczytanyInput = {"", "", "", 0};
    int i = 0;
    int j = 0;
    int arg_lcz = 0;

    // Pomijamy spacje
    while (wpisane_dane[i] == ' ') {
        i++;
    }
    if (strncmp(&wpisane_dane[i], "A:", 2) == 0 || strncmp(&wpisane_dane[i], "R:", 2) == 0) {
        wczytanyInput.polecenie[0] = wpisane_dane[i];
        wczytanyInput.polecenie[1] = wpisane_dane[i+1];
        wczytanyInput.polecenie[2] = '\0';
        i+=2; 
    }else {
        while (wpisane_dane[i] != '\0' && wpisane_dane[i] != ' ' && j < 9) {
        wczytanyInput.polecenie[j] = wpisane_dane[i];
        i++;
        j++;
    }
    wczytanyInput.polecenie[j] = '\0';
    }
    
    j = 0;
    arg_lcz = 1;


    // Pomijamy spacje
    while (wpisane_dane[i] == ' ') {
        i++;
    }
    
    // Wczytujemy arg1
    while (wpisane_dane[i] != '\0' && wpisane_dane[i] != ',' && wpisane_dane[i] != ' ' && j < 19 && arg_lcz == 1)
    {
         wczytanyInput.arg1[j] = wpisane_dane[i];
        i++;
        j++;
    }
    //dodajemy '\0' na końcu napisów
     wczytanyInput.arg1[j] = '\0';
     j = 0;

   
     // Pomijamy spacje i przecinek
    while (wpisane_dane[i] == ' ' || wpisane_dane[i] == ',') {
         i++;
    }
    if (wpisane_dane[i] != '\0') {
         arg_lcz = 2;
    }
  

     // Wczytujemy arg2
    while (wpisane_dane[i] != '\0'  && j < 19 && arg_lcz == 2) {
        wczytanyInput.arg2[j] = wpisane_dane[i];
        i++;
        j++;
    }
     wczytanyInput.arg2[j] = '\0';
  
     // Zliczamy liczbę argumentów
      if (strlen(wczytanyInput.arg1) > 0)
        wczytanyInput.arg_liczba++;
      if (strlen(wczytanyInput.arg2) > 0)
        wczytanyInput.arg_liczba++;

    return wczytanyInput;
}

// Funkcja do zamiany string na uint64
uint64_t zamiana_stringa_na_uint64(const char *str) {
    char *endptr;
    uint64_t result = strtoull(str, &endptr, 10);
    if (*endptr != '\0') {
        return 0; 
    }
    return result;
}

// Funkcja interfejsu
void Interfejs() {
    char wpisane_dane[100];
    input podzielone_polecenie;
    uint64_t etykieta1, etykieta2;
    

    while (1) {
        printf("Wpisz polecenie: ");
        if (fgets(wpisane_dane, sizeof(wpisane_dane), stdin) == NULL) {
            printf("Błąd przy wczytywaniu\n");
            break; 
        }

        
        int len = 0;
        while (wpisane_dane[len] != '\0' && wpisane_dane[len] != '\n'){
            len++;
        }
        wpisane_dane[len] = '\0';

        if (wpisane_dane[0] == '\0') {
            continue;
        }

        podzielone_polecenie = podziel_polecenie(wpisane_dane);
        
        // Konwersja argumentów na liczby
        etykieta1 = 0;
         if (podzielone_polecenie.arg_liczba > 0) {
            etykieta1 = zamiana_stringa_na_uint64(podzielone_polecenie.arg1);
        }
        etykieta2 = 0;
         if (podzielone_polecenie.arg_liczba > 1) {
            etykieta2 = zamiana_stringa_na_uint64(podzielone_polecenie.arg2);
        }
      

        //porównujemy napisy przy użyciu strcmp, dla A: i R: rozróżniamy przypadki w zależności
        //od liczby argumentów
        if (strcmp(podzielone_polecenie.polecenie, "Exit") == 0) {
            break;
        } else if (strcmp(podzielone_polecenie.polecenie, "Save") == 0) {
            zapisz_do_pliku(podzielone_polecenie.arg1);
        } else if (strcmp(podzielone_polecenie.polecenie, "Run") == 0) {
            uruchom_skrypt(podzielone_polecenie.arg1);
        } else if (strcmp(podzielone_polecenie.polecenie, "Print") == 0) {
            wypisz_etykiety();
        } else if (strcmp(podzielone_polecenie.polecenie, "Dump") == 0) {
            zapisz_etykiety(podzielone_polecenie.arg1);
        }else if (strncmp(podzielone_polecenie.polecenie, "A:", 2) == 0) {
            if (podzielone_polecenie.arg_liczba == 1) {
                dodaj_wierzcholek(etykieta1);
            } else if (podzielone_polecenie.arg_liczba == 2) {
                dodaj_krawedz(etykieta1, etykieta2);
            }
             else{
                 printf("Błędna komenda lub liczba argumentow\n");
             }
        } else if (strncmp(podzielone_polecenie.polecenie, "R:", 2) == 0) {
             if (podzielone_polecenie.arg_liczba == 1) {
                usun_wierzcholek(etykieta1);
            } else if (podzielone_polecenie.arg_liczba == 2) {
                usun_krawedz(etykieta1, etykieta2);
            } else{
                 printf("Błędna komenda lub liczba argumentow\n");
             }
        }
        else {
            printf("Inny błąd\n");
        }
    }
}


