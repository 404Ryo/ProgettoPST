#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "utils.h"

#define FILE_UTENTI "accounts.txt"

// ===================== CONTROLLO ESISTENZA USER =====================
int userExists(char username[]) {
    FILE *fp = fopen(FILE_UTENTI, "r");
    if (fp == NULL) return 0;

    Account temp;

    while (fscanf(fp, "%s %s %d",
        temp.username,
        temp.password,
        &temp.isAdmin) == 3) {

        if (strcmp(temp.username, username) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// ===================== REGISTRAZIONE (USER NORMALE) =====================
void signin() {
    Account a;
    FILE *fp = fopen(FILE_UTENTI, "a");

    if (fp == NULL) {
        msgError("Errore file utenti.");
        return;
    }

    printf("=== REGISTRAZIONE ===\n");

    do {
        printf("Username: ");
        scanf("%49s", a.username);

        if (userExists(a.username)) {
            msgError("Username già esistente!");
        }

    } while (userExists(a.username));

    printf("Password: ");
    scanf("%49s", a.password);

    // ❌ SEMPRE USER NORMALE
    a.isAdmin = 0;

    fprintf(fp, "%s %s %d\n",
        a.username,
        a.password,
        a.isAdmin);

    fclose(fp);

    msgSuccess("Registrazione completata!");
}

// ===================== LOGIN =====================
int login(char username[], int *isAdmin) {
    char user[MAX_USER];
    char pass[MAX_PASS];

    FILE *fp = fopen(FILE_UTENTI, "r");

    if (fp == NULL) {
        msgError("Nessun utente registrato.");
        return 0;
    }

    printf("=== LOGIN ===\n");

    printf("Username: ");
    scanf("%49s", user);

    printf("Password: ");
    scanf("%49s", pass);

    Account temp;

    while (fscanf(fp, "%s %s %d",
        temp.username,
        temp.password,
        &temp.isAdmin) == 3) {

        if (strcmp(temp.username, user) == 0 &&
            strcmp(temp.password, pass) == 0) {

            strcpy(username, temp.username);
            *isAdmin = temp.isAdmin;

            fclose(fp);

            if (*isAdmin)
                msgSuccess("Login ADMIN effettuato!");
            else
                msgSuccess("Login USER effettuato!");

            return 1;
        }
    }

    fclose(fp);
    msgError("Credenziali errate!");
    return 0;
}