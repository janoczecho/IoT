#include <stdio.h>
#include <string.h>
#include <stdlib.h> // do zamiany napisów na liczby
#include "graf.h"
//#include "pliki.h"
#include <ctype.h>

graf G = { NULL, 0 };


void przetworz_komende(const char* komenda);


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
typ zamiana_stringa_na_uint64(const char *str);
int podziel_polecenie(char *wpisane_dane, input *wczytanyInput);
char *trim(char *str);

int main() {
    Interfejs();
    return 0;
}
char *trim(char *str) {
    char *end;
    // Usuń białe znaki z początku
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  // Cały string to białe znaki
        return str;

    // Usuń białe znaki z końca
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Dodaj znak null na końcu
    end[1] = '\0';

    return str;
}



// Funkcja do dzielenia polecenia na części
//przechodzimy znak po znaku przez dane wprowadzone przez użytkownika
//arg_lcz - licznik informujący czy przechodzimy przez polecenie, arg1 czy arg2
int podziel_polecenie(char *wpisane_dane, input *wczytanyInput) {    
    wczytanyInput->polecenie[0] = '\0';
    wczytanyInput->arg1[0] = '\0';
    wczytanyInput->arg2[0] = '\0';
    wczytanyInput->arg_liczba = 0;
    char temp_arg[2 * 20 + 2]; // Bufor pomocniczy na argumenty A i R
    char *token;

    char *trimmed_data = trim(wpisane_dane); // Usuwamy spacje 

    
    char *space_ptr = strchr(trimmed_data, ' ');
    int command_len;

    if (space_ptr != NULL) {
        command_len = space_ptr - trimmed_data;
    } else {
        command_len = strlen(trimmed_data);
    }

    if (command_len >= 10) {
        printf("Błąd: Za długie polecenie.\n");
        return 1; // Błąd: Za długie polecenie
    }
    strncpy(wczytanyInput->polecenie, trimmed_data, command_len);
    wczytanyInput->polecenie[command_len] = '\0';
    trim(wczytanyInput->polecenie);

    // Krok 2: Parsowanie argumentów w zależności od komendy
    if (strcmp(wczytanyInput->polecenie, "Exit") == 0 || strcmp(wczytanyInput->polecenie, "Print") == 0) {
        // Komendy bez argumentów
        char *rest = trimmed_data + command_len;
        if (rest != NULL && strlen(trim(rest)) > 0) {
            printf("Błąd: Komenda '%s' nie przyjmuje argumentów.\n", wczytanyInput->polecenie);
            return 1; // Błąd: Komenda nie przyjmuje argumentów
        }
        wczytanyInput->arg_liczba = 0;
    } else if (strcmp(wczytanyInput->polecenie, "Save") == 0 || strcmp(wczytanyInput->polecenie, "Dump") == 0 || strcmp(wczytanyInput->polecenie, "Run") == 0) {
        char *rest_with_spaces = trimmed_data + command_len;
        char *rest = trim(rest_with_spaces);
        if (strlen(rest) > 0) {
            char *space_after_arg = strchr(rest, ' ');
            if (space_after_arg == NULL) {
                strncpy(wczytanyInput->arg1, rest, 19);
                wczytanyInput->arg1[19] = '\0';
                wczytanyInput->arg_liczba = 1;
            } else {
                printf("Błąd: Za dużo argumentów dla komendy '%s'.\n", wczytanyInput->polecenie);
                return 1; // Błąd: Za dużo argumentów
            }
        } else {
            printf("Błąd: Brak argumentu dla komendy '%s'.\n", wczytanyInput->polecenie);
            return 1; // Błąd: Brak argumentu
        }
    } else if (strncmp(wczytanyInput->polecenie, "A:", 2) == 0 || strncmp(wczytanyInput->polecenie, "R:", 2) == 0) {
        char *args_start = strchr(trimmed_data, ':');
        if (args_start != NULL) {
            args_start++; // Przesuń za dwukropek
            strcpy(temp_arg, trim(args_start));
            token = strtok(temp_arg, ",");
            if (token != NULL) {
                strncpy(wczytanyInput->arg1, trim(token), 19);
                wczytanyInput->arg1[19] = '\0';
                wczytanyInput->arg_liczba++;

                token = strtok(NULL, ",");
                if (token != NULL) {
                    strncpy(wczytanyInput->arg2, trim(token), 19);
                    wczytanyInput->arg2[19] = '\0';
                    wczytanyInput->arg_liczba++;
                    if (strtok(NULL, ",") != NULL) {
                        printf("Błąd: Za dużo argumentów dla komendy '%s'.\n", wczytanyInput->polecenie);
                        return 1; // Błąd: Za dużo argumentów
                    }
                }
            } else {
                printf("Błąd: Brak argumentów dla komendy '%s'.\n", wczytanyInput->polecenie);
                return 1; // Błąd: Brak argumentów
            }
        } else {
            printf("Błąd: Nieprawidłowy format komendy '%s'.\n", wczytanyInput->polecenie);
            return 1; // Błąd: Nieprawidłowy format komendy
        }
    } else if (strlen(wczytanyInput->polecenie) > 0) {
        printf("Inny błąd\n");
        return 1; // Błąd: Nieznana komenda
    } else {
        printf("Błąd: Puste polecenie.\n");
        return 1; // Błąd: Puste polecenie
    }

    return 0; // Sukces
}

// Funkcja do zamiany string na uint64
typ zamiana_stringa_na_uint64(const char *str) {
    char *endptr;
    typ result = strtoull(str, &endptr, 10);
    if (*endptr != '\0') {
        return 0; 
    }
    return result;
}

