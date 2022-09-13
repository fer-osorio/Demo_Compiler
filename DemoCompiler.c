#include "lexico.h"
#include "back_end.h"
#include "error.h"

int main(void){
    AST_nodo *codigo;
    if(! analisis_sintactico(&codigo))
        Error("Expresión no reconocida por la gramatica.");
    Procesa(codigo);

    return 0;
}