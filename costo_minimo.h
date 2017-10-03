//===-------------- costo_minimo.h ---------------------------------------===//
//
// Autor: Rafael Fernando Garcia Sagastume.
// Escuintla, Guatemala
//
// La libreria contiene los procesos necesarios para poder generar la insercion
// a la matriz para el metodo multiplicadores, esta costa de ofertas y demandas
//
// Librerias principales para el uso:
//
//		insert_fila_nodo(1,5,&pt1);  [Global struture => pt1]
//		close_line(1, pt1); //cierre de linea de insercion
//
//		inserta_demanda(35, &l_Demanda);
//		inserta_oferta(30, &l_Oferta);
//
//		ver_n(pt1);
//		Operacion_costo_minimo(pt1, l_Oferta, l_Demanda);
//		v_cost_min();
//
// compilacion: gcc costo_minimo.c -o costo_minimo
//
// Copyright © 2017 Rafael Fernando Garcia Sagastume.
//===----------------------------------------------------------------------===//


#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct nodo{ // estuctura de los ndos de la matriz Multiplicadores
	int status; //[solo sera para el primer nodo] [0 // cerrado || 1 // abierto]
	int fila, sts_sp;  // sts_sp  ?? bloqueo special
	int base, expo; // haran las multiplicaciones de base con exponente
	int pase_ordenamiento; // decide quien es el que pasara primero a operar la demanda / oferta
	struct nodo *sig, *abj; // enlace de nodos
};

// raiz de la matriz del nodo
struct nodo *pt1=0; // ??  matriz de datos ??
struct nodo *l_Demanda=0;  //?? contendra las demandas
struct nodo *l_Oferta=0; // ?? contendra las ofertas

// variables de la consola   
int v_consola=0, cantidad_nodos_listas=0; // la cantidad_nodos_listas cuenta los nodos creados en las listas y lo reduce al dar el pase
int f, nf=0, c, nc=0, d, nd=0, o, no;
int control_demanda=0, control_oferta=0;
int numero_pase=1; // leda el el orden de pase para el nodo que sera operado
int numero_nodos_matriz=0; // contendra el valor inicial de cantidad_nodos_lista pero sera una constante del total nodos encontrados
//--------------------------------------------

int ciclos=0;
//prototipos
void insert_fila_nodo(int f, int b, /*int e*/ struct nodo **rn);
void insert_new_fila_nodo(int f, int b, /*int e*/ struct nodo **rn);
void close_line(int line, struct nodo *rn);
void ver_n(struct nodo *rn);
void ver_Demanda_Oferta(struct nodo *raiz_demanda, struct nodo *raiz_oferta);
struct nodo *inserta_oferta(int o, struct nodo **rai_oferta);
struct nodo *inserta_demanda(int d, struct nodo **raiz_demanda);
void block_nodos_off(struct nodo *raiz_matriz , struct nodo *raiz_oferta, struct nodo *raiz_demanda);
void Operacion_costo_minimo(struct nodo *raiz_matriz , struct nodo *raiz_oferta, struct nodo *raiz_demanda); // ordena los pases de nodos
void opera_costo_minimo(struct nodo *raiz_matriz , struct nodo *raiz_oferta, struct nodo *raiz_demanda); // da el valor del exponente costo_minimo
void v_cost_min(); // da el valor del costo minimo


// ---------------------------- crea los nodos -------------------------------------------
struct nodo *crear_nodo(int f, int b, /*int e*/ struct nodo *rn){
	rn = (struct nodo *)malloc(sizeof(struct nodo)); // aparta la memoria del nodo
	rn->fila=f;
	rn->base=b;
	rn->status=0; // ndo abierto
	//rn->expo=e;   [pendiente del primer resultado]
	rn->sig=rn->abj=NULL;
	return rn; // retorna el puntero del ndo creado
}

// fila 23 45 12 45 [67--> Oferta???] 
// 		45 67 23 21  [Opciones de Demanda?????]
// inserta nodos en la filas y nuevas filas------------------------------------------------
void insert_fila_nodo(int f, int b, /*int e*/ struct nodo **rn){
	
	if(!(*rn)){
		cantidad_nodos_listas++; // cuentas los nodos insertados en listas
		(*rn)=crear_nodo(f, b, (*rn));
	}else{
		if((*rn)->status!=1){
			insert_fila_nodo(f, b, &(*rn)->sig);
		}else{
			insert_new_fila_nodo(f, b, &((*rn)->abj));
		}
	}

}

void insert_new_fila_nodo(int f, int b, /*int e*/ struct nodo **rn){
	if(!(*rn)){
		cantidad_nodos_listas++; // cuentas los nodos insertados en listas
		(*rn)=crear_nodo(f, b, (*rn));
	}else{
		if((*rn)->status!=1){
			insert_fila_nodo(f, b, &(*rn)->sig);
		}else{
			insert_new_fila_nodo(f, b, &((*rn)->abj));
		}
	}
}
//--------------------------------------------------------------------------------------------

