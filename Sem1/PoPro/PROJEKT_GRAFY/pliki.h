#ifndef PLIKI_H
#define PLIKI_H

#include "graf.h"

// Deklaracja funkcji do operacji na plikach
void zapisz_do_pliku(const char* nazwaPliku);
void zapisz_etykiety(const char* nazwaPliku);
void wypisz_etykiety();
void uruchom_skrypt(const char* nazwaPliku);

#endif // PLIKI_H