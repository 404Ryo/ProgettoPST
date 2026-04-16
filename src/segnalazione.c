#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "segnalazione.h"

// Creazione nuova segnalazione
Segnalazione* creaSegnalazione() {
    Segnalazione* nuovo = (Segnalazione*)malloc(sizeof(Segnalazione));

    printf("Codice: ");
    scanf("%d", &nuovo->codice);

    printf("Nome cittadino: ");
    scanf("%s", nuovo->nome);

    printf("Categoria: ");
    scanf("%s", nuovo->categoria);

    printf("Descrizione: ");
    scanf(" %[^\n]", nuovo->descrizione);

    printf("Data: ");
    scanf("%s", nuovo->data);

    printf("Urgenza (1-10): ");
    scanf("%d", &nuovo->urgenza);

    strcpy(nuovo->stato, "aperta");

    nuovo->next = NULL;
    return nuovo;
}

// Inserimento
Segnalazione* aggiungiSegnalazione(Segnalazione* head) {
    Segnalazione* nuovo = creaSegnalazione();
    nuovo->next = head;
    return nuovo;
}

// Stampa
void stampaSegnalazioni(Segnalazione* head) {
    if (head == NULL) {
        printf("Nessuna segnalazione.\n");
        return;
    }

    while (head != NULL) {
        printf("\nCodice: %d", head->codice);
        printf("\nNome: %s", head->nome);
        printf("\nCategoria: %s", head->categoria);
        printf("\nDescrizione: %s", head->descrizione);
        printf("\nData: %s", head->data);
        printf("\nUrgenza: %d", head->urgenza);
        printf("\nStato: %s\n", head->stato);

        head = head->next;
    }
}

// Ricerca codice
Segnalazione* cercaPerCodice(Segnalazione* head, int codice) {
    while (head != NULL) {
        if (head->codice == codice)
            return head;
        head = head->next;
    }
    return NULL;
}

// Categoria
void cercaPerCategoria(Segnalazione* head, char categoria[]) {
    int trovate = 0;
    while (head != NULL) {
        if (strcmp(head->categoria, categoria) == 0) {
            printf("\nCodice: %d - %s", head->codice, head->descrizione);
            trovate = 1;
        }
        head = head->next;
    }
    if (!trovate)
        printf("Nessuna segnalazione trovata.\n");
}

// Aggiorna stato
void aggiornaStato(Segnalazione* head, int codice) {
    Segnalazione* s = cercaPerCodice(head, codice);

    if (s == NULL) {
        printf("Segnalazione non trovata.\n");
        return;
    }

    printf("Nuovo stato: ");
    scanf(" %[^\n]", s->stato);
}

// Filtra stato
void stampaPerStato(Segnalazione* head, char stato[]) {
    while (head != NULL) {
        if (strcmp(head->stato, stato) == 0) {
            printf("\nCodice: %d - %s", head->codice, head->descrizione);
        }
        head = head->next;
    }
}

// Urgenti
void stampaUrgenti(Segnalazione* head) {
    while (head != NULL) {
        if (head->urgenza >= 8) {
            printf("\nCodice: %d - Urgenza: %d", head->codice, head->urgenza);
        }
        head = head->next;
    }
}

// Elimina
Segnalazione* eliminaSegnalazione(Segnalazione* head, int codice) {
    Segnalazione *temp = head, *prev = NULL;

    while (temp != NULL && temp->codice != codice) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Segnalazione non trovata.\n");
        return head;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("Eliminata.\n");

    return head;
}

// Report
void generaReport(Segnalazione* head) {
    int totale = 0, aperte = 0, chiuse = 0;

    while (head != NULL) {
        totale++;
        if (strcmp(head->stato, "aperta") == 0) aperte++;
        if (strcmp(head->stato, "chiusa") == 0) chiuse++;
        head = head->next;
    }

    printf("\nTotale: %d\nAperte: %d\nChiuse: %d\n", totale, aperte, chiuse);
}