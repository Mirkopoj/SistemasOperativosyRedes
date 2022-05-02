#ifndef ARBOLBB_H_INCLUDED
#define ARBOLBB_H_INCLUDED

typedef int Tipo_Dato;

struct Nodo
{
    struct Nodo *izq;
    Tipo_Dato dato;
    char id;
    struct Nodo *der;
    int tamano;
};

typedef struct Nodo* Arbol_T;

Arbol_T CrearArbol(int t);

int InsertarElemento(Arbol_T *arbol, char ID, Tipo_Dato x);

void Imprimir(Arbol_T arbol);

int Contar_Desperdicio(Arbol_T arbol);

int Contar(Arbol_T arbol);

int Eliminar(Arbol_T *arbol, char ID);

#endif // ARBOLBB_H_INCLUDED