void close_line(int line, struct nodo *rn){ // cierra las inserciones en la fila de la matriz
	struct nodo *rf;
	rf = rn;
	int ln=1;
	while(rf!=NULL){
		if(ln==line){
			rf->status=1;
			break;
		}else{
			rf=rf->abj;
			ln++;
		}
	}
}

void ver_n(struct nodo *rf){ // muestra la fila de inserciones
	struct nodo *rf1=rf;
	struct nodo *rf2=rf;
	int fila=1;
	while(rf1!=NULL){
		printf("[\t%d", (rf1)->base);printf(":%d",rf1->expo);printf("\t]");
		rf2=rf1->sig;
		while(rf2!=NULL){
			printf("[\t%d", (rf2)->base);printf(":%d",rf2->expo);printf("\t]");
			rf2=rf2->sig;
		}
		rf1=rf1->abj;printf("\n");
		fila++;
	}

}

// ------------------------------ inserta las demandas / Ofertas----------------------------------
struct nodo *inserta_demanda(int d, struct nodo **raiz_demanda){
	if(!(*raiz_demanda)){
		(*raiz_demanda)=crear_nodo(1, d, (*raiz_demanda));
	}else{
		inserta_demanda(d, &((*raiz_demanda)->sig));
	}

	return *raiz_demanda;
}

struct nodo *inserta_oferta(int o, struct nodo **raiz_oferta){
	if(!(*raiz_oferta)){
		(*raiz_oferta)=crear_nodo(1, o, (*raiz_oferta));
	}else{
		inserta_oferta(o, &((*raiz_oferta)->sig));
	}

	return *raiz_oferta;
}

void ver_Demanda_Oferta(struct nodo *raiz_demanda, struct nodo *raiz_oferta){
	printf("-----------Oferta----------\n");
	while(raiz_oferta!=NULL){
		printf("[\t%d", raiz_oferta->base );printf("\t]");
		raiz_oferta=raiz_oferta->sig;
	}
	printf("\n----------Demanda----------\n");
	while(raiz_demanda!=NULL){
		printf("[\t%d", raiz_demanda->base);printf("\t]");
		raiz_demanda=raiz_demanda->sig;
	}
	printf("\n");

}



// ------------------------------------------------------- Operacion Costo Minimo ---------------------------------------------------------

void Operacion_costo_minimo(struct nodo *raiz_matriz , struct nodo *raiz_oferta, struct nodo *raiz_demanda){

	// 	apuntara al menor // recorre la fila // recorre la siguiente lista
	struct nodo *ptr_menor, *busca_menor, *ptr_baja, *ptr_menor_matriz;
	// toma la direccion de la raiz de la matriz de datos
	ptr_baja = busca_menor = ptr_menor_matriz = ptr_menor = raiz_matriz; // raiz matriz = la raiz de todas las listas

while(ptr_baja!=NULL){
	busca_menor=ptr_baja;
	while(busca_menor!=NULL){//busca libre

		if(busca_menor->sts_sp==0){
			ptr_menor=busca_menor;
			break;
		}
		busca_menor=busca_menor->sig;
	}
	ptr_baja=ptr_baja->abj;
}

// retorna los punteros a raiz
busca_menor=ptr_baja=raiz_matriz;


	while(ptr_baja!=NULL){
	busca_menor=ptr_baja;
		while(busca_menor!=NULL){

			if(ptr_menor->base > busca_menor->base && (busca_menor->sts_sp==0)){
				ptr_menor=busca_menor;
			}

			busca_menor=busca_menor->sig;
		}
		ptr_baja=ptr_baja->abj;
	}
	ptr_menor->sts_sp=1;
	ptr_menor->pase_ordenamiento=numero_pase;
	numero_pase++;
	cantidad_nodos_listas--;

	printf("Nodo: %d  pase: %d\n", ptr_menor->base, ptr_menor->pase_ordenamiento);

	if(cantidad_nodos_listas > 0){
		Operacion_costo_minimo(raiz_matriz ,raiz_oferta, raiz_demanda);
	}else{
		numero_nodos_matriz = numero_pase; // tendra el valor total de los nodos
		numero_pase=1; // recetea el numero de pase
		opera_costo_minimo(raiz_matriz , raiz_oferta, raiz_demanda);
	}
// fin del metodo operacion
}


