#include <stdio.h>
#include <stdlib.h>
#include "graf.h"



void dodaj_wierzhcolek(graf* g, typ etykieta) {
    // sprawdzenie czy wierzcholek juz istnieje
    wierzcholek* temp = g->pierwszy;
    while (temp != NULL) {
        if (temp->etykieta == etykieta) {
            printf("Wierzchołek o etykiecie %llu już istnieje.\n", etykieta);
            return;
        }
        temp = temp->next;
    }

    // tworzymy nowy wierzcholek
    wierzcholek* nowyWierzcholek = (wierzcholek*)malloc(sizeof(wierzcholek));
    if (nowyWierzcholek == NULL) {
        printf("Błąd przydzielania pamięci.\n");
        return;
    }
    nowyWierzcholek->etykieta = etykieta;
    nowyWierzcholek->next = g->pierwszy;  // dodajemy go na poczatek listy
    nowyWierzcholek->sasiedzi = NULL;        //brak sasiadow
    nowyWierzcholek->ile_sasiad = 0;

    //dodajemy wierzcholek do listy wierzcholkow w grafie
    g->pierwszy = nowyWierzcholek;
    g->ile_wierzcholkow++;
    printf("Dodano wierzchołek o etykiecie %llu.\n", etykieta);
}




void usun_wierzcholek(graf* g, typ etykieta) {
    wierzcholek* prev = NULL;
    wierzcholek* curr = g->pierwszy;

    //szukamy wierzcholka o danej etykiecie
    while (curr != NULL && curr->etykieta != etykieta) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Wierzchołek o etykiecie %llu nie istnieje.\n", etykieta);
        return;
    }

    // usuwamy ten wierzcholek z listy sasiadow innych wierzcholkow
    wierzcholek* temp = g->pierwszy;
    while (temp != NULL) {
        //sprawdzamy czy dany wierzcholek (curr) jest sasiadem innych wierzcholkow
        for (int i = 0; i < temp->ile_sasiad; i++) {
            if (temp->sasiedzi[i]->etykieta == etykieta) {
                // usuwamy curr z listy sasiadow temp
                for (int j = i; j < temp->ile_sasiad - 1; j++) {
                    temp->sasiedzi[j] = temp->sasiedzi[j + 1];
                }
                temp->ile_sasiad--;
                temp->sasiedzi = realloc(temp->sasiedzi, temp->ile_sasiad * sizeof(wierzcholek*));
                break;
            }
        }
        temp = temp->next;
    }

    // usuwamy sąsiadów wierzcholka curr
    for (int i = 0; i < curr->ile_sasiad; i++) {
        //wystarczy teraz ze usuniemy odwolanie do curr z ich listy sąsiadow.
    }

    //usuwamy wierzcholek z listy wierzcholków
    if (prev == NULL) {  //jesli to pierwszy wierzcholek w grafie
        g->pierwszy = curr->next;
    } else {
        prev->next = curr->next;
    }

    // zwalniamy pamiec dla wierzchołka
    free(curr->sasiedzi);  // zwalniamy pamiec dla listy sasiadów wierzcholka
    free(curr);  // zwalniamy pamiec dla samego wierzcholka
    g->ile_wierzcholkow--;
    printf("Usunięto wierzchołek o etykiecie %llu.\n", etykieta);
}


