#pragma once
#include "Buddy_malloc.h"
#include "Buddy.h"

//Memory descriptor
char mem_map[MEM];

//"Memoria"
char mem_arr[MEM];

void *buddy_malloc(int size_to_alloc){
	//algo de bookkeeping antes o despues
	int adr;
	adr = alocar(size_to_alloc);
	mem_map[adr]=redondear(size_to_alloc);
	char *ret_adr = mem_map;
	ret_adr += adr;
	return (void *)ret_adr;
}

void buddy_free(void *adress){
	//Obtener tam del bookkeepinge
	int offset = (int)((char *)adress-mem_map);
	int tam = mem_map[offset];
	liberar(offset, tam);
}