// buscara el nodo con el pase menor al mayor de la matriz para disponer 
//de la demanda/ oferta que llevara el exponente del nodo
void opera_costo_minimo(struct nodo *raiz_matriz , struct nodo *raiz_oferta, struct nodo *raiz_demanda){
	
	int posicion_demanda=0, posicion_oferta=0; // que oferta y que demanda gastara
	int busca_posicion_demanda=1, busca_posicion_oferta=1; //auxiliares para buscar las posiciones demanda/oferta

	// 	apuntara al menor del pase // recorre la fila // recorre la siguiente lista
	struct nodo *ptr_menor, *busca_menor, *ptr_baja, *ptr_menor_matriz;
	// toma la direccion de la raiz de la matriz de datos
	ptr_baja = busca_menor = ptr_menor_matriz = ptr_menor = raiz_matriz; // raiz matriz = la raiz de todas las listas


	struct nodo *ptr_busca_demanda, *ptr_busca_oferta;
	ptr_busca_oferta = raiz_oferta; // se posiciona en la raiz de la oferta
	ptr_busca_demanda = raiz_demanda; // se posiciona en la raiz de la demanda


	while(ptr_baja!=NULL){
		busca_menor = ptr_baja; // se posiciona en cada linea para buscar el pase menor
		posicion_oferta++; // aumenta si baja de lista
		while(busca_menor!=NULL){
			posicion_demanda++; //aumenta si recorre un nodo de la lista
			if(busca_menor->pase_ordenamiento == numero_pase){ // pase_ordenamiento se asigno anteriormente al nodo
				//printf("Nodo encontrado: %d\n", busca_menor->base);
				printf("Posicion de la oferta: %d\n", posicion_oferta);
				printf("Posicion de la demanda: %d\n", posicion_demanda);
				//break;

				while(posicion_demanda != busca_posicion_demanda){ // encuentro la posicion de la demanda
					busca_posicion_demanda++;
					if(ptr_busca_demanda->sig != NULL){
						ptr_busca_demanda = ptr_busca_demanda->sig;
					}else {
						printf("El numero del nodo de la Matriz Supera al Numero de Nodo de la Demanda\n");
						exit(0);
					}
				}

				while(posicion_oferta != busca_posicion_oferta){ // encentro la posicion de la oferta
					busca_posicion_oferta++;
					if(ptr_busca_oferta->sig != NULL){
						ptr_busca_oferta = ptr_busca_oferta->sig;
					}else {
						printf("El numero de lista de la Matriz Supera al Numero de Nodo de la Oferta\n");
						exit(0);
					}
				}

				printf("Nodo encontrado: %d\n", busca_menor->base);
				printf("Demanda: %d\n", ptr_busca_demanda->base);
				printf("Oferta: %d\n", ptr_busca_oferta->base);
				//break;

				if(ptr_busca_oferta->base < ptr_busca_demanda->base){
					if(ptr_busca_oferta->base!=0){
						busca_menor->expo= ptr_busca_oferta->base;
					}
					ptr_busca_demanda->base = ptr_busca_demanda->base - ptr_busca_oferta->base;
					ptr_busca_oferta->base = 0;
				}else if(ptr_busca_oferta->base > ptr_busca_demanda->base){
					
					if(ptr_busca_demanda->base!=0){
						busca_menor->expo=ptr_busca_demanda->base;
					}

					ptr_busca_oferta->base=ptr_busca_oferta->base - ptr_busca_demanda->base;
					ptr_busca_demanda->base = 0;
				}else if(ptr_busca_oferta->base == ptr_busca_demanda->base){
					busca_menor->expo=ptr_busca_demanda->base;
					ptr_busca_oferta->base = 0;
					ptr_busca_demanda->base = 0;
				}

				
				printf("-------------------------------------------------------------- \n");
				//break;
				
			}

			busca_menor = busca_menor->sig; // recorre la lista completa de su determinando nivel
		}

		ptr_baja = ptr_baja->abj;
		ptr_busca_oferta = raiz_oferta; // se posiciona en la raiz de la oferta
		ptr_busca_demanda = raiz_demanda; // se posiciona en la raiz de la demanda
		posicion_demanda=0;
		//posicion_oferta=0;
	}

	numero_pase++; // busca el sigiente nodo [del menor al mayor]
	if(numero_nodos_matriz != numero_pase){ // hasta que alcance los nodos totales
		opera_costo_minimo(raiz_matriz , raiz_oferta, raiz_demanda); // mando las raices nuevamente
	}
	

}
//----------------------------------------------------------------------------------------------------------------------------------------
// entrega el resultado de la matriz 

void v_cost_min(){

	struct nodo *ndo_res_matriz, *ndo_res_abj;
	ndo_res_matriz=pt1; // entro a la raiz de la matriz
	int cost_min;

	while(ndo_res_abj!=NULL){
		ndo_res_matriz=ndo_res_abj;

		while(ndo_res_matriz!=NULL){
			cost_min = cost_min + (ndo_res_matriz->base * ndo_res_matriz->expo);
			ndo_res_matriz=ndo_res_matriz->sig;
		}
		ndo_res_abj=ndo_res_abj->abj;
	}
		printf("Costo Minimo de la Operacion: %d\n", cost_min);
}