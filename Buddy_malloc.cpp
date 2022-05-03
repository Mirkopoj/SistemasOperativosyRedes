#pragma once
#include "Buddy_malloc.h"
#include "Buddy.h"

//Memory descriptor
char mem_map[MEM];

int buddy_malloc(int size_to_alloc){
	//algo de bookkeeping antes o despues
	int adr;
	adr = alocar(size_to_alloc);
	mem_map[adr]=redondear(size_to_alloc);
	return adr;
}

void buddy_free(int adress){
	//Obtener tam del bookkeeping
	char exp = mem_map[adress];
	liberar(adress, exp);
}