void dodaj_krawedz(graf* g, typ etykieta1, typ etykieta2) {
    wierzcholek* v1 = NULL;
    wierzcholek* v2 = NULL;

    if(etykieta1==etykieta2){
        puts("Nie mozna utworzyć krawędzi pomiędzy tymi samymi wierzchołkami");
        return;
    }

    //szukamy wierzcholkow o danej etykiecie
    wierzcholek* temp = g->pierwszy;
    while (temp != NULL) {
        if (temp->etykieta == etykieta1) {
            v1 = temp;
        }
        if (temp->etykieta == etykieta2) {
            v2 = temp;
        }
        temp = temp->next;
    }

    //sprawdzenie czy oba wierzchołki zostały znalezione
    if (v1 == NULL || v2 == NULL) {
        printf("Jeden lub oba wierzchołki nie istnieją.\n");
        return;
    }

    //sprawdzenie czy krawedz juz istnieje
    for (int i = 0; i < v1->ile_sasiad; i++) {
        if (v1->sasiedzi[i]->etykieta == etykieta2) {
            printf("Krawędź między wierzchołkami %llu i %llu już istnieje.\n", etykieta1, etykieta2);
            return;
        }
    }
    //w liscie drugiego wierzcholka
    for (int i = 0; i < v2->ile_sasiad; i++) {
        if (v2->sasiedzi[i]->etykieta == etykieta1) {
            printf("Krawędź między wierzchołkami %llu i %llu już istnieje.\n", etykieta1, etykieta2);
            return;
        }
    }

    //dodajemy v2 do sasiadow v1
    v1->sasiedzi = realloc(v1->sasiedzi, (v1->ile_sasiad + 1) * sizeof(wierzcholek*));
    v1->sasiedzi[v1->ile_sasiad] = v2;
    v1->ile_sasiad++;

    //dodajemy v1 do sąsiadow v2
    v2->sasiedzi = realloc(v2->sasiedzi, (v2->ile_sasiad + 1) * sizeof(wierzcholek*));
    v2->sasiedzi[v2->ile_sasiad] = v1;
    v2->ile_sasiad++;

    printf("Dodano krawędź między wierzchołkami %llu i %llu.\n", etykieta1, etykieta2);
}



void usun_krawedz(graf* g, typ etykieta1, typ etykieta2) {
    wierzcholek* v1 = NULL;
    wierzcholek* v2 = NULL;

    //szukamy wierzcholkow o danej etykiecie
    wierzcholek* temp = g->pierwszy;
    while (temp != NULL) {
        if (temp->etykieta == etykieta1) {
            v1 = temp;
        }
        if (temp->etykieta == etykieta2) {
            v2 = temp;
        }
        temp = temp->next;
    }

    //sprawdzenie czy wierzcholki zostaly znalezione
    if (v1 == NULL || v2 == NULL) {
        printf("Jeden lub oba wierzchołki nie istnieją.\n");
        return;
    }

    //sprawdzenie czy krawedz istnieje
    int found1 = 0;
    for (int i = 0; i < v1->ile_sasiad; i++) {
        if (v1->sasiedzi[i]->etykieta == etykieta2) {
            found1 = 1;
            break;
        }
    }

    //sprawdzenie w drugiej liscie
    int found2 = 0;
    for (int i = 0; i < v2->ile_sasiad; i++) {
        if (v2->sasiedzi[i]->etykieta == etykieta1) {
            found2 = 1;
            break;
        }
    }

    if (!found1 || !found2) {
        printf("Krawędź między wierzchołkami %llu i %llu nie istnieje.\n", etykieta1, etykieta2);
        return;
    }

    //usuwamy v2 z sasiadow v1
    for (int i = 0; i < v1->ile_sasiad; i++) {
        if (v1->sasiedzi[i]->etykieta == etykieta2) {
            for (int j = i; j < v1->ile_sasiad - 1; j++) {
                v1->sasiedzi[j] = v1->sasiedzi[j + 1];
            }
            v1->ile_sasiad--;
            v1->sasiedzi = realloc(v1->sasiedzi, v1->ile_sasiad * sizeof(wierzcholek*));
            break;
        }
    }

    //usuwamy v1 z sasiadow v2
    for (int i = 0; i < v2->ile_sasiad; i++) {
        if (v2->sasiedzi[i]->etykieta == etykieta1) {
            for (int j = i; j < v2->ile_sasiad - 1; j++) {
                v2->sasiedzi[j] = v2->sasiedzi[j + 1];
            }
            v2->ile_sasiad--;
            v2->sasiedzi = realloc(v2->sasiedzi, v2->ile_sasiad * sizeof(wierzcholek*));
            break;
        }
    }

    printf("Usunięto krawędź między wierzchołkami %llu i %llu.\n", etykieta1, etykieta2);
}


