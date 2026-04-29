#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "segnalazione.h"
#include "account.h"
#include "utils.h"

int main() {

    int scelta;
    int isAdmin = 0;
    char username[50];

    // LOGIN SAFE
    do {
        screenClear();

        printf("1. Login\n");
        printf("2. Registrati\n");
        printf("Scelta: ");

        scelta = leggiIntero();

        if (scelta == 2) {
            signin();
            pause();
        }

    } while (scelta != 1 || !login(username, &isAdmin));

    Segnalazione* lista = caricaSegnalazioni();
    if (!lista) {
        msgInfo("Lista vuota");
    }

    int codice;
    char categoria[50], stato[50];

    // MENU LOOP
    do {
        screenClear();

        if (isAdmin) menuAdmin();
        else menuUser();

        printf("Scelta: ");
        scelta = leggiIntero();

        switch (scelta) {

            case 1:
                lista = aggiungiSegnalazione(lista, username);
                break;

            case 2:
                stampaSegnalazioni(lista, username, isAdmin);
                break;

            case 3:
                printf("Codice: ");
                codice = leggiIntero();

                if (cercaPerCodice(lista, codice))
                    msgSuccess("Trovata");
                else
                    msgError("Non trovata");
                break;

            case 4:
                if (!isAdmin)
                    statoSegnalazioneUtente(lista, username);
                else {
                    printf("Categoria: ");
                    scanf("%49s", categoria);
                    cercaPerCategoria(lista, categoria);
                }
                break;

            case 5:
                if (isAdmin) {
                    printf("Codice: ");
                    codice = leggiIntero();
                    aggiornaStato(lista, codice, isAdmin);
                }
                break;

            case 6:
                if (isAdmin) {
                    printf("Stato: ");
                    scanf("%49s", stato);
                    stampaPerStato(lista, stato);
                }
                break;

            case 7:
                stampaUrgenti(lista);
                break;

            case 8:
                if (isAdmin) {
                    printf("Codice: ");
                    codice = leggiIntero();
                    lista = eliminaSegnalazione(lista, codice, isAdmin);
                }
                break;

            case 9:
                if (isAdmin)
                    generaReport(lista);
                break;

        }

        pause();

    } while (scelta != 0);

    return 0;
}