#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba {
    char ime[50];
    char prezime[50];
    int godina_rodjenja;
    struct Osoba* sljedeci;
} Osoba;

void unosOsobe(Osoba* nova) {
    printf("Unesite ime: ");
    scanf("%49s", nova->ime);

    printf("Unesite prezime: ");
    scanf("%49s", nova->prezime);

    printf("Unesite godinu rodenja: ");
    scanf("%d", &nova->godina_rodjenja);
}

Osoba* dodajNaPocetak(Osoba* glava) {
    Osoba* nova = malloc(sizeof(Osoba));

    if (nova == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return glava;
    }

    unosOsobe(nova);

    nova->sljedeci = glava;
    glava = nova;

    return glava;
}

void ispisiListu(Osoba* glava) {
    Osoba* tekuci = glava;

    if (glava == NULL) {
        printf("Lista je prazna.\n");
        return;
    }

    while (tekuci != NULL) {
        printf("Ime: %s, Prezime: %s, Godina rodenja: %d\n",
            tekuci->ime,
            tekuci->prezime,
            tekuci->godina_rodjenja);

        tekuci = tekuci->sljedeci;
    }
}

Osoba* dodajNaKraj(Osoba* glava) {
    Osoba* nova = malloc(sizeof(Osoba));

    if (nova == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return glava;
    }

    unosOsobe(nova);
    nova->sljedeci = NULL;

    if (glava == NULL) {
        return nova;
    }

    Osoba* tekuci = glava;

    while (tekuci->sljedeci != NULL) {
        tekuci = tekuci->sljedeci;
    }

    tekuci->sljedeci = nova;

    return glava;
}


Osoba* pronadiOsobu(Osoba* glava, const char* prezime) {
    Osoba* tekuci = glava;

    while (tekuci != NULL) {
        if (strcmp(tekuci->prezime, prezime) == 0) {
            return tekuci;
        }

        tekuci = tekuci->sljedeci;
    }

    return NULL;
}


Osoba* obrisiOsobu(Osoba* glava, const char* prezime) {
    Osoba* tekuci = glava;
    Osoba* prethodni = NULL;

    while (tekuci != NULL &&
        strcmp(tekuci->prezime, prezime) != 0) {
        prethodni = tekuci;
        tekuci = tekuci->sljedeci;
    }

    if (tekuci == NULL) {
        printf("Osoba s tim prezimenom nije pronadena.\n");
        return glava;
    }

    if (prethodni == NULL) {
        glava = tekuci->sljedeci;
    }
    else {
        prethodni->sljedeci = tekuci->sljedeci;
    }

    free(tekuci);

    printf("Osoba je uspjesno obrisana.\n");
    return glava;
}


void oslobodiListu(Osoba* glava) {
    while (glava != NULL) {
        Osoba* zaBrisanje = glava;
        glava = glava->sljedeci;
        free(zaBrisanje);
    }
}

int main(void) {
    Osoba* glava = NULL;
    Osoba* pronadena;
    char trazenoPrezime[50];
    int izbor;

    do {
        printf("\n--- IZBORNIK ---\n");
        printf("1. Dodaj osobu na pocetak\n");
        printf("2. Ispisi listu\n");
        printf("3. Dodaj osobu na kraj\n");
        printf("4. Pronadi osobu po prezimenu\n");
        printf("5. Obrisi osobu po prezimenu\n");
        printf("0. Izlaz\n");
        printf("Odabir: ");

        if (scanf("%d", &izbor) != 1) {
            printf("Neispravan unos.\n");
            break;
        }

        switch (izbor) {
        case 1:
            glava = dodajNaPocetak(glava);
            break;

        case 2:
            ispisiListu(glava); 

        case 3:
            glava = dodajNaKraj(glava);
            break;

        case 4:
            printf("Unesite prezime za pretragu: ");
            scanf("%49s", trazenoPrezime);

            pronadena = pronadiOsobu(glava, trazenoPrezime);

            if (pronadena != NULL) {
                printf("Osoba je pronadena:\n");
                printf("Ime: %s, Prezime: %s, Godina rodenja: %d\n",
                    pronadena->ime,
                    pronadena->prezime,
                    pronadena->godina_rodjenja);
            }
            else {
                printf("Osoba nije pronadena.\n");
            }
            break;

        case 5:
            printf("Unesite prezime osobe za brisanje: ");
            scanf("%49s", trazenoPrezime);

            glava = obrisiOsobu(glava, trazenoPrezime);
            break;

        case 0:
            printf("Kraj programa.\n");
            break;

        default:
            printf("Nepostojeca opcija.\n");
        }

    } while (izbor != 0);

    oslobodiListu(glava);

    return 0;
}
