#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "segnalazione.h"
#include "colors.h"
#include "utils.h"
#include "codice.h"

// ===================== CREA =====================
Segnalazione* creaSegnalazione(char username[]) {
    Segnalazione* s = malloc(sizeof(Segnalazione));
    if (!s) {
        msgError("Errore allocazione memoria");
        return NULL;
    }

    strcpy(s->utente, username);

    printf(cyan "Categoria (illuminazione/buche/rifiuti/impianti): " reset);
    scanf("%49s", s->categoria);

    s->codice = generaCodice(s->categoria);

    printf(cyan "Descrizione: " reset);
    scanf(" %[^\n]", s->descrizione);

    printf(cyan "Urgenza (1-10): " reset);
    scanf("%d", &s->urgenza);

    // timestamp automatico
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(s->data, 30, "%d/%m/%Y %H:%M", tm_info);

    strcpy(s->stato, "aperta");
    s->next = NULL;

    salvaSegnalazione(s);

    msgSuccess("Segnalazione creata!");
    return s;
}

// ===================== AGGIUNGI =====================
Segnalazione* aggiungiSegnalazione(Segnalazione* head, char username[]) {
    Segnalazione* nuovo = creaSegnalazione(username);

    if (!nuovo) return head;

    nuovo->next = head;
    return nuovo;
}

// ===================== STAMPA =====================
void stampaSegnalazioni(Segnalazione* head, char username[], int isAdmin) {
    if (!head) {
        msgError("Nessuna segnalazione");
        return;
    }

    while (head) {

        if (!isAdmin && strcmp(head->utente, username) != 0) {
            head = head->next;
            continue;
        }

        printf(yellow "\n---------------------\n" reset);
        printf("Codice: %d\n", head->codice);
        printf("Utente: %s\n", head->utente);
        printf("Categoria: %s\n", head->categoria);
        printf("Descrizione: %s\n", head->descrizione);
        printf("Data: %s\n", head->data);
        printf("Urgenza: %d\n", head->urgenza);
        printf("Stato: %s\n", head->stato);

        head = head->next;
    }
}

// ===================== CERCA CODICE =====================
Segnalazione* cercaPerCodice(Segnalazione* head, int codice) {
    while (head) {
        if (head->codice == codice)
            return head;
        head = head->next;
    }
    return NULL;
}

// ===================== CERCA CATEGORIA =====================
void cercaPerCategoria(Segnalazione* head, char categoria[]) {
    int trovato = 0;

    while (head) {
        if (strcmp(head->categoria, categoria) == 0) {
            printf("Codice: %d | %s\n", head->codice, head->descrizione);
            trovato = 1;
        }
        head = head->next;
    }

    if (!trovato)
        msgError("Nessuna segnalazione trovata");
}

// ===================== UPDATE STATO (ADMIN) =====================
void aggiornaStato(Segnalazione* head, int codice, int isAdmin) {
    if (!isAdmin) {
        msgError("Solo admin può modificare lo stato");
        return;
    }

    Segnalazione* s = cercaPerCodice(head, codice);

    if (!s) {
        msgError("Non trovata");
        return;
    }

    printf(cyan "Nuovo stato: " reset);
    scanf(" %[^\n]", s->stato);

    msgSuccess("Stato aggiornato");
}

// ===================== STATO =====================
void stampaPerStato(Segnalazione* head, char stato[]) {
    int ok = 0;

    while (head) {
        if (strcmp(head->stato, stato) == 0) {
            printf("%d - %s\n", head->codice, head->descrizione);
            ok = 1;
        }
        head = head->next;
    }

    if (!ok)
        msgError("Nessuna segnalazione con questo stato");
}

// ===================== URGENTI =====================
void stampaUrgenti(Segnalazione* head) {
    while (head) {
        if (head->urgenza >= 8)
            printf("URGENTE %d - %s\n", head->codice, head->descrizione);

        head = head->next;
    }
}

// ===================== DELETE =====================
Segnalazione* eliminaSegnalazione(Segnalazione* head, int codice, int isAdmin) {
    if (!isAdmin) {
        msgError("Solo admin può eliminare");
        return head;
    }

    Segnalazione *tmp = head, *prev = NULL;

    while (tmp && tmp->codice != codice) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (!tmp) {
        msgError("Non trovata");
        return head;
    }

    if (!prev)
        head = tmp->next;
    else
        prev->next = tmp->next;

    free(tmp);

    msgSuccess("Eliminata");
    return head;
}

// ===================== REPORT =====================
void generaReport(Segnalazione* head) {
    int t=0,a=0,c=0;

    while (head) {
        t++;
        if (strcmp(head->stato,"aperta")==0) a++;
        if (strcmp(head->stato,"chiusa")==0) c++;
        head = head->next;
    }

    printf("\nTotale:%d Aperte:%d Chiuse:%d\n", t,a,c);
}

// ===================== FILE SAVE =====================
void salvaSegnalazione(Segnalazione* s) {
    FILE* f = fopen("segnalazioni.txt","a");
    if(!f){msgError("Errore file"); return;}

    fprintf(f,"%d %s %s %s %s %d %s\n",
        s->codice,
        s->utente,
        s->categoria,
        s->descrizione,
        s->data,
        s->urgenza,
        s->stato);

    fclose(f);
}

// ===================== FILE LOAD =====================
Segnalazione* caricaSegnalazioni() {
    FILE* f = fopen("segnalazioni.txt","r");
    if(!f) return NULL;

    Segnalazione *h=NULL,*t;

    while(1){
        t=malloc(sizeof(Segnalazione));

        if(fscanf(f,"%d %s %s %s %s %d %s",
            &t->codice,
            t->utente,
            t->categoria,
            t->descrizione,
            t->data,
            &t->urgenza,
            t->stato)!=7){
            free(t);
            break;
        }

        t->next=h;
        h=t;
    }

    fclose(f);
    return h;
}