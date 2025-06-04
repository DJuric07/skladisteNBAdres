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
int particijaRastuci(NBADRES* polje, int lijevo, int desno);
int particijaPadajuci(NBADRES* polje, int lijevo, int desno);
void kreiranjeDat();
void dodavanjeDresova();
void azuriranje();
void* ucitavanjeDresova();
void ispisivanje(NBADRES*);
void* pretragaIme(NBADRES*);
void* pretragaCijena(NBADRES*);
void zamjena(NBADRES*, NBADRES*);
void brisanjeDresova(NBADRES*);
void quickSortRastuci(NBADRES* polje, int lijevo, int desno);
void quickSortPadajuci(NBADRES* polje, int lijevo, int desno);



#endif // HEADER
