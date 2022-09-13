// Manejos de errores.

#include "error.h"
#include <stdlib.h>
#include <stdio.h>

void Error(char* msj){
    printf("%s", msj); printf("\n");
    exit(EXIT_FAILURE);
}