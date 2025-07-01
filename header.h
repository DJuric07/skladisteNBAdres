#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 50

typedef enum {
    DODAJ = 1,
    AZURIRAJ,
    ISPISI,
    PRETRAZI,
    SORTIRAJ,
    OBRISI,
    IZLAZ
} Opcije;

typedef struct {
    int id;
    char imeIgraca[MAX_NAZIV];
    char tim[MAX_NAZIV];
    float cijena;
} NBADres;

void dodajDres(FILE* datoteka);
void azurirajDres(FILE* datoteka);
void ispisiDresove(FILE* datoteka);
void pretraziDres(FILE* datoteka);
void sortirajDresove(FILE* datoteka, int nacin);
void obrisiDres(FILE* datoteka);

int usporediCijeneUzlazno(const void* a, const void* b);
int usporediCijeneSilazno(const void* a, const void* b);

#endif
