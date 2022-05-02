#include <iostream>
#ifdef __CLANG__
	#define NULL nullptr
#endif
#include "Pila.h"

#define MEM 512

class bloque_libre{
public:
	int adress;
	bloque_libre(int adr):adress(adr){};
};

//TABLA DE ALOCACIONES
char tabla[MEM] = {0};

//FREE LIST
Pila<bloque_libre> free_list[10];

//BIT MAP
bool *bit_map[10];

bool piso_0[MEM] = {0};
bool piso_1[MEM/2] = {0}; 
bool piso_2[MEM/4] = {0}; 
bool piso_3[MEM/8] = {0}; 
bool piso_4[MEM/16] = {0};
bool piso_5[MEM/32] = {0};
bool piso_6[MEM/64] = {0};
bool piso_7[MEM/128] = {0};
bool piso_8[MEM/256] = {0};
bool piso_9[MEM/512] = {0};

void alocar(char nombre, int tam);
int redondear(int tam);

int main(){
	free_list[9].Push(0);

	bit_map[0] = piso_0;
	bit_map[1] = piso_1;
	bit_map[2] = piso_2;
	bit_map[3] = piso_3;
	bit_map[4] = piso_4;
	bit_map[5] = piso_5;
	bit_map[6] = piso_6;
	bit_map[7] = piso_7;
	bit_map[8] = piso_8;
	bit_map[9] = piso_9;

	alocar('A', 14);
	alocar('B', 30);

	for(int i=0;i<MEM;i++){
		std::cout<<i<<":"<<tabla[i]<<std::endl;
	}
	return 0;
}

int redondear(int tam){
	int exponente = 1;
	while(tam != 1){
		tam >>= 1;
		exponente++;
	}
	return exponente;
}

void actualizar_tabla(int adr, int exp, char nom){
	for(int i=adr;i<(adr+(1<<exp));i++){
		tabla[i]=nom;
	}
}

void actualizar_bit_map(int adr, int exp){
	bit_map[exp][adr>>exp]=!bit_map[exp][adr>>exp];
	if(exp<8){
		actualizar_bit_map(adr, exp+1);
	}
	return;
}

void alocar(char nombre, int tam){
	int exp_asignado = redondear(tam);	
	int i = exp_asignado;
	while(free_list[i].EstaVacia()){
		i++;
		if(i>9) return;
	}
	bloque_libre asignacion = free_list[i].Pop();
	while(i != exp_asignado){
		i--;
		free_list[i].Push(asignacion.adress + (1<<i));
	}
	actualizar_bit_map(asignacion.adress, exp_asignado);
	actualizar_tabla(asignacion.adress, exp_asignado, nombre);
}
