#pragma once

//Nº maximo de marcos en memoria
#define MEM 512

#define adress dato

//Estructura para la FREE LIST
class bloque_libre{
public:
	int adress;
	bloque_libre(int adr):adress(adr){};
	void Imprimir();
};

//PROTOTIPOS
int alocar(int tam);
int redondear(int tam);
void actualizar_bit_map_alloc(int adr, int exp);
int actualiar_bit_map_free(int adr, int exp);
int min (int a, int b);
void actualizar_free_list(int adr, int iter, int exp);
void liberar(int adr, int tam);
void buddy_init();

#include "Buddy.cpp"
