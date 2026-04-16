#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void screenClear() {
    printf("\033[2J\033[H");
}