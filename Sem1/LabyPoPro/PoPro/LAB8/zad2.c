// Lab. 8, zadanie 1
//
// Kinga Konieczna i Jan Czechowski
// 337072 i 337066
// 02.12.2024

#include <stdio.h>
#include <stdlib.h>

struct ElListy {
  int el;
  struct ElListy *nast;
};

typedef struct ElListy *WskElListy;
typedef enum {
  FALSZ, PRAWDA
} Bool;

unsigned int liczbaElListy(WskElListy pierwszy);
/*funkcja dodaje nowy element na początek listy i jako wynik zwraca wskaźnik do niego*/
WskElListy dodajEl(WskElListy pierwszy, int war);

/*funkcja usuwa pierwszy element na liście, dla którego el=war*/
WskElListy usunEl(WskElListy pierwszy, int war);

WskElListy zwolnijListe(WskElListy pierwszy);

void wyswietlListe(WskElListy pierwszy);

Bool listaPusta(WskElListy pierwszy);

void wyswietlMenu(WskElListy pierwszy);

char odczytajOpcjeMenu(void);

Bool odczytajDana(char *tekstKom, int *wskaznikDoDanych);

int main(void) {
  WskElListy pierwszy = NULL;
  char opcja;
  int tmp;
  for (;;) {
    wyswietlMenu(pierwszy);
    opcja = odczytajOpcjeMenu();
    switch (opcja) {
      // ilustracyjnie: default nie musi być ostatnią klauzulą instrukcji switch
      default:
        puts("Bledny wybor opcji!\n");
        break;
      case 'd': /* dodanie elementu */
        if (odczytajDana("\nWprowadz dane elementu dodawanego do listy: ", &tmp)) {
          pierwszy = dodajEl(pierwszy, tmp);
          break;
        }
        fputs("Blad wprowadzania danych!\n", stderr);
        break;
      case 'w': /* wyświetlenie wszystkich elementów */
        wyswietlListe(pierwszy);
        break;
      case 'u': /* usunięcie elementu o zadanej wartości pola el */
        if (odczytajDana("\nWprowadz dane elementu do usuniecia: ", &tmp))
          pierwszy = usunEl(pierwszy, tmp);
        break;
      case 'z': /* usunięcie całej listy */
        pierwszy = zwolnijListe(pierwszy);
        break;
      case 'l':
        printf("Liczba elementow w liscie to: %u\n", liczbaElListy(pierwszy));
        break;
      case 'q': /* zakończenie działania programu */
        zwolnijListe(pierwszy);
        exit(0);
        break; // break jest tu nadmiarowe, bo wcześniej jest exit(), co kończy
        // działanie programu, ale pozostawiamy break na wypadek zmiany decyzji
        // i wywołania innej funkcji niż exit() - bez break sterowanie weszłoby
        // w kolejną klauzulę instrukcji switch
        //
        // nawet w ostatniej klauzuli instrukcji switch warto dodawać instrukcję
        // break, bo może się zdarzyć, że kiedyś dopiszemy kolejną klauzulę
        // (zapominając o dodaniu break...) i sterowanie po wykonaniu ostatniej
        // klauzuli weszłoby w nowo dopisaną,
    }
  }
  // return 0; // tu nie ma return, bo jedyny sposób wyjścia z programu to
  // wybranie opcji 'q' lub przerwanie działania programu (zwykle Ctrl+C)
}

unsigned int liczbaElListy(WskElListy pierwszy) {
    unsigned int liczbaElementow = 0;
    WskElListy biezacy = pierwszy;
    if (biezacy == NULL) {
        return liczbaElementow; // Zwróć 0 dla pustej listy
    }
    while (biezacy != NULL) {
        liczbaElementow++;
        biezacy = biezacy->nast;
    }
    return liczbaElementow;
}

WskElListy dodajEl(WskElListy pierwszy, int war) {
  WskElListy nowyElListy = (WskElListy) malloc(sizeof(struct ElListy));
  if (nowyElListy == NULL) {
    fputs("Blad alokacji pamieci", stderr);
    exit(1);
  }
  nowyElListy->el = war;
  nowyElListy->nast = NULL;

  if (pierwszy == NULL) {
    return nowyElListy;
  }
  WskElListy biezacy = pierwszy;
  while (biezacy->nast != NULL) {
    biezacy = biezacy->nast;
  }
  biezacy->nast = nowyElListy;
  
  return pierwszy;
}


void wyswietlListe(WskElListy pierwszy) {
  WskElListy ElListy = pierwszy;
  unsigned licz = 1;
  do {
    printf("Element %d Dane: %d\n", licz++, ElListy->el);
    ElListy = ElListy->nast;
  } while (ElListy != NULL);
}

WskElListy usunEl(WskElListy pierwszy, int war) {
  WskElListy ElListy = pierwszy, poprzedniElListy = NULL;
  do {
    if (ElListy->el == war) {
      if (ElListy == pierwszy) {
        pierwszy = ElListy->nast;
      } else poprzedniElListy->nast = ElListy->nast;
      free(ElListy);
      return pierwszy;
    }
    poprzedniElListy = ElListy;
    ElListy = ElListy->nast;
  } while (ElListy != NULL);
  printf("W liscie nie ma elementu z zadanymi danymi - nic nie usunieto.\n");
  return pierwszy;
}

WskElListy zwolnijListe(WskElListy pierwszy) {
  WskElListy elListy = pierwszy;
  while (elListy != NULL) {
    WskElListy tmpWsk = elListy;
    elListy = elListy->nast;
    free(tmpWsk);
  }
  return NULL;
}

Bool listaPusta(WskElListy pierwszy) {
  if (pierwszy == NULL)
    return PRAWDA;
  return FALSZ;
}

void wyswietlMenu(WskElListy pierwszy) {
  printf("Prosze wybrac opcje:\n");
  printf("\n\t'd' - dodanie nowego elementu do listy");
  if (!listaPusta(pierwszy)) {
    printf("\n\t'w' - wyswietlenie wszystkich elementow listy");
    printf("\n\t'u' - usuniecie elementu z listy");
    printf("\n\t'z' - usuniecie calej listy");
    printf("\n\t'l' - wyswietlanie liczby elementow listy");
  }
  printf("\n\t'q' - wyjscie z programu");
  printf("\n\t > ");
}

char odczytajOpcjeMenu(void) {
  char opcja[2];
  fgets(opcja, 2, stdin);
  while ((getchar()) != '\n');
  return opcja[0];
}

Bool odczytajDana(char *tekstKom, int *wskaznikDoDanych) {
  char bufor[BUFSIZ];
  int wynikKonwersji;
  printf("%s", tekstKom);
  fgets(bufor, BUFSIZ, stdin);
  wynikKonwersji = sscanf(bufor, "%d", wskaznikDoDanych);
  if (wynikKonwersji != 1)
    return FALSZ;
  return PRAWDA;
}