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
char redondear(int tam);
void actualizar_bit_map_alloc(int adr, char exp);
char actualiar_bit_map_free(int adr, char exp);
int min (int a, int b);
void actualizar_free_list(int adr, char iter, char exp);
void liberar(int adr, char exp_asignado);
void buddy_init();

#include "Buddy.cpp"
