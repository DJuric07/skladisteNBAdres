#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

int main() {

    FILE* datoteka = fopen("dresovi.bin", "rb+");

    if (!datoteka) {
        datoteka = fopen("dresovi.bin", "wb+");

    if (!datoteka) {
            perror("Ne moze se otvoriti datoteka");
            return 1;
        }
    }

    int izbor;

    do {
        printf("\n1. Dodaj dres\n2. Azuriraj dres\n3. Ispisi dresove\n4. Pretrazi dres\n5. Sortiraj dresove\n6. Obrisi dres\n7. Izlaz\n");
        printf("Odabir: ");
        scanf("%d", &izbor);
        system("cls");

        switch ((Opcije)izbor) {
        case DODAJ: dodajDres(datoteka); break;
        case AZURIRAJ: azurirajDres(datoteka); break;
        case ISPISI: ispisiDresove(datoteka); break;
        case PRETRAZI: pretraziDres(datoteka); break;
        case SORTIRAJ: {
            int nacin;
            printf("1. Sortiraj po cijeni od najjeftinijeg do najskupljeg)\n");
            printf("2. Sortiraj po cijeni od najskupljeg do najjeftinijeg\n");
            printf("Odaberi nacin: ");
            scanf("%d", &nacin);
            sortirajDresove(datoteka, nacin);
            break;
        }
        case OBRISI:
            obrisiDres(datoteka);
            datoteka = fopen("dresovi.bin", "rb+");  
            break;
        case IZLAZ:
            printf("Kraj programa\n");
            break;
        default:
            printf("Nije opcija!\n");
            break;
        }
    } while (izbor != IZLAZ);

    fclose(datoteka);
    return 0;
}
