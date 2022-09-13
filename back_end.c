// Generación de código.

#include <stdio.h>
#include "lexico.h"
#include "back_end.h"


void Code_gen_expresion(Expresion *exp){
    switch(exp->tipo){
        case 'D':
            printf("PUSH %d\n", exp->valor);
            break;
        case 'P':
            Code_gen_expresion(exp->izquierda);
            Code_gen_expresion(exp->derecha);
            switch(exp->operador){
                case '+':
                    printf("ADD\n");
                    break;
                case '*':
                    printf("MULT\n");
                    break;
            }
            break;
    }
}

void Procesa(AST_nodo *codigo){
    Code_gen_expresion(codigo);
    printf("PRINT\n");
}