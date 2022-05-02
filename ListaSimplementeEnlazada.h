#pragma once
template<typename dato,typename... data>
dato principal(dato org, data... resto){    //Devuelve el primer dato de un paquete para poder manipularlo
    return org;                             //se puede overloadear si el dato de comparacion se calcula del paquete
}
template<typename T,typename... data>
    void init(T* initer, data... datos){
        T aux(datos...); //Setea todos los bytes "basura" de cada nodo en 0
        void *a;
        a=&aux;
        for(int i=0;i<sizeof(T);i++){
            *((char*)a+i)=0;
        }
        new(&aux)T(datos...);
        void *n=initer;
        for(int i=0;i<sizeof(T);i++){
            *((char*)n+i)=*((char*)a+i);
        }
    }
template<typename T>
class CNodo:public T{
    CNodo *sig;
public:
    template<typename... data>
    CNodo(CNodo *enlace, data... datos):sig(enlace),T(datos...){
        init<T>(this,datos...);
    }
    void Relink(CNodo *enlace){sig=enlace;} //Redefine la coneccione de un nodo
    CNodo *getSig()const{return sig;}
};
template<typename T>
class Lista{
    int n;  //Numero de elementos en la lista
    CNodo<T> *inicio;
    char op;//Operador de comparacion
    template<typename data,typename datb>
    bool comparar(data datoa,datb datob)const{
        switch(op){
            case '<':
                return datoa<datob? 1:0;
            case '>':
                return datoa>datob? 1:0;
            case '{':
                return datoa<=datob? 1:0;
            case '}':
                return datoa>=datob? 1:0;
            case '=':
                return datoa==datob? 1:0;
            case '!':
                return datoa!=datob? 1:0;
            default:
                std::cout<<"ERROR de comparacion defaulteo a '<'";
                return datoa<datob? 1:0;
            }
        }
    bool igual(T n1, T n2)const{
        void *a,*b; //Devulve 1 si dos nodos contienen los mismos datos, 0 si no
        a=&n1;      //Como los datos de un nodo se desconocen, compara byte a byte
        b=&n2;      //Esta funcion depende de la correcta inicializacion de los bytes "basura"
        for(int i=0;i<sizeof(T);i++) if(*((char*)a+i)!=*((char*)b+i)) return 0;
        return 1;
    } 
public:
    Lista():n(0),inicio(NULL),op('<'){}
    Lista(const char* opovr):n(0),inicio(NULL),op(*opovr){
        if(op!='<'&&op!='>'&&op!='{'&&op!='}'&&op!='='&&op!='!'){
            std::cout<<"Operador invalido default a '<'"<<std::endl;
            op='<';
        }
        switch(opovr[1]){   //Reduce la expercion del string de entrada
            case '\0':      //a un unico char que codifica el operador de comparacion
                break;
            case '=':
                switch(opovr[0]){
                    case '<':
                        op='{';
                        break;
                    case '>':
                        op='}';
                        break;
                    case '=':
                        break;
                    case '!':
                        break;
                    default:
                        std::cout<<"Operador invalido default a '<'"<<std::endl;
                        op='<';
                        break;
                }
                break;
            case '<':
                if(opovr[2]=='=') op='>';
                else op='}';
                break;
            case '>':
                if(opovr[2]=='=') op='<';
                else op='{';
                break;
            default:
                std::cout<<"Operador invalido default a '<'"<<std::endl;
                op='<';
                break;
        }
    }
    int EstaVacia()const{   //Devuelve 1 si esta vacia, 0 si no
        return n==0 && inicio==NULL? 1 : 0;
    }
    template<typename... data> 
    int insertarEn(int pos, data... datos){
        if(pos > n) return -1;      //Inserta un nodo con los datos dados
        CNodo<T> *aux;              //en la posicion data
        if(pos==0){
            aux = new CNodo<T>(inicio, datos...);
            if(aux==NULL) return -1;
            inicio = aux;
            n++;
            return 1;
        }
        CNodo<T> *buff;
        buff = inicio;
        for(int i=0;i<pos-1;i++) buff = buff->getSig();
        aux = new CNodo<T>(buff->getSig(), datos...);
        if(aux==NULL) return -1;
        buff->Relink(aux);
        n++;
        return 1;
    }
    template<typename... data> 
    int insertarEnFinal(data... datos){
        CNodo<T> *buff,*aux;    //Inserta un nodo con los datos dados al final de la lista
        buff = inicio;
        if(n==0){
            aux = new CNodo<T>(NULL, datos...);
            if(aux==NULL) return -1;
            inicio = aux;
            n++;
            return 1;    
        }
        for(int i=0;i<n-1;i++) buff = buff->getSig();
        aux = new CNodo<T>(buff->getSig(), datos...);
        if(aux==NULL) return -1;
        buff->Relink(aux);
        n++;
        return 1;
    }
    template<typename... data>          //Inserta un nodo con los datos dados de manera ordenada
    int insertar(data... datos){        //Ordena comparando el dato "principal" de cada nodo    
        CNodo<T> *aux;                  //Compara en funcion de la veriable "op"                
        if(EstaVacia() || comparar(principal(datos...),inicio->dato)){
            aux = new CNodo<T>(inicio, datos...);
            if(aux==NULL) return -1;
            inicio = aux;
            n++;
            return 1;
        }
        CNodo<T> *buff;
        buff = inicio;
        while(buff->getSig()!=NULL && comparar(buff->getSig()->dato,principal(datos...))) buff = buff->getSig();
        aux = new CNodo<T>(buff->getSig(), datos...);
        if(aux==NULL) return -1;
        buff->Relink(aux);
        n++;
        return 1;
    }
    int Recorrer()const{   //Imprime todos los elementos de la lista de inicio a fin
        if (EstaVacia()) return -1;
        CNodo<T> *nodo = inicio;
        while(nodo->getSig() != NULL){
            nodo->Imprimir();
            nodo = nodo->getSig();
        }
        nodo->Imprimir();
        return 1;
    }
    template<typename... data>
    int SuprimirDato(data... datos){    //Elimina todos los nodos que contengan los datos dados
        if (EstaVacia()) return -1;
        CNodo<T> *aux = inicio, *buff;
        T aux2(datos...);
        init<T>(&aux2, datos...);
        int borre_x = n;
        if (igual(aux2,(T)*(aux))) {
            buff = aux;
            aux = aux->getSig();
            delete buff;
            n--;
            inicio=aux;
            if (EstaVacia()) return borre_x != n? 1 : -1;
        }
        while (aux->getSig() != NULL) {
            if (igual(aux2,(T)*(aux->getSig()))){
                buff = aux->getSig()->getSig();
                delete aux->getSig();
                aux->Relink(buff);
                n--;
                continue;
            }aux=aux->getSig();
        }
        return borre_x != n? 1 : -1;
    }
    template<typename data>
    int SuprimirDatoPrincipal(data dato){    //Elimina todos los nodos que contenga dato principal
        if (EstaVacia()) return -1;
        CNodo<T> *aux = inicio, *buff;
        int borre_x = n;
        if (dato == aux->dato) {
            buff = aux;
            aux = aux->getSig();
            delete buff;
            n--;
            inicio=aux;
            if (EstaVacia()) return borre_x != n? 1 : -1;
        }
        while (aux->getSig() != NULL) {
            if (dato == aux->getSig()->dato){
                buff = aux->getSig()->getSig();
                delete aux->getSig();
                aux->Relink(buff);
                n--;
                continue;
            }
            if(aux->getSig()!=NULL) aux=aux->getSig();
        }
        return borre_x != n? 1 : -1;
    }

