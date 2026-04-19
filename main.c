#include <stdio.h>
#include "segnalazione.h"
#include "utils.h"
#include "account.h"

int main() {
    int scelta;
    int isAdmin = 0;
    char username[50];

    // ===================== LOGIN SYSTEM =====================
    do {
        screenClear();
        printf("1. Login\n2. Registrati\nScelta: ");
        scanf("%d", &scelta);

        if (scelta == 2) {
            signin();
            pause();
        }

    } while (scelta != 1 || !login(username, &isAdmin));

    if (isAdmin)
        msgSuccess("Accesso come ADMIN");
    else
        msgInfo("Accesso come UTENTE");

    pause();

    // ===================== CARICAMENTO DATI =====================
    Segnalazione* lista = caricaSegnalazioni();

    int codice;
    char categoria[50], stato[20];

    // ===================== MENU PRINCIPALE =====================
    do {
        screenClear();
        menu();
        scanf("%d", &scelta);

        switch (scelta) {

            // ➕ CREA SEGNALAZIONE (USER + ADMIN)
            case 1:
                lista = aggiungiSegnalazione(lista, username);
                break;

            // 📋 VISUALIZZA
            case 2:
                stampaSegnalazioni(lista, username, isAdmin);
                break;

            // 🔎 CERCA PER CODICE
            case 3:
                printf("Codice: ");
                scanf("%d", &codice);

                if (cercaPerCodice(lista, codice))
                    msgSuccess("Trovata!");
                else
                    msgError("Non trovata!");
                break;

            // 📂 CERCA PER CATEGORIA
            case 4:
                printf("Categoria: ");
                scanf("%49s", categoria);
                cercaPerCategoria(lista, categoria);
                break;

            // 🛠️ AGGIORNA STATO (ADMIN ONLY)
            case 5:
                printf("Codice: ");
                scanf("%d", &codice);
                aggiornaStato(lista, codice, isAdmin);
                break;

            // 📌 FILTRA PER STATO
            case 6:
                printf("Stato: ");
                scanf(" %[^\n]", stato);
                stampaPerStato(lista, stato);
                break;

            // 🚨 URGENTI
            case 7:
                stampaUrgenti(lista);
                break;

            // ❌ ELIMINA (ADMIN ONLY)
            case 8:
                printf("Codice: ");
                scanf("%d", &codice);
                lista = eliminaSegnalazione(lista, codice, isAdmin);
                break;

            // 📊 REPORT
            case 9:
                generaReport(lista);
                break;

            // 🚪 USCITA
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