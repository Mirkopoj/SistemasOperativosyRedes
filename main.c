#include<stdio.h>
#include<stdlib.h>
#include"arbolbb.h"

#define N 512

int main()
{
    Arbol_T a;
    a=CrearArbol(N);
    InsertarElemento(&a,'A',128);

    InsertarElemento(&a,'C',250);
    InsertarElemento(&a,'D',30);
    InsertarElemento(&a,'B',15);
    Imprimir(a);
    printf("\nMemoria usada = %d",Contar(a));
    printf("\nMemoria libre = %d",N-Contar(a));
    printf("\nMemoria desperdiciada = %d\n",Contar_Desperdicio(a));
    Eliminar(&a,'C');
    Eliminar(&a,'B');
    Eliminar(&a,'D');
    Eliminar(&a,'A');
    Imprimir(a);
    return 0;
}
