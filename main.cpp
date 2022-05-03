#include <iostream>
#include "Buddy.h"
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

	int ptr1, ptr2;

	for(int i=0; i<MEM;i++){
		mem_map[i].proceso='-';
		//printf("%c \n",tabla[i]);
	}

	ptr1 = buddy_malloc(14);
	actualizar_tabla(ptr1, 14, 'A');
	ptr2 = buddy_malloc(30);
	actualizar_tabla(ptr2, 30, 'B');
	buddy_free(ptr1);
	actualizar_tabla(ptr1, 14, '-');

	//IMPRIMIR ESTADO DE LA MEMORIA
	//temporal, está choto
	for(int i=0;i<64;i++){
		std::cout<<i<<":"<<mem_map[i].proceso<<std::endl;
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
	tam=1<<mem_map[adr].tamaño;
	for(int i=adr;i<(adr+tam);i++){
		mem_map[i].proceso=nom;
	}
}
