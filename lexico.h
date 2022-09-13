// Análiis lexico; encabezados.
// Definimos algunas constantes.
// Lbos valores del 0 al 255 están reservados para los caracteres de código ASCII.

#define EoF    256
#define DIGITO 257

typedef int Operador;

typedef struct expresion
{
    char tipo;          // Dígito: 'D'; Parentesis: 'P'
    int valor;          // Para 'D'
    Operador operador;  // Para 'D'
    struct expresion *izquierda, *derecha; // Para 'P'
} Expresion;

typedef Expresion AST_nodo;     // AST:: Abstrac Sintax Tree. Raíz para el arbol de
                                // una expresion

typedef struct tipo_simbolo
{
    int clase;
    char representacion;
} Tipo_simbolo;

int es_caracter_presentacion(int ch);
void consigue_sig_simbolo(void);
int analiza_operador(Operador *oper);
int analiza_expresion(Expresion **expp);
int analisis_sintactico(AST_nodo **pcodigo);
Expresion* nueva_expresion(void);
void libera_expresion(Expresion *exp);