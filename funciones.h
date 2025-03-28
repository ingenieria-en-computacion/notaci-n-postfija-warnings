#ifndef __FUNCIONES_H__
#define __FUNCIONES_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VARS 100
#define MAX_EXPR 256
#define MAX_STACK 256
#define esNumero(c) (isdigit(c) || isalpha(c))
#define esEspacio(c) (isspace(c))

typedef struct {
    char nombre;
    int valor;
} Variable;

typedef struct {
    Variable variables[MAX_VARS];
    int num_vars;
    char expresion[MAX_EXPR];
} Datos;

typedef struct {
    char data[MAX_STACK];
    int top;
} Pila;

void push(Pila *p, char val);
char pop(Pila *p);
char peek(Pila *p);
int esOperador(char c);
int JERARQUIA(char op);

Datos LEER_ARCHIVO(const char *nombreArchivo);
void CONVERSION(const char *expresion, char *postfija);
int EVALUACION_POSTFIJA(const char *postfija, Datos *datos);

#endif