#pragma once
template<typename T>
class CNodoPila:public T{
    CNodoPila *sig;
public:
    template<typename... data>
    CNodoPila(CNodoPila *enlace, data... datos):sig(enlace),T(datos...){}
    void Relink(CNodoPila *enlace){sig=enlace;} //Redefine la coneccione de un nodo
    CNodoPila *getSig()const{return sig;}
};
template<typename T>
class Pila{
    int n;  //Numero de elementos en la pila
    CNodoPila<T> *inicio;
public:
    Pila():n(0),inicio(NULL){}//LARA
    int EstaVacia()const{   //Devuelve 1 si esta vacia, 0 si no //LARA
        return n==0 && inicio==NULL? 1 : 0;
    }
    template<typename... data> 
    int Push(data... datos){
        CNodoPila<T> *aux;    //Inserta un nodo con los datos dados al final de la pila
        aux = new CNodoPila<T>(inicio, datos...);
        if(aux==NULL) return -1;
        inicio=aux;
        n++;
        return 1;
    }
    T Pop(){
        T aux=*inicio;
        CNodoPila<T> *buff;
        buff=inicio;
        inicio=inicio->getSig();
        delete buff;
        n--;
        return aux;
    }
    T Top(){
	return *inicio;
    }

    int Recorrer()const{   //Imprime todos los elementos de la pila de inicio a fin //Hace falta??
        if (EstaVacia()) return -1;
        CNodoPila<T> nodo = *inicio;
        while(nodo.getSig() != NULL){
            nodo.Imprimir();
            nodo = *nodo.getSig();
        }
        nodo.Imprimir();
        return 1;
    }
  
    int Longitud()const{
        return n;
    }
    int Vaciar(){  //Elimina todo los nodos de la pila //LARA
        if (EstaVacia()) return 1;
        CNodoPila<T> *aux;
        while(inicio->getSig() != NULL){
            aux = inicio;
            inicio = inicio->getSig();
            delete aux;
        }
        delete inicio;
        inicio=NULL;
        n=0;
        return EstaVacia()? 1 : -1;
    }
};
