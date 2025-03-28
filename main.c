#include "funciones.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <archivo.txt>\n", argv[0]);
        return 1;
    }
    
    Datos datos = LEER_ARCHIVO(argv[1]);
    printf("Expresión infija: %s\n", datos.expresion);
    
    char postfija[MAX_EXPR];
    CONVERSION(datos.expresion, postfija);
    printf("Expresión postfija: %s\n", postfija);
    
    int resultado = EVALUACION_POSTFIJA(postfija, &datos);
    printf("Resultado: %d\n", resultado);
    
    return 0;
}