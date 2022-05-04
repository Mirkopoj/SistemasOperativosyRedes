#include <iostream>
#include "Buddy.h"
#include "Buddy_malloc.h"

#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

void bloque_libre::Imprimir(){
	std::cout<<adress<<", ";
}

//TABLA DE ALOCACIONES
//temporal para printear
char tabla[MEM] = {0};

void actualizar_tabla(int adr, int tam, char nom);
void tabla_init();

int main(){
	buddy_init();
	tabla_init();

	int ptr1, ptr2;

	ptr1 = buddy_malloc(14);
	actualizar_tabla(ptr1, 14, 'A');
	ptr2 = buddy_malloc(30);
	actualizar_tabla(ptr2, 30, 'B');
	buddy_free(ptr1);
	actualizar_tabla(ptr1, 14, '_');

	printf(FWHT("%c"),204);
	//IMPRIMIR ESTADO DE LA MEMORIA
	//temporal, está choto
	for(int i=0;i<16;i++){
		for(int j=0;j<32;j++){
			std::cout<<tabla[32*i+j];
		}
		std::cout<<std::endl;
	}
	for(int i=9;i>2;i--){
		for(int j=0;j<(MEM/(1<<i));j++){
			std::cout<<bit_map[i][j];
		}
		std::cout<<std::endl;
	}
	for(int i=9;i>=0;i--){
		std::cout<<i<<":";
		free_list[i].Recorrer();
		std::cout<<std::endl;
	}	
	return 0;
}

void tabla_init(){
	for(int i=0; i<MEM; i++){
		tabla[i]='_';
	}	
}

void actualizar_tabla(int adr, int tam, char nom){	//Pone el nombre del bloque alocado para dsp imprimirlo (solucion fea)
	for(int i=adr;i<(adr+tam);i++){
		tabla[i]=nom;
	}
}
