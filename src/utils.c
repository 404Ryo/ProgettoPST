#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "colors.h"

void screenClear() {
    printf("\033[2J\033[H");
}

void pause() {
    printf("\nPremi invio per continuare...");
    getchar();
    getchar();
}

void title() {
    printf(blue);
    printf("=====================================\n");
    printf("   SISTEMA SEGNALAZIONI COMUNE\n");
    printf("=====================================\n");
    printf(reset);
}

void menu() {
    title();

    printf(green "1. Inserisci segnalazione\n" reset);
    printf(cyan  "2. Visualizza\n" reset);
    printf(yellow "3. Cerca codice\n" reset);
    printf(purple "4. Categoria\n" reset);
    printf(blue   "5. Aggiorna stato\n" reset);
    printf(green  "6. Filtra stato\n" reset);
    printf(cyan   "7. Urgenti\n" reset);
    printf(red    "8. Elimina\n" reset);
    printf(yellow "9. Report\n" reset);
    printf(white  "0. Esci\n" reset);

    printf("\nScelta: ");
}
// ===== MESSAGGI =====

void msgSuccess(const char* testo) {
    printf(green "[SUCCESSO] %s\n" reset, testo);
}

void msgError(const char* testo) {
    printf(red "[ERRORE] %s\n" reset, testo);
}

void msgInfo(const char* testo) {
    printf(cyan "[INFO] %s\n" reset, testo);
}