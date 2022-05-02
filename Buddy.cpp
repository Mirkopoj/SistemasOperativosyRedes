#ifdef __CLANG__
	#define NULL nullptr
#endif

#include <iostream>
#include "ListaSimplementeEnlazada.h"

#define Push(X) insertarEn(0,X) 
#define adress dato

//Nº maximo de marcos en memoria
#define MEM 512

//Estructura para la FREE LIST
class bloque_libre{
public:
	int adress;
	bloque_libre(int adr):adress(adr){};
	void Imprimir(){
		std::cout<<adress<<", ";
	}
};

//TABLA DE ALOCACIONES
//temporal para printear
char tabla[MEM] = {0};

//FREE LIST
Lista<bloque_libre> free_list[10];

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

//PROTOTIPOS
void alocar(char nombre, int tam);
int redondear(int tam);
void actualizar_tabla(int adr, int exp, char nom);
void actualizar_bit_map_alloc(int adr, int exp);
int actualiar_bit_map_free(int adr, int exp);
int min (int a, int b);
void actualizar_free_list(int adr, int iter, int exp);
void liberar(int adr, int tam);

int main(){
	//INICIALIZACION
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
	//FIN INICIALIZACION

	alocar('A', 14);
	alocar('B', 30);
	liberar(0,14);

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

int redondear(int tam){	//Devuelve el exponente de la potencia de 2 inmediatamente superior
	tam--;
	int exponente = 0;
	while(tam != 0){
		tam >>= 1;
		exponente++;
	}
	return exponente;
}

void actualizar_tabla(int adr, int exp, char nom){	//Pone el nombre del bloque alocado para dsp imprimirlo (solucion fea)
	for(int i=adr;i<(adr+(1<<exp));i++){
		tabla[i]=nom;
	}
}

void actualizar_bit_map_alloc(int adr, int exp){ //Hace un toggle al bit de la pareja especificada, y propaga hacia arriba
	int bit = adr>>exp;
	bit_map[exp][bit]=!bit_map[exp][bit];
	if(bit_map[exp][bit]==1 && exp<9){
		actualizar_bit_map_alloc(adr, exp+1);
	}
	return;
}

int actualiar_bit_map_free(int adr, int exp){
	int ret = 1;
	int bit = adr>>exp;
	bit_map[exp][bit]=!bit_map[exp][exp];
	if(bit_map[exp][bit]==0 && exp<9){
		ret += actualiar_bit_map_free(adr, exp+1);
	}
	return ret;
}

int min (int a, int b){
	return (a<b)? a:b;
}

void actualizar_free_list(int adr, int iter, int exp){
	int buddy_adr;
	for(int i=0;i<iter;i++){
		buddy_adr = adr ^ (1<<(exp+i));
		free_list[exp+i].SuprimirDatoPrincipal(buddy_adr);
		adr = min(adr, buddy_adr);
	}
	free_list[exp+iter].Push(adr);
}

void alocar(char nombre, int tam){ //Busca en la FREE LIST donde alocar, y dsp actualiza el bit_map y la tabla para imprimir
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
	actualizar_bit_map_alloc(asignacion.adress, exp_asignado);
	actualizar_tabla(asignacion.adress, exp_asignado, nombre);
}

void liberar(int adr, int tam){
	int exp_asignado = redondear(tam);
	int merge_count;
	merge_count = actualiar_bit_map_free(adr, exp_asignado);
	actualizar_free_list(adr, merge_count, exp_asignado);
	actualizar_tabla(adr, exp_asignado, '\0');
}
