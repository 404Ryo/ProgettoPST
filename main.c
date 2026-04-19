#include <stdio.h>
#include "segnalazione.h"
#include "utils.h"
#include "account.h"

int main() {
    int scelta;
    int isAdmin = 0;
    char username[50];

    // ===================== LOGIN =====================
    do {
        screenClear();

        printf("1. Login\n");
        printf("2. Registrati\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        if (scelta == 2) {
            signin();
            pause();
        }

    } while (scelta != 1 || !login(username, &isAdmin));

    // ===================== CARICAMENTO =====================
    Segnalazione* lista = caricaSegnalazioni();

    int codice;
    char categoria[50], stato[20];

    // ===================== MENU =====================
    do {
        screenClear();

        if (isAdmin)
            menuAdmin();
        else
            menuUser();

        scanf("%d", &scelta);

        switch (scelta) {

            // ================= USER + ADMIN =================
            case 1:
                lista = aggiungiSegnalazione(lista, username);
                break;

            case 2:
                stampaSegnalazioni(lista, username, isAdmin);
                break;

            case 3:
                printf("Codice: ");
                scanf("%d", &codice);

                if (cercaPerCodice(lista, codice))
                    msgSuccess("Trovata!");
                else
                    msgError("Non trovata!");
                break;

            // ================= USER =================
            case 4:
                if (!isAdmin) {
                    printf("Codice: ");
                    scanf("%d", &codice);
                    statoSegnalazioneUtente(lista, username);
                } else {
                    printf("Categoria: ");
                    scanf("%49s", categoria);
                    cercaPerCategoria(lista, categoria);
                }
                break;

            // ================= ADMIN ONLY =================
            case 5:
                if (!isAdmin) {
                    msgError("Non autorizzato");
                    break;
                }
                printf("Codice: ");
                scanf("%d", &codice);
                aggiornaStato(lista, codice, isAdmin);
                break;

            case 6:
                if (!isAdmin) {
                    msgError("Non autorizzato");
                    break;
                }
                printf("Stato: ");
                scanf(" %[^\n]", stato);
                stampaPerStato(lista, stato);
                break;

            case 7:
                stampaUrgenti(lista);
                break;

            case 8:
                if (!isAdmin) {
                    msgError("Non autorizzato");
                    break;
                }
                printf("Codice: ");
                scanf("%d", &codice);
                lista = eliminaSegnalazione(lista, codice, isAdmin);
                break;

            case 9:
                if (!isAdmin) {
                    msgError("Non autorizzato");
                    break;
                }
                generaReport(lista);
                break;

            case 0:
                msgInfo("Uscita...");
                break;

            default:
                msgError("Scelta non valida!");
        }

        pause();

    } while (scelta != 0);

    return 0;
}