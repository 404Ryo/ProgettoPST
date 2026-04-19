#ifndef SEGNALAZIONE_H
#define SEGNALAZIONE_H

typedef struct Segnalazione {
    int codice;
    char utente[50];
    char categoria[50];
    char descrizione[100];
    char data[30];
    int urgenza;
    char stato[20];
    struct Segnalazione* next;
} Segnalazione;

// CRUD base
Segnalazione* creaSegnalazione(char username[]);
Segnalazione* aggiungiSegnalazione(Segnalazione* head, char username[]);

// visualizzazione
void stampaSegnalazioni(Segnalazione* head, char username[], int isAdmin);
void stampaPerStato(Segnalazione* head, char stato[]);
void stampaUrgenti(Segnalazione* head);

// ricerca
Segnalazione* cercaPerCodice(Segnalazione* head, int codice);
void cercaPerCategoria(Segnalazione* head, char categoria[]);

// update
void aggiornaStato(Segnalazione* head, int codice, int isAdmin);

// delete
Segnalazione* eliminaSegnalazione(Segnalazione* head, int codice, int isAdmin);

// report
void generaReport(Segnalazione* head);

// file
void salvaSegnalazione(Segnalazione* s);
Segnalazione* caricaSegnalazioni();

#endif