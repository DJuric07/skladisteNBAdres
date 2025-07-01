#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

static void swapID(NBADres* a, NBADres* b) {
    NBADres temp = *a;
    *a = *b;
    *b = temp;
}

static int partitionID(NBADres* niz, int low, int high) {
    int pivot = niz[high].id;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (niz[j].id <= pivot) {
            i++;
            swapID(&niz[i], &niz[j]);
        }
    }
    swapID(&niz[i + 1], &niz[high]); //stavlja pivot na pravo mjesto
    return i + 1;
}

static void quickSortID(NBADres* niz, int low, int high) {
    if (low < high) {
        int pi = partitionID(niz, low, high);
        quickSortID(niz, low, pi - 1); //rekurzivno sortira lijevi podniz
        quickSortID(niz, pi + 1, high); //rekurzivno sortira desni podniz
    }
}

int usporediCijeneUzlazno(const void* a, const void* b) {
    float c1 = ((NBADres*)a)->cijena;
    float c2 = ((NBADres*)b)->cijena;
    if (c1 < c2) return -1;
    if (c1 > c2) return 1;
    return 0;
}

int usporediCijeneSilazno(const void* a, const void* b) {
    float c1 = ((NBADres*)a)->cijena;
    float c2 = ((NBADres*)b)->cijena;
    if (c1 < c2) return 1;
    if (c1 > c2) return -1;
    return 0;
}

void dodajDres(FILE* datoteka) {
    NBADres novi;
    printf("Unesi ID: ");
    scanf("%d", &novi.id);  // nije &novi jer bi cijelu strukturu uhvatilo
    printf("Unesi ime igraca: ");
    scanf(" %49[^\n]", novi.imeIgraca);
    printf("Unesi tim: ");
    scanf(" %49[^\n]", novi.tim);
    printf("Unesi cijenu: ");
    scanf("%f", &novi.cijena);

    fseek(datoteka, 0, SEEK_END);  // postavlja pokazivac na kraj i pomjera pokazivac za 0 bajtova
    fwrite(&novi, sizeof(NBADres), 1, datoteka); // adresa strukture koje cemo zapisat (1 element) u datoteku
    printf("Dres dodan.\n");
}

void azurirajDres(FILE* datoteka) {
    int trazeniID;
    NBADres temp;
    printf("Unesi ID za azuriranje: ");
    scanf("%d", &trazeniID);

    rewind(datoteka); // postavlja pokazivac na pocetak da moze procitat sve zapise

    long pozicija = 0;
    int pronadjen = 0;

    while (fread(&temp, sizeof(NBADres), 1, datoteka)) {  // fread cita jedan zapis velicine sizeof iz datoteke i sprema ga u temp strukturu
        if (temp.id == trazeniID) {
            pronadjen = 1;
            pozicija = ftell(datoteka) - sizeof(NBADres); // ftell vraca trenutnu poziciju u datoteci te oduzimamo da dobijemo pocetnu poziciju 
            fseek(datoteka, pozicija, SEEK_SET); // postavlja pokazivac datoteke na pocetak zapisa koji zelimo azurirati

            printf("Unesi novo ime igraca: ");
            scanf(" %49[^\n]", temp.imeIgraca);
            printf("Unesi novi tim: ");
            scanf(" %49[^\n]", temp.tim);
            printf("Unesi novu cijenu: ");
            scanf("%f", &temp.cijena);

            fwrite(&temp, sizeof(NBADres), 1, datoteka);
            fflush(datoteka); // osigurava da se promjene odmah fizicki zapisu 
            printf("Dres s ID %d azuriran.\n", trazeniID);
            break;
        }
    }

    if (!pronadjen)
        printf("Dres s ID %d nije pronadjen.\n", trazeniID);
}

void ispisiDresove(FILE* datoteka) {
    NBADres temp;
    rewind(datoteka);
    while (fread(&temp, sizeof(NBADres), 1, datoteka)) {
        printf("ID: %d | Igrac: %s | Tim: %s | Cijena: %.2f\n",
            temp.id, temp.imeIgraca, temp.tim, temp.cijena);
    }
}

void pretraziDres(FILE* datoteka) {
    int trazeniID;
    NBADres temp;
    printf("Unesi ID za pretragu: ");
    scanf("%d", &trazeniID);
    rewind(datoteka);
    while (fread(&temp, sizeof(NBADres), 1, datoteka)) {
        if (temp.id == trazeniID) {
            printf("Pronadjen: %s iz %s, cijena %.2f\n",
                temp.imeIgraca, temp.tim, temp.cijena);
            return;
        }
    }
    printf("Dres nije pronadjen.\n");
}

void sortirajDresove(FILE* datoteka, int nacin) {
    fseek(datoteka, 0, SEEK_END);
    long velicina = ftell(datoteka); //ftell određuje ukupnu veličinu datoteke u bajtovima
    int broj = velicina / sizeof(NBADres); //izračunava koliko zapisa o NBA dresovima se nalazi u datoteci (1,2,3...)
    rewind(datoteka);

    if (broj == 0) {
        printf("Nema dresova za sortiranje.\n");
        return;
    }

    NBADres* niz = (NBADres*)malloc(broj * sizeof(NBADres)); //malloc-funkcija za dinamicku alokaciju memorije,()ukupna velicina memorije koja se trazi
    if (!niz) {
        perror("Greska pri alokaciji memorije");
        return;
    }

    fread(niz, sizeof(NBADres), broj, datoteka); // fread učitava podatke iz datoteke u prethodno alocirani niz 

    if (nacin == 1)
        qsort(niz, broj, sizeof(NBADres), usporediCijeneUzlazno); //niz - pokazivac na pocetak niza koji se sortira
    else if (nacin == 2)
        qsort(niz, broj, sizeof(NBADres), usporediCijeneSilazno);
    else if (nacin == 3) {
        quickSortID(niz, 0, broj - 1); // niz - pokazivac na niz dresova iz datoteke
    }
    else {
        printf("Nepoznat nacin sortiranja.\n");
        free(niz);
        return;
    }

    rewind(datoteka);
    fwrite(niz, sizeof(NBADres), broj, datoteka);
    fflush(datoteka);

    printf("\n--- Sortirani dresovi ---\n");
    for (int i = 0; i < broj; i++) {
        printf("ID: %d | Igrac: %s | Tim: %s | Cijena: %.2f\n",
            niz[i].id, niz[i].imeIgraca, niz[i].tim, niz[i].cijena);
    }
    printf("--------------------------\n");

    free(niz);
    niz = NULL;
}


void obrisiDres(FILE* datoteka) {
    int trazeniID;
    printf("Unesi ID za brisanje: ");
    scanf("%d", &trazeniID);

    FILE* privremena = fopen("temp.bin", "wb"); //otvara se nova privremena datoteka u binarnom modu za pisanje
    if (!privremena) {
        perror("Greska pri otvaranju privremene datoteke");
        return;
    }

    NBADres temp;
    rewind(datoteka);
    while (fread(&temp, sizeof(NBADres), 1, datoteka)) {
        if (temp.id != trazeniID)
            fwrite(&temp, sizeof(NBADres), 1, privremena); //upisuje zapis u privremenu datoteku, radi analogno od fread
    }

    fclose(datoteka);
    fclose(privremena);

    remove("dresovi.bin"); //originalna datoteka se brise
    rename("temp.bin", "dresovi.bin"); //privremena datoteka se preimenuje u ime originalne datoteke

    printf("Dres obrisan ako je postojao.\n");
}