// Funkcja interfejsu
void Interfejs() {
    char wpisane_dane[100];
    input podzielone_polecenie;
    typ etykieta1, etykieta2;
    

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

        if (podziel_polecenie(wpisane_dane, &podzielone_polecenie) != 0) {
            printf("Błąd w poleceniu.\n");
            continue; // Przejdź do następnej iteracji
        }

        // Konwersja argumentów na liczby tylko dla A: i R:
        etykieta1 = 0;
        etykieta2 = 0;

        if (strncmp(podzielone_polecenie.polecenie, "A:", 2) == 0 || strncmp(podzielone_polecenie.polecenie, "R:", 2) == 0) {
            if (podzielone_polecenie.arg_liczba >= 1) {
                etykieta1 = zamiana_stringa_na_uint64(podzielone_polecenie.arg1);
                if (etykieta1 == 0 && strcmp(podzielone_polecenie.arg1, "0") != 0) {
                    printf("Błąd: Nieprawidłowy format etykiety '%s'.\n", podzielone_polecenie.arg1);
                    continue;
                }
            }
            if (podzielone_polecenie.arg_liczba == 2) {
                etykieta2 = zamiana_stringa_na_uint64(podzielone_polecenie.arg2);
                if (etykieta2 == 0 && strcmp(podzielone_polecenie.arg2, "0") != 0) {
                    printf("Błąd: Nieprawidłowy format etykiety '%s'.\n", podzielone_polecenie.arg2);
                    continue;
                }
            }
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
                dodaj_wierzhcolek(&G,etykieta1);
            } else if (podzielone_polecenie.arg_liczba == 2) {
                dodaj_krawedz(&G, etykieta1, etykieta2);
            }
            else{
                printf("Błąd wewnętrzny - nieobsłużona liczba argumentów dla A:\n");
            }
        } else if (strncmp(podzielone_polecenie.polecenie, "R:", 2) == 0) {
            if (podzielone_polecenie.arg_liczba == 1) {
                usun_wierzcholek(&G, etykieta1);
            } else if (podzielone_polecenie.arg_liczba == 2) {
                usun_krawedz(&G, etykieta1, etykieta2);
            } else{
                printf("Błąd wewnętrzny - nieobsłużona liczba argumentów dla R:\n");
            }
        }
        else {
            printf("Inny błąd\n");
        }
    }
}

void przetworz_komende(const char* komenda) {
    input parsowane_polecenie;
    char komenda_copy[256];
    
    
    strncpy(komenda_copy, komenda, sizeof(komenda_copy) - 1);
    komenda_copy[sizeof(komenda_copy) - 1] = '\0';

    
    if (podziel_polecenie(komenda_copy, &parsowane_polecenie) != 0) {
        printf("Błąd w poleceniu: %s\n", komenda);
        return;
    }

    typ etykieta1 = 0, etykieta2 = 0;

    
    if (strncmp(parsowane_polecenie.polecenie, "A:", 2) == 0 || strncmp(parsowane_polecenie.polecenie, "R:", 2) == 0) {
        if (parsowane_polecenie.arg_liczba >= 1) {
            etykieta1 = zamiana_stringa_na_uint64(parsowane_polecenie.arg1);
            if (etykieta1 == 0 && strcmp(parsowane_polecenie.arg1, "0") != 0) {
                printf("Błąd: Nieprawidłowy format etykiety '%s'.\n", parsowane_polecenie.arg1);
                return;
            }
        }
        if (parsowane_polecenie.arg_liczba == 2) {
            etykieta2 = zamiana_stringa_na_uint64(parsowane_polecenie.arg2);
            if (etykieta2 == 0 && strcmp(parsowane_polecenie.arg2, "0") != 0) {
                printf("Błąd: Nieprawidłowy format etykiety '%s'.\n", parsowane_polecenie.arg2);
                return;
            }
        }
    }

    // Obsługa komend
    if (strcmp(parsowane_polecenie.polecenie, "Exit") == 0) {
        printf("Zamykanie programu.\n");
        exit(0);
    }
    else if (strcmp(parsowane_polecenie.polecenie, "Print") == 0) {
        wypisz_etykiety();
    }
    else if (strcmp(parsowane_polecenie.polecenie, "Save") == 0) {
        zapisz_do_pliku(parsowane_polecenie.arg1);
    }
    else if (strcmp(parsowane_polecenie.polecenie, "Dump") == 0) {
        zapisz_etykiety(parsowane_polecenie.arg1);
    }
    else if (strcmp(parsowane_polecenie.polecenie, "Run") == 0) {
        uruchom_skrypt(parsowane_polecenie.arg1);
    }
    else if (strncmp(parsowane_polecenie.polecenie, "A:", 2) == 0) {
        if (parsowane_polecenie.arg_liczba == 1) {
            dodaj_wierzhcolek(&G, etykieta1); // Poprawiona nazwa funkcji
        }
        else if (parsowane_polecenie.arg_liczba == 2) {
            dodaj_krawedz(&G, etykieta1, etykieta2);
        }
        else {
            printf("Błąd: Nieobsłużona liczba argumentów dla komendy A:\n");
        }
    }
    else if (strncmp(parsowane_polecenie.polecenie, "R:", 2) == 0) {
        if (parsowane_polecenie.arg_liczba == 1) {
            usun_wierzcholek(&G, etykieta1);
        }
        else if (parsowane_polecenie.arg_liczba == 2) {
            usun_krawedz(&G, etykieta1, etykieta2);
        }
        else {
            printf("Błąd: Nieobsłużona liczba argumentów dla komendy R:\n");
        }
    }
    else {
        printf("Nieznane polecenie: %s\n", parsowane_polecenie.polecenie);
    }
}