    int SuprimirNodo(int pos){  //Elimina el nodo en la posicion dada
        if(pos>=n) return -1;
        CNodo<T> *buff;
        buff=inicio; 
        if(pos==0){
            inicio=inicio->getSig();
            delete buff;
            n--;
            return 1;
        }
        CNodo<T> *buff2;
        for(int i=0;i<pos-1;i++) buff=buff->getSig();
        buff2=buff->getSig();
        buff->Relink(buff2->getSig());
        delete buff2;
        n--;
        return 1;
    }
    int Longitud()const{
        return n;
    }
    T *DevolverDatoPosicion(int pos)const{
        if(pos>=n) return NULL; //Devuelve un puntero al nodo en la posicion pedida
        CNodo<T>* buff;
        buff=inicio;
        for(int i=0;i<pos;i++) buff=buff->getSig();
        return buff;
    }
    template<typename data>
    T *DevolverNodoDatoPrincipal(data dato){    //Devuelve nodo que contenga dato principal
        if (EstaVacia()) return NULL;
        CNodo<T> *aux = inicio;
        if (dato == aux->dato){
            return aux;
        }
        while (aux->getSig() != NULL){
            aux=aux->getSig();
            if (dato == aux->dato){
                return aux;
            }
        } 
        return NULL;
    }
    T Pop(){    //Devuelve el primer nodo y lo elimina, Insegura (chequear que no este vacia)
         CNodo<T> *aux = inicio;
		   CNodo<T> buf = *inicio;
			inicio = aux->getSig();
			delete aux;
			return buf;
    }
    template<typename data>
    T PopNodoDatoPrincipal(data dato){    //Devuelve nodo que contenga dato principal y lo elimina, Insegura (chequear que no este vacia)
        CNodo<T> *aux = inicio;
		  CNodo<T> buf = *inicio;
        if (dato == aux->dato){
			   inicio = aux->getSig();
				delete aux;
				return buf;
        }
		  CNodo<T> *bufptr;
        while (aux->getSig() != NULL){
            if (dato == aux->getSig()->dato){
					 bufptr = aux->getSig();
					 aux->Relink(aux->getSig()->getSig());
					 buf = *bufptr;
					 delete bufptr;
                return buf;
            }
            aux=aux->getSig();
        } 
    }
    template<typename... data>
    int DevolverPosicionDato(int pos,data... datos)const{
        if(pos>=n) return -1;                       //Devulve la posicion del primer nodo que contiene los datos dados
        CNodo<T> buff(NULL, datos...);              //busca entre la posicion dada y el final inclusive               
        buff=*inicio;                               //si pos=0, el intervalo de busqueda es la lista entera           
        for(int i=0;i<pos;i++) buff=*buff.getSig(); //el intervalo de busqueda es [pos,fin]                           
        T aux(datos...);
        init<T>(&aux,datos...);
        for(int i=pos;i<n-1;i++){
            if(igual(aux,(T)buff)) return i;
            buff=*buff.getSig();
        }
        if(igual(aux,(T)buff)) return n;
        return -1;
    }
    template<typename data>
    int DevolverPosicionDatoPrincipal(data dato){    //Devuelve pos que contenga dato principal
        if (EstaVacia()) return -1;
        CNodo<T> *aux = inicio;
        if (dato == aux->dato){
            return 0;
        }
        int p=0;
        while (aux->getSig() != NULL){
            aux=aux->getSig();
            p++;
            if (dato == aux->dato){
                return p;
            }
        } 
        return -1;
    }    
        int Vaciar(){  //Elimina todo los nodos de la lista
        if (EstaVacia()) return 1;
        CNodo<T> *aux;
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
