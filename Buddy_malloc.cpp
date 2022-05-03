#pragma once
#include "Buddy_malloc.h"
#include "Buddy.h"



int buddy_malloc(int size_to_alloc){
	//algo de bookkeeping antes o despues
	int adr;
	adr = alocar(size_to_alloc);
	mem_map[adr].tamaño=redondear(size_to_alloc);
	return adr;
}

void buddy_free(int adress){
	//Obtener tam del bookkeeping
	int tam = mem_map[adress].tamaño;
	liberar(adress, tam);
}
