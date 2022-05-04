#include <iostream>
#include "Buddy.cpp"
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
	
	//IMPRIMIR ESTADO DE LA MEMORIA
	printf(FWHT("%c"),201);
	for (int i = 0; i < 32; i++){
		printf(FWHT("%c"),205);	
	}
	printf(FWHT("%c\n"),187);
	for(int i=0;i<16;i++){
		printf(FWHT("%c"),186);
		for(int j=0;j<32;j++){
			std::cout<<tabla[32*i+j];
		}
		printf(FWHT("%c"),186);
		std::cout<<std::endl;
	}
	printf(FWHT("%c"),200);
	for (int i = 0; i < 32; i++){
		printf(FWHT("%c"),205);	
	}
	printf(FWHT("%c\n"),188);

	//IMPRIMIR BITMAP
	printf(FWHT("%c"),201); //primer
	for(int k=0;k<127;k++){
			printf(FWHT("%c"),205);
	}
	printf(FWHT("%c\n"),187);

	for(int i=9;i>3;i--){ //6
		int pad = 1<<(i-3);
		for(int j=0;j<(MEM/(1<<i));j++){
			printf("%-*c%-*d", pad, 186, pad, bit_map[i][j]);
		}
		printf(FWHT("%c\n"),186);
		printf(FWHT("%c"),204);
		for(int k=0;k<127;k++){
			printf(FWHT("%c"),(205-((k%pad)/(pad-1)*2)+(((k%(2*pad))/((2*pad)-1))*3)));
		}	
		printf(FWHT("%c\n"),185);
	}

	for(int j=0;j<(MEM/(1<<3));j++){ //ultima
		printf("%c%d", 186, bit_map[3][j]);
	}
	printf(FWHT("%c\n"),186);
	printf(FWHT("%c"),200);
	for(int k=0;k<127;k++){
		printf(FWHT("%c"),(205-(k%2)*3));
	}	
	printf(FWHT("%c\n"),188);

	//IMPRIMIR FREELIST
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
