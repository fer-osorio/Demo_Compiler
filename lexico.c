// Análisis léxico. Definiciones.

#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"
#include "error.h"

/* Función privada; nos permite verificar si un caracter es solo de 'presentación',
    es decir, si es un espacio, tabulador o cambio de linea.*/
int es_caracter_presentacion(int ch){
    switch (ch)
    {
    case' ': case'\t': case'\n': return 1;    
    default: return 0;
    }
}

Tipo_simbolo Simbolo;

void consigue_sig_simbolo(void){
    int ch;

    // Tomamos un simbolo que no sea ' ', '\t', '\n'; es decir, que no sea de presentación.
    do
    {
        ch = getchar();

        // Nos protegenos contra simbolos no reconocidos por el codigo ASCII.
        if (ch < 0)
        {
            Simbolo.clase = EoF;
            Simbolo.representacion = '#';
            return;
        }
        
    } while (es_caracter_presentacion(ch));

    // Clasificamos el simbolo.
    if('0' <= ch && ch <= '9')
        Simbolo.clase = DIGITO;
    else
        Simbolo.clase = ch;    
    
    Simbolo.representacion = ch;
}

int analiza_operador(Operador *oper)
{
    if(Simbolo.clase == '+')
    {
        *oper = '+'; consigue_sig_simbolo();
        return 1;
    }
    if(Simbolo.clase == '*')
    {
        *oper = '*'; consigue_sig_simbolo();
        return 1;
    }
    return 0;
}

int analiza_expresion(Expresion **expp)
{
    Expresion *exp = *expp = nueva_expresion();

    // En el caso de un digito.
    if(Simbolo.clase == DIGITO)
    {
        exp->tipo = 'D';
        exp->valor = Simbolo.representacion - '0';
        consigue_sig_simbolo();
        return 1;
    }

    // En caso de una expresión con parentesis.
    if(Simbolo.clase == '(')
    {
        exp->tipo = 'P';
        consigue_sig_simbolo();

        // Manejo de errores.
        if(!analiza_expresion(&exp->izquierda))
            Error("Expresión no encontrada");
        if(!analiza_operador(&exp->operador))
            Error("Operador no encontrado");
        if(!analiza_expresion(&exp->derecha))
            Error("Expresión no encontrada");
        if(Simbolo.clase != ')')
            Error("Parentesis de cierre ')' no encontrado");

        consigue_sig_simbolo();
        return 1;
    }

    // En caso de fallar en ambos intentos
    libera_expresion(exp);
    return 0;
}

int analisis_sintactico(AST_nodo **pcodigo)
{
    Expresion *exp;

    consigue_sig_simbolo();
    if(analiza_expresion(&exp))
    {
        if(Simbolo.clase != EoF)
            Error("Información basura encontrada al finalizar el programa.");
        *pcodigo = exp;
        return 1;
    }
    return 0;
}

Expresion* nueva_expresion(void){
    return (Expresion*)malloc(sizeof(Expresion));
}

void libera_expresion(Expresion *exp){
    free((void*)exp);
}