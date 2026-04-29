#ifndef ACCOUNT_H
#define ACCOUNT_H

// ================= LIMITI SICURI =================
#define MAX_USER 50
#define MAX_PASS 50

// ================= STRUCT ACCOUNT =================
typedef struct {
    char username[MAX_USER];
    char password[MAX_PASS];
    int isAdmin;   // 1 = admin, 0 = user
} Account;

// ================= FUNZIONI =================
void signin();
int login(char username[], int *isAdmin);

// (OPZIONALE ma consigliato per progetti grandi)
int userExists(char username[]);

#endif