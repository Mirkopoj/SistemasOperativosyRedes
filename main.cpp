#include <cstdio>
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
	std::cout<<" "<<adress<<",";
}

//TABLA DE ALOCACIONES
char tabla[MEM] = {0};

//Contadores de memoria
int MEM_RES=0;
int MEM_OCP=0;

void actualizar_tabla(int adr, int tam, char nom);
void tabla_init();
void print_structs();

int main(){
	buddy_init();
	tabla_init();

	int ptr1, ptr2, ptr3, ptr4, ptr5;

	print_structs();
	ptr1 = buddy_malloc(14);
	actualizar_tabla(ptr1, 14, 'A');
	print_structs();
	ptr2 = buddy_malloc(30);
	actualizar_tabla(ptr2, 30, 'B');
	print_structs();
	buddy_free(ptr1);
	actualizar_tabla(ptr1, 14, '_');
	print_structs();
	ptr1 = buddy_malloc(17);
	actualizar_tabla(ptr1, 17, 'C');
	print_structs();
	ptr3 = buddy_malloc(129);
	actualizar_tabla(ptr3, 129, 'D');
	print_structs();
	ptr4 = buddy_malloc(127);
	actualizar_tabla(ptr4, 127, 'E');
	print_structs();
	ptr5 = buddy_malloc(5);
	actualizar_tabla(ptr5, 5, 'F');
	print_structs();
	buddy_free(ptr2);
	actualizar_tabla(ptr2, 30, '_');
	print_structs();
	buddy_free(ptr1);
	actualizar_tabla(ptr1, 17, '_');
	print_structs();
	buddy_free(ptr3);
	actualizar_tabla(ptr3, 129, '_');
	print_structs();
	buddy_free(ptr4);
	actualizar_tabla(ptr4, 127, '_');
	print_structs();
	buddy_free(ptr5);
	actualizar_tabla(ptr5, 5, '_');
	print_structs();
	ptr1 = buddy_malloc(257);
	actualizar_tabla(ptr1, 257, 'G');
	print_structs();
	return 0;
}

void tabla_init(){
	for(int i=0; i<MEM; i++){
		tabla[i]='_';
	}	
}

void actualizar_tabla(int adr, int tam, char nom){	//Pone el nombre del bloque alocado para dsp imprimirlo
	if (nom!='_'){
		MEM_RES += tam;
		MEM_OCP += 1<<(redondear(tam));
	}else{
		MEM_RES -= tam;
		tam = 1<<(redondear(tam));
		MEM_OCP -= tam;
	}
	for(int i=adr;i<(adr+tam);i++){
		tabla[i]=nom;
	}
	for(int i=(adr+tam);i<(adr+(1<<redondear(tam)));i++){
		tabla[i]='#';
	}
}

void print_structs(){
	//IMPRIMIR ESTADO DE LA MEMORIA
	std::cout<<"MAPA DE MEMORIA"<<std::endl;
	printf(FWHT("%c"),201);
	for (int i = 0; i < 32; i++){
		printf(FWHT("%c"),205);	
	}
	printf(FWHT("%c\n"),187);
	for(int i=0;i<16;i++){
		printf(FWHT("%c"),186);
		for(int j=0;j<32;j++){
			if(tabla[32*i+j]=='_'){
				printf(FGRN("%c"),tabla[32*i+j]);
			}else if(tabla[32*i+j]=='#'){
				printf(FBLU("%c"),tabla[32*i+j]);
			}else{
				printf(FRED("%c"),tabla[32*i+j]);
			}
		}
		printf(FWHT("%c"),186);
		std::cout<<std::endl;
	}
	printf(FWHT("%c"),200);
	for (int i = 0; i < 32; i++){
		printf(FWHT("%c"),205);	
	}
	printf(FWHT("%c\n"),188);
	printf(FWHT("Espacio Total: %3d, "),MEM);
	printf(FWHT("Espacio Ocupado: %3d, "),MEM_OCP);
	printf(FRED("Espacio Reservado: %3d, "),MEM_RES);
	printf(FBLU("Espacio Desperdiciado: %3d, "),MEM_OCP-MEM_RES);
	printf(FGRN("Espacio Libre: %3d\n"),MEM-MEM_OCP);


	//IMPRIMIR BITMAP
	std::cout<<"BITMAP"<<std::endl;
	printf(FWHT("%c"),201); //primer
	printf(FWHT("%c%c%c%c"),205,205,205,203);
	for(int k=0;k<127;k++){
			printf(FWHT("%c"),205);
	}
	printf(FWHT("%c\n"),187);

	for(int i=9;i>3;i--){ //6
		int pad = 1<<(i-3);
		printf(FWHT("%c%-3d"),186,(1<<i));
		for(int j=0;j<(MEM/(1<<i));j++){
			printf("%-*c%-*d", pad, 186, pad, bit_map[i][j]);
		}
		printf(FWHT("%c\n"),186);
		printf(FWHT("%c"),204);
		printf(FWHT("%c%c%c%c"),205,205,205,206);
		for(int k=0;k<127;k++){
			printf(FWHT("%c"),(205-((k%pad)/(pad-1)*2)+(((k%(2*pad))/((2*pad)-1))*3)));
		}	
		printf(FWHT("%c\n"),185);
	}

	printf(FWHT("%c%-3d"),186,8);
	for(int j=0;j<(MEM/(1<<3));j++){ //ultima
		printf("%c%d", 186, bit_map[3][j]);
	}
	printf(FWHT("%c\n"),186);
	printf(FWHT("%c"),200);
	printf(FWHT("%c%c%c%c"),205,205,205,202);
	for(int k=0;k<127;k++){
		printf(FWHT("%c"),(205-(k%2)*3));
	}	
	printf(FWHT("%c\n"),188);

	//IMPRIMIR FREELIST
	std::cout<<"FREELIST"<<std::endl;
	for(int i=9;i>=0;i--){
		std::cout<<i<<":";
		free_list[i].Recorrer();
		std::cout<<std::endl;
	}
	getchar();
}
