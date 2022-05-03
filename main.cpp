#include <iostream>
#include "Buddy.h"
#include "Buddy_malloc.cpp"
#include "Buddy_malloc.h"

void bloque_libre::Imprimir(){
	std::cout<<adress<<", ";
}

//TABLA DE ALOCACIONES
//temporal para printear
char tabla[MEM] = {0};

void actualizar_tabla(int adr, int tam, char nom);

int main(){
	buddy_init();
	
	struct b16{
		long double algo;
	};
	struct b32{
		long double algo0;
		long double algo1;
	};
	struct b16 *ptr1;
	struct b32 *ptr2;
	std::cout<<sizeof(struct b16 *)<<std::endl;
	std::cout<<sizeof(void *)<<std::endl;
	std::cout<<sizeof(long long int)<<std::endl;

	ptr1 = (struct b16 *)buddy_malloc(16);
	long long int a = (long long int)ptr1;
	long long int b = (long long int)&mem_arr;
	std::cout<<ptr1<<", "<<&mem_arr<<std::endl;
	std::cout<<a<<", "<<b<<", "<<b-a<<std::endl;
	actualizar_tabla((int)(mem_arr-(char *)ptr1), 16, 'A');
	ptr2 = (struct b32 *)buddy_malloc(32);
	actualizar_tabla((int)(mem_arr-(char *)ptr2), 32, 'B');
	buddy_free(ptr1);
	actualizar_tabla((int)(mem_arr-(char *)ptr1), 16, '-');

	//IMPRIMIR ESTADO DE LA MEMORIA
	//temporal, está choto
	for(int i=0;i<64;i++){
		std::cout<<i<<":"<<tabla[i]<<std::endl;
	}
	for(int i=9;i>2;i--){
		for(int j=0;j<(MEM/(1<<i));j++){
			std::cout<<bit_map[i][j];
		}
		std::cout<<std::endl;
	}
	for(int i=0;i<10;i++){
		std::cout<<i<<":";
		free_list[i].Recorrer();
		std::cout<<std::endl;
	}	
	return 0;
}

void actualizar_tabla(int adr, int tam, char nom){	//Pone el nombre del bloque alocado para dsp imprimirlo (solucion fea)
	for(int i=adr;i<(adr+tam);i++){
		tabla[i]=nom;
	}
}
