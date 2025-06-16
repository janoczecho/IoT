#ifndef GRAF_H
#define GRAF_H

typedef unsigned long long int typ;
typedef struct wierzcholek wierzcholek;
typedef struct graf {
    wierzcholek* pierwszy;    // Wskaźnik do listy wierzchołków
    int ile_wierzcholkow;     // Liczba wierzchołków w grafie
} graf;
struct wierzcholek {
    typ etykieta; //etykieta wierzcholka
    struct wierzcholek* next; //wskaznik do następnego wierzcholka w liscie (dla listy sasiedztwa)
    struct wierzcholek** sasiedzi; //lista wskaznikow do sasiadujacych wierzcholkow
    int ile_sasiad; //liczba sasiadow (rozmiar listy sasiedztwa)
};

// Deklaracja funkcji do operacji na plikach
void dodaj_wierzhcolek(graf* g, typ etykieta); //et=etykieta
void usun_wierzcholek(graf* g, typ etykieta);
void dodaj_krawedz(graf* g, typ etykieta1, typ etykieta2);
void usun_krawedz(graf* g, typ etykieta1, typ etykieta2);

#endif // GRAF_H
