#pragma once
#ifndef HEADER_H
#define HEADER_H

typedef struct nbaDres {
	int id;
	char ime[25];
	int cijena;
	int kolicina;
}NBADRES;

int izbornik();
int izbornikPret();
int izbornikSort();
void kreiranjeDat();
void dodavanjeDresova();
void azuriranje();
void* ucitavanjeDresova();
void ispisivanje(NBADRES*);
void* pretragaIme(NBADRES*);
void* pretragaCijena(NBADRES*);
void zamjena(NBADRES*, NBADRES*);
void selectionSortNajjefCijena(NBADRES*);
void selectionSortNajskupCijena(NBADRES*);
void brisanjeDresova(NBADRES*);



#endif // HEADER_H