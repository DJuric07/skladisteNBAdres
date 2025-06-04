#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

static int brojDresova = 0;
static int i;
static int j;
static int br = 0;

int izbornik() {
	int uvijet = 0;
	static NBADRES* polje = NULL;

	printf("Odaberite jednu od opcija.");
	printf("\n***************************\n");
	printf("Opcija 1: Dodaj NBA dres\n");
	printf("Opcija 2: Azuriranje NBA dresova\n");
	printf("Opcija 3: Ispisivanje NBA dresova\n");
	printf("Opcija 4: Pretrazivanje NBA dresova\n");
	printf("Opcija 5: Sortiranje NBA dresova\n");
	printf("Opcija 6: Brisanje NBA dresova\n");
	printf("Opcija 7: Izlaz iz programa\n");
	printf("***************************\n");

	printf("ODABIR: ");
	scanf("%d", &uvijet);
	system("cls");

	switch (uvijet) {
	case 1:	ucitavanjeDresova();
		if (brojDresova == 0) {
			kreiranjeDat();
		}
		dodavanjeDresova();
		break;

	case 2: azuriranje(); break;

	case 3: if (polje != NULL) {
		free(polje);
		polje = NULL;
	}
		  polje = (NBADRES*)ucitavanjeDresova();
		  ispisivanje(polje);
		  break;

	case 4:
		while (uvijet != 90) {
			uvijet = izbornikPret();
		}
		break;

	case 5: while (uvijet != 89)
		uvijet = izbornikSort();
		break;

	case 6: if (polje == NULL)
		printf("Nema unesenih dresova\n\n");
		  else
		brisanjeDresova(polje);
		break;

	case 7:
		printf("Zelite li izaci iz programa? (da/ne)\n");
		char odgovor[3] = { '\0' };
		scanf("%2s", odgovor);
		if (strcmp("da", odgovor) == 0) {
			free(polje);
			return 99;

		}
		break;

	default:
		printf("\nPogresan unos!\n\n");
	}

	return uvijet;
}

int izbornikPret() {
	int uvijet = 0;
	NBADRES* polje = NULL;
	polje = (NBADRES*)ucitavanjeDresova();
	printf("Pretrazivanje.\n\n");
	printf("Opcija 1: Cijena\n");
	printf("Opcija 2: Ime\n");
	printf("Opcija 3: Povratak\n");
	printf("ODABIR: ");
	scanf("%d", &uvijet);
	system("cls");

	switch (uvijet) {
	case 1: pretragaCijena(polje); break;
	case 2:	pretragaIme(polje); break;
	case 3: return 90;
	default: printf("\nPogresan unos!\n");

	}

	return uvijet;
}

int izbornikSort() {
	int uvijet = 0;
	NBADRES* polje = NULL;
	polje = (NBADRES*)ucitavanjeDresova();

	if (polje == NULL) {
		printf("Nema dresova za sortiranje.\n");
		return 0;
	}

	printf("Sortiranje.\n\n");
	printf("Opcija 1: Cijena od najjeftinijeg do najskupljeg\n");
	printf("Opcija 2: Cijena od najskupljeg do najjeftinijeg\n");
	printf("Opcija 3: Povratak\n");
	printf("ODABIR: ");
	scanf("%d", &uvijet);
	system("cls");

	switch (uvijet) {
	case 1:
		quickSortRastuci(polje, 0, brojDresova - 1);
		printf("Sortirani dresovi po cijeni od najjeftinijeg do najskupljeg:\n");
		ispisivanje(polje);
		break;
	case 2:
		quickSortPadajuci(polje, 0, brojDresova - 1);
		printf("Sortirani dresovi po cijeni od najskupljeg do najjeftinijeg:\n");
		ispisivanje(polje);
		break;
	case 3:
		return 89;
	default:
		printf("\nPogresan unos!\n");
	}

	free(polje);
	return uvijet;
}


void kreiranjeDat() {
	FILE* fp = NULL;
	fp = fopen("dresovi.bin", "wb");

	if (fp == NULL) {
		perror("Kreiranje");
	}
	else {
		fwrite(&brojDresova, sizeof(int), 1, fp);
		fclose(fp);
	}
}

void dodavanjeDresova() {
	FILE* fp = NULL;
	fp = fopen("dresovi.bin", "rb+");

	if (fp == NULL) {
		perror("Dodavanje");
		exit(1);
	}

	fread(&brojDresova, sizeof(int), 1, fp);
	printf("Trenutni broj dresova: %d", brojDresova);

	NBADRES dresovi;
	dresovi.id = brojDresova + 1;
	br++;
	getchar();
	printf("\nUnesite ime NBA dresa: ");
	scanf("%24[^\n]", dresovi.ime);
	printf("\nUnesite cijenu NBA dresa: ");
	scanf("%d", &dresovi.cijena);
	printf("\nUnesite kolicinu NBA dresova: ");
	scanf("%d", &dresovi.kolicina);
	fseek(fp, sizeof(NBADRES) * brojDresova, SEEK_CUR);
	fwrite(&dresovi, sizeof(NBADRES), 1, fp);
	rewind(fp);
	brojDresova++;
	fwrite(&brojDresova, sizeof(int), 1, fp);
	fclose(fp);
}

void azuriranje() {
	FILE* fp = NULL;
	int ispravak;
	fp = fopen("dresovi.bin", "rb+");
	if (fp == NULL)
		printf("Nema unesenih dresova\n\n");
	else {
		printf("Unesi broj dresa koji zelite ispraviti.\n");
		scanf("%d", &ispravak);
		fseek(fp, sizeof(int) + (sizeof(NBADRES) * (ispravak - 1)), SEEK_SET);
		NBADRES ispravljenDres;
		ispravljenDres.id = ispravak;
		getchar();
		printf("\nUnesite ime NBA dresa: ");
		scanf("%24[^\n]", ispravljenDres.ime);
		printf("\nUnesite cijenu NBA dresa: ");
		scanf("%d", &ispravljenDres.cijena);
		printf("\nUnesite kolicinu NBA dresova: ");
		scanf("%d", &ispravljenDres.kolicina);
		fwrite(&ispravljenDres, sizeof(NBADRES), 1, fp);
		rewind(fp);
		fwrite(&brojDresova, sizeof(int), 1, fp);
		fclose(fp);

	}
}

void* ucitavanjeDresova() {
	FILE* fp = fopen("dresovi.bin", "rb");
	if (fp == NULL) {
		printf("Nema unesenih dresova\n\n");
		return NULL;
	}
	fread(&brojDresova, sizeof(int), 1, fp);
	NBADRES* polje = NULL;
	polje = (NBADRES*)calloc(brojDresova, sizeof(NBADRES));
	if (polje == NULL) {
		perror("Zauzimanje memorije");
		return NULL;
	}
	fread(polje, sizeof(NBADRES), brojDresova, fp);
	fclose(fp);
	return polje;
}

void ispisivanje(NBADRES* polje) {
	for (i = 0; i < brojDresova; i++)
	{
		printf("NBA dres broj %d:\tID: %d\tIme: %s\tCijena:  %d\tKolicina: %d\n", i + 1, (polje + i)->id, (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);
	}
}

void* pretragaIme(NBADRES* polje) {
	char trazenoIme[25] = { 0 };
	int brojac = 0;

	printf("Upisite ime NBA dresa koji zelite pronaci.\n");
	getchar();
	scanf("%24[^\n]", trazenoIme);

	for (i = 0; i < brojDresova; i++) {
		if (!strcmp(trazenoIme, (polje + i)->ime)) {
			printf("\nIme dresa je pronadeno!\n\n");
			printf("\tIme: %s\tCijena: %d\tKolicina: %d\n\n", (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);
			brojac++;
		}
	}
	if (brojac == 0)
		printf("\nIme dresa nije pronadeno!\n\n");
	return NULL;
}

void* pretragaCijena(NBADRES* polje) {
	int trazenaCijena;
	int brojac = 0;

	printf("Upisite cijenu dresa koju zelite pronaci.\n");
	scanf("%d", &trazenaCijena);

	for (i = 0; i < brojDresova; i++) {
		if (trazenaCijena == (polje + i)->cijena) {
			printf("\nCijena dresa je pronadena!\n\n");
			printf("\tIme: %s\tCijena: %d\tKolicina: %d\n\n", (polje + i)->ime, (polje + i)->cijena, (polje + i)->kolicina);
			brojac++;
		}
	}
	if (brojac == 0)
		printf("\nCijena dresa nije pronadena!\n\n");
	return NULL;
}

void zamjena(NBADRES* veci, NBADRES* manji) {
	NBADRES temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void quickSortRastuci(NBADRES* polje, int lijevo, int desno) {
	if (lijevo < desno) {
		int pivot = particijaRastuci(polje, lijevo, desno);
		quickSortRastuci(polje, lijevo, pivot - 1);
		quickSortRastuci(polje, pivot + 1, desno);
	}
}

void quickSortPadajuci(NBADRES* polje, int lijevo, int desno) {
	if (lijevo < desno) {
		int pivot = particijaPadajuci(polje, lijevo, desno);
		quickSortPadajuci(polje, lijevo, pivot - 1);
		quickSortPadajuci(polje, pivot + 1, desno);
	}
}

int particijaRastuci(NBADRES* polje, int lijevo, int desno) {
	int pivot = polje[desno].cijena;
	int i = (lijevo - 1);

	for (int j = lijevo; j <= desno - 1; j++) {
		if (polje[j].cijena <= pivot) {
			i++;
			zamjena(&polje[i], &polje[j]);
		}
	}
	zamjena(&polje[i + 1], &polje[desno]);
	return (i + 1);
}

int particijaPadajuci(NBADRES* polje, int lijevo, int desno) {
	int pivot = polje[desno].cijena;
	int i = (lijevo - 1);

	for (int j = lijevo; j <= desno - 1; j++) {
		if (polje[j].cijena >= pivot) {
			i++;
			zamjena(&polje[i], &polje[j]);
		}
	}
	zamjena(&polje[i + 1], &polje[desno]);
	return (i + 1);
}

void brisanjeDresova(NBADRES* polje) {
	FILE* fp = NULL;
	fp = fopen("dresovi.bin", "wb");
	if (fp == NULL) {
		perror("  Brisanje dresova");
		exit(1);
	}

	rewind(fp);
	fseek(fp, sizeof(int), SEEK_CUR);

	int brojac = 0;
	int trazeniDres;

	printf("\nUnesi ID dresa koji zelite obrisati\n");
	scanf("%d", &trazeniDres);

	for (i = 0; i < brojDresova; i++) {
		if (trazeniDres != (polje + i)->id) {
			fwrite((polje + i), sizeof(NBADRES), 1, fp);
			brojac++;
		}
	}
	rewind(fp);
	fwrite(&brojac, sizeof(int), 1, fp);
	fclose(fp);
}
