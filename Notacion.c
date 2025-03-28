#include "funciones.h"

void push(Pila *p, char val) {
    if (p->top < MAX_STACK - 1) {
        p->data[++(p->top)] = val;
    }
}

char pop(Pila *p) {
    if (p->top >= 0) {
        return p->data[(p->top)--];
    }
    return '\0';
}

char peek(Pila *p) {
    if (p->top >= 0) {
        return p->data[p->top];
    }
    return '\0';
}

int esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int JERARQUIA(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void CONVERSION(const char *expresion, char *postfija) {
    char stack[MAX_STACK];
    int top = -1, j = 0;

    for (int i = 0; expresion[i] != '\0'; i++) {
        if (isdigit(expresion[i])) {

            while (isdigit(expresion[i])) {
                postfija[j++] = expresion[i++];
            }
            postfija[j++] = ' ';
            i--;
        } else if (isalpha(expresion[i])) {
            postfija[j++] = expresion[i];
            postfija[j++] = ' ';
        } else if (expresion[i] == '(') {
            stack[++top] = expresion[i];
        } else if (expresion[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                postfija[j++] = stack[top--];
                postfija[j++] = ' ';
            }
            top--;
        } else if (esOperador(expresion[i])) {
            while (top != -1 && JERARQUIA(stack[top]) >= JERARQUIA(expresion[i])) {
                postfija[j++] = stack[top--];
                postfija[j++] = ' ';
            }
            stack[++top] = expresion[i];
        }
    }

    while (top != -1) {
        postfija[j++] = stack[top--];
        postfija[j++] = ' ';
    }

    postfija[j] = '\0';
}

Datos LEER_ARCHIVO(const char *nombreArchivo) {
    Datos datos;
    datos.num_vars = 0;
    datos.expresion[0] = '\0';

    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char linea[MAX_EXPR];
    while (fgets(linea, sizeof(linea), archivo)) {
        if (strchr(linea, '=')) {
            char var;
            int valor;
            if (sscanf(linea, " %c = %d", &var, &valor) == 2) {
                datos.variables[datos.num_vars].nombre = var;
                datos.variables[datos.num_vars].valor = valor;
                datos.num_vars++;
            }
        } else if (strlen(linea) > 1) {
            strcpy(datos.expresion, linea);
            datos.expresion[strcspn(datos.expresion, "\n")] = '\0';
        }
    }
    fclose(archivo);
    return datos;
}

int EVALUACION_POSTFIJA(const char *postfija, Datos *datos) {
    int pila[MAX_STACK], top = -1;
    int i = 0;
    
    while (postfija[i] != '\0') {
        if (isdigit(postfija[i])) {
            int num = 0;
            while (isdigit(postfija[i])) {
                num = num * 10 + (postfija[i] - '0');
                i++;
            }
            pila[++top] = num;
        } else if (isalpha(postfija[i])) {
            for (int j = 0; j < datos->num_vars; j++) {
                if (datos->variables[j].nombre == postfija[i]) {
                    pila[++top] = datos->variables[j].valor;
                    break;
                }
            }
        } else if (esOperador(postfija[i])) {
            if (top < 1) {
                printf("Error: Expresión postfija inválida\n");
                exit(EXIT_FAILURE);
            }
            int b = pila[top--];
            int a = pila[top--];

            switch (postfija[i]) {
                case '+': pila[++top] = a + b; break;
                case '-': pila[++top] = a - b; break;
                case '*': pila[++top] = a * b; break;
                case '/': 
                    if (b == 0) {
                        printf("Error: No se puede dividir entre cero\n");
                        exit(EXIT_FAILURE);
                    }
                    pila[++top] = a / b; 
                    break;
            }
        }
        i++;
    }
    return pila[top];
}