#ifndef SEGNALAZIONE_H
#define SEGNALAZIONE_H

typedef struct Segnalazione {
    int codice;
    char nome[50];
    char categoria[50];
    char descrizione[100];
    char data[20];
    int urgenza;
    char stato[20];
    struct Segnalazione* next;
} Segnalazione;

// Prototipi
Segnalazione* creaSegnalazione();
Segnalazione* aggiungiSegnalazione(Segnalazione* head);
void stampaSegnalazioni(Segnalazione* head);
Segnalazione* cercaPerCodice(Segnalazione* head, int codice);
void cercaPerCategoria(Segnalazione* head, char categoria[]);
void aggiornaStato(Segnalazione* head, int codice);
void stampaPerStato(Segnalazione* head, char stato[]);
void stampaUrgenti(Segnalazione* head);
Segnalazione* eliminaSegnalazione(Segnalazione* head, int codice);
void generaReport(Segnalazione* head);

#endif