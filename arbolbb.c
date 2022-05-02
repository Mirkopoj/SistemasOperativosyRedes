#include<stdio.h>
#include<stdlib.h>
#include"arbolbb.h"

Arbol_T CrearArbol(int t){
    Arbol_T a;
    a=(Arbol_T)malloc(sizeof(struct Nodo));
    if(a==NULL){
        printf ("Error en la alocacion de memoria");
        exit(-1);
    }
    a->der=NULL;
    a->izq=NULL;
    a->dato=0;
    a->tamano=t;
    printf("Crear nodo %d\n",t);
    return a;
}
/*
Crea un nuevo nodo con tamano t
Todos los nodos son a la vez raiz de su propio subarbol
*/

int InsertarElemento(Arbol_T *arbol, char ID, Tipo_Dato x ){
    if ((*arbol)->id!='\0')
    {
        return 0;
    }
    else if (x<(*arbol)->tamano&&x<=((*arbol)->tamano)/2)
    {
        if ((*arbol)->izq==NULL)
        {
            (*arbol)->der=CrearArbol(((*arbol)->tamano)/2);
            (*arbol)->izq=CrearArbol(((*arbol)->tamano)/2);
            return InsertarElemento(&(*arbol)->izq,ID,x);
        }
        return (InsertarElemento(&(*arbol)->izq,ID,x))? 1:InsertarElemento(&(*arbol)->der,ID,x);
    }
    else if ((*arbol)->izq==NULL)
    {
        (*arbol)->dato=x;
        (*arbol)->id=ID;
        printf("Alocacion %c\n",ID);
        return 1;
    }
    else
        return 0;
}
/*
Si encuentra lugar define los valores del nodo como ocupados
Cuando el nodo libre le queda grande hace la division creando dos nuevos nodos de la mitad de tamano
Inserta preferentemente en la izquierda
Solo puede asignarse el valor en un nodo hoja, un nodo sin hijos
*/


void Imprimir(Arbol_T arbol){
    if (arbol->der!=NULL&&arbol->izq!=NULL){
        Imprimir(arbol->izq);
        Imprimir(arbol->der);
    }
    else
    {
        if (arbol->id!='\0')
            printf ("|%c=%dKB|",arbol->id,arbol->dato);
        else
            printf ("|Espacio libre=%d|",arbol->tamano);
    }
}
/*
Solo imprime los nodos hoja, los cuales pueden estar ocupados o libres
*/

int Contar_Desperdicio(Arbol_T arbol){
    if (arbol->der!=NULL)
        return Contar_Desperdicio(arbol->izq) + Contar_Desperdicio(arbol->der);
    else if (arbol->id!='\0')
        return (arbol->tamano-arbol->dato);
    else
        return 0;
}
/*
Retorna la suma de todos los desperdicios individuales
*/

int Contar(Arbol_T arbol){
    if (arbol->der!=NULL)
        return Contar(arbol->izq) + Contar(arbol->der);
    else if (arbol->id!='\0')
        return arbol->tamano;
    else
        return 0;
}
/*
Retorna la suma de todos los espacios ocupados
*/

int Eliminar(Arbol_T *arbol, char ID){
    int b=0;
    if ((*arbol)->id==ID)
    {
        (*arbol)->dato=0;
        (*arbol)->id='\0';
        printf("Liberacion de espacio de memoria de %c\n",ID);
        return 1;
    }
    else if ((*arbol)->izq==NULL||(*arbol)->der==NULL)
    {
        return 0;
    }
    else if ((*arbol)->izq->id==ID)
    {
        (*arbol)->izq->id='\0';
        (*arbol)->izq->id=0;
        printf("Liberacion de espacio de memoria de %c\n",ID);
        if ((*arbol)->der->id=='\0'&&(*arbol)->der->izq==NULL)
        {
            free((*arbol)->izq);
            free((*arbol)->der);
            (*arbol)->izq=NULL;
            (*arbol)->der=NULL;
            printf("Nuevos buddies agrupados\n");
        }
        return 1;
    }
    else if ((*arbol)->der->id==ID)
    {
        (*arbol)->der->id='\0';
        (*arbol)->der->id=0;
        printf("Liberacion de espacio de memoria de %c\n",ID);
        if ((*arbol)->izq->id=='\0'&&(*arbol)->izq->izq==NULL)
        {
            free((*arbol)->izq);
            free((*arbol)->der);
            (*arbol)->izq=NULL;
            (*arbol)->der=NULL;
            printf("Nuevos buddies agrupados\n");
        }
        return 1;
    }
    else
    {
        b=Eliminar(&((*arbol)->izq),ID);
        if(!b);
            b=Eliminar(&((*arbol)->der),ID);
        if ((*arbol)->izq->izq==NULL&&(*arbol)->der->izq==NULL&&(*arbol)->izq->id=='\0'&&(*arbol)->der->id=='\0')
        {
            free((*arbol)->izq);
            free((*arbol)->der);
            (*arbol)->izq=NULL;
            (*arbol)->der=NULL;
            printf("Nuevos buddies agrupados\n");
        }
        return b;
    }
}
/*
Libera el espacio ocupado por el ID especificado, si es que el ID esta asignado a algun lugar
Luego de liberar se fija si puede reagrupar nuevos buddies
El free() solo se usa en caso de que sea posible reagrupar, si no es posible dejo los nodos disponibles para asignar
*/
