#include <string.h>
#include "codice.h"

int generaCodice(char categoria[]) {
    static int counter10 = 10000;
    static int counter20 = 20000;
    static int counter30 = 30000;
    static int counter40 = 40000;

    if (strcmp(categoria, "illuminazione") == 0)
        return counter10++;

    if (strcmp(categoria, "buche") == 0)
        return counter20++;

    if (strcmp(categoria, "rifiuti") == 0)
        return counter30++;

    if (strcmp(categoria, "impianti") == 0)
        return counter40++;

    return 99999; // categoria non valida
}