// Jan Czechowski 337066

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int wartoscElementu;
    struct elementListy *nastepny;
}elementListy;

typedef struct {
    elementListy *wierzcholek;
    int rozmiar;
    int maxRozmiar;
} stos;

//funkcja służąca do tworzenia stosu, przyjmuje argument mowiący o wielkości listy
stos* utworzenieStosu(int wielkoscListy){
    stos *nowyStos = malloc(sizeof(stos));
    if (nowyStos == NULL)
    {
        puts("Blad alokacji pamieci podczas tworzenia stosuu");
    
    nowyStos->wierzcholek = NULL;
    nowyStos->rozmiar = 0;
    nowyStos->maxRozmiar = wielkoscListy;
    return nowyStos;
}

//funkcja służąca do dodawania elementów, przyjmuje argumenty takie jak stos do ktorego chcemy dodac elemnet oraz wartosc tego elementu
void dodajElement(stos *uzywanyStos, int wartosc){
    elementListy *nowy = malloc(sizeof(elementListy));
    if (uzywanyStos->rozmiar == uzywanyStos->maxRozmiar)
    {
        puts("Stos jest pelny");
    }
    
    else if (uzywanyStos->wierzcholek == NULL)
    {
        uzywanyStos->rozmiar++;
        nowy->wartoscElementu = wartosc;
        nowy->nastepny = NULL;
    }
    else
    {
        nowy->wartoscElementu = wartosc;
        nowy->nastepny = uzywanyStos->wierzcholek;
        uzywanyStos->rozmiar++;
    }

}

//funkcja służąca do usuwania elementów, argumenty to stos z ktorego chcemy zdjac element ze stosu
int usunElement(stos *uzywanyStos){
    if (uzywanyStos->rozmiar == 0)
    {
        puts("Lista jest pusta");
        return -1;
    }
    else
    {
        elementListy *temp = uzywanyStos->wierzcholek;
        int wartosc = temp->wartoscElementu;
        uzywanyStos->wierzcholek = temp->nastepny;
        free(temp);
        uzywanyStos->rozmiar--;
        return wartosc;

    }
    
    
}

void wyswietlWierzcholek(){

}

int main(void){
    int N = 5;
    stos *stosTestowy = utworzStos(N);

    dodajElement(stosTestowy, 10);
    dodajElement(stosTestowy, 15);
    dodajElement(stosTestowy, 8);


    return 0;
}