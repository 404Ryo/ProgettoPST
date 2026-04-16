#include <stdio.h>
#include "segnalazione.h"
#include "utils.h"

int main() {
    Segnalazione* lista = NULL;
    int scelta, codice;
    char categoria[50], stato[20];

    do {
        printf("\n--- MENU ---");
        printf("\n1. Inserisci");
        printf("\n2. Visualizza");
        printf("\n3. Cerca codice");
        printf("\n4. Categoria");
        printf("\n5. Aggiorna stato");
        printf("\n6. Filtra stato");
        printf("\n7. Urgenti");
        printf("\n8. Elimina");
        printf("\n9. Report");
        printf("\n0. Esci");
        printf("\nScelta: ");
        scanf("%d", &scelta);
        
        screenClear();

        switch (scelta) {
            
            case 1: lista = aggiungiSegnalazione(lista); break;
            case 2: stampaSegnalazioni(lista); break;

            case 3:
                scanf("%d", &codice);
                if (cercaPerCodice(lista, codice))
                    printf("Trovata\n");
                else
                    printf("Non trovata\n");
                break;

            case 4:
                scanf("%s", categoria);
                cercaPerCategoria(lista, categoria);
                break;

            case 5:
                scanf("%d", &codice);
                aggiornaStato(lista, codice);
                break;

            case 6:
                scanf(" %[^\n]", stato);
                stampaPerStato(lista, stato);
                break;

            case 7:
                stampaUrgenti(lista);
                break;

            case 8:
                scanf("%d", &codice);
                lista = eliminaSegnalazione(lista, codice);
                break;

            case 9:
                generaReport(lista);
                break;
        }

    } while (scelta != 0);

    return 0;
}