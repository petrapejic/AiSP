#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct cvor {
    int broj;
    struct cvor* sljedeci;
} CVOR;

void dodaj(CVOR** lista, int x) {
    CVOR* novi = (CVOR*)malloc(sizeof(CVOR));

    novi->broj = x;
    novi->sljedeci = NULL;

    if (*lista == NULL) {
        *lista = novi;
    }
    else {
        CVOR* pom = *lista;

        while (pom->sljedeci != NULL) {
            pom = pom->sljedeci;
        }

        pom->sljedeci = novi;
    }
}

void ispisi(CVOR* lista) {
    while (lista != NULL) {
        printf("%d ", lista->broj);
        lista = lista->sljedeci;
    }
    printf("\n");
}

CVOR* unija(CVOR* L1, CVOR* L2) {
    CVOR* L3 = NULL;

    while (L1 != NULL && L2 != NULL) {

        if (L1->broj < L2->broj) {
            dodaj(&L3, L1->broj);
            L1 = L1->sljedeci;
        }
        else if (L1->broj > L2->broj) {
            dodaj(&L3, L2->broj);
            L2 = L2->sljedeci;
        }
        else {
            dodaj(&L3, L1->broj);
            L1 = L1->sljedeci;
            L2 = L2->sljedeci;
        }
    }

    while (L1 != NULL) {
        dodaj(&L3, L1->broj);
        L1 = L1->sljedeci;
    }

    while (L2 != NULL) {
        dodaj(&L3, L2->broj);
        L2 = L2->sljedeci;
    }

    return L3;
}

CVOR* presjek(CVOR* L1, CVOR* L2) {
    CVOR* L3 = NULL;

    while (L1 != NULL && L2 != NULL) {

        if (L1->broj < L2->broj) {
            L1 = L1->sljedeci;
        }
        else if (L1->broj > L2->broj) {
            L2 = L2->sljedeci;
        }
        else {
            dodaj(&L3, L1->broj);
            L1 = L1->sljedeci;
            L2 = L2->sljedeci;
        }
    }

    return L3;
}

void obrisi(CVOR* lista) {
    while (lista != NULL) {
        CVOR* pom = lista;
        lista = lista->sljedeci;
        free(pom);
    }
}

int main() {
    CVOR* L1 = NULL;
    CVOR* L2 = NULL;
    CVOR* U;
    CVOR* P;

    int n, x;

    printf("Unesite broj elemenata liste L1: ");
    scanf("%d", &n);

    printf("Unesite elemente sortirane liste L1:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        dodaj(&L1, x);
    }

    printf("Unesite broj elemenata liste L2: ");
    scanf("%d", &n);

    printf("Unesite elemente sortirane liste L2:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        dodaj(&L2, x);
    }

    U = unija(L1, L2);
    P = presjek(L1, L2);

    printf("\nLista L1: ");
    ispisi(L1);

    printf("Lista L2: ");
    ispisi(L2);

    printf("Unija L1 i L2: ");
    ispisi(U);

    printf("Presjek L1 i L2: ");
    ispisi(P);


    obrisi(L1);
    obrisi(L2);
    obrisi(U);
    obrisi(P);

    return 0;
}
