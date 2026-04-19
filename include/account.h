#ifndef ACCOUNT_H
#define ACCOUNT_H

#define MAX_USER 50
#define MAX_PASS 50

typedef struct {
    char username[MAX_USER];
    char password[MAX_PASS];
    int isAdmin;   // 1 = admin, 0 = user
} Account;

void signin();
int login(char username[], int *isAdmin);

#endif