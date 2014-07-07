// Creado por ArchangelSmarth 25/05/2014
// version 1.0.0
// Escuintla_Guatemala
// Copyright © 2007 Free Software Foundation, Inc

#include "stdio.h"
#include "stdlib.h"

struct nodo{ // estuctura de los ndos de la matriz Multiplicadores
	int status; //[solo sera para el primer nodo] [0 // cerrado || 1 // abierto]
	int fila, sts_sp;  // sts_sp  ?? bloqueo special
	int base, expo; 
	struct nodo *sig, *abj; // enlace de nodos
};

// raiz de la matriz del nodo
struct nodo *pt1=0; // ??  matriz de datos ??
struct nodo *l_Demanda=0;  //?? contendra las demandas
struct nodo *l_Oferta=0; // ?? contendra las ofertas
//prototipos
void insert_fila_nodo(int f, int b, /*int e*/ struct nodo **rn);
void insert_new_fila_nodo(int f, int b, /*int e*/ struct nodo **rn);
void close_line(int line, struct nodo *rn);
void ver_n(struct nodo *rn);
void ver_Demanda_Oferta(struct nodo *raiz_demanda, struct nodo *raiz_oferta);
struct nodo *inserta_oferta(int o, struct nodo **rai_oferta);
struct nodo *inserta_demanda(int d, struct nodo **raiz_demanda);
void block_nodos_off(struct nodo *raiz_matriz , struct nodo *raiz_oferta, struct nodo *raiz_demanda);
void Operacion_costo_minimo(struct nodo *raiz_matriz , struct nodo *raiz_oferta, struct nodo *raiz_demanda);
void v_cost_min();


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
}

struct nodo *inserta_oferta(int o, struct nodo **rai_oferta){
	if(!(*rai_oferta)){
		(*rai_oferta)=crear_nodo(1, o, (*rai_oferta));
	}else{
		inserta_oferta(o, &((*rai_oferta)->sig));
	}
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

}

// ----------------------------------- Operacion Costo Minimo ----------------------------------

void Operacion_costo_minimo(struct nodo *raiz_matriz , struct nodo *raiz_oferta, struct nodo *raiz_demanda){

	int pos_minimo_matriz, r_demanda, r_oferta=1, pos_demanda, pos_oferta;
	int max, min;
	struct nodo *ptr, *new_fila, *f1;
	ptr = pt1;
	new_fila=pt1; 
	raiz_oferta=l_Oferta;
	raiz_demanda=l_Demanda;

	while(new_fila!=NULL){
		ptr=raiz_matriz=new_fila; // estara en cada fila
		min=raiz_matriz->base; // por default toma el valor del primer nodo
		raiz_oferta=l_Oferta;
		raiz_demanda=l_Demanda;
		pos_minimo_matriz = pos_demanda = pos_oferta = 1;
	while(raiz_matriz!=NULL){ //?? buscar numero de fila

		if(raiz_matriz->sig!=NULL){	// valida si el siguiente existe
			if(min<raiz_matriz->sig->base && (raiz_matriz->sig->sts_sp==0)){  // si el nodo esta bloqueado no compara
				raiz_matriz=raiz_matriz->sig;
			}else if(min>raiz_matriz->sig->base && (raiz_matriz->sig->sts_sp==0)){
				min=raiz_matriz->sig->base; // tiene el valor minimo
				pos_minimo_matriz++; // posicion del minimo
				raiz_matriz=raiz_matriz->sig;
				ptr = raiz_matriz;  // apunta al nodo menor
			}else{
				raiz_matriz=raiz_matriz->sig;
			}
		}else{
			break;
		}
		
	}
	printf("Minimo: %d", ptr->base);printf(" Posicion: %d\n", pos_minimo_matriz);

	while(pos_demanda!=pos_minimo_matriz){ // busca la demanda para el caso

		if(raiz_demanda!=NULL){ // solo valido que no sea NULL
			raiz_demanda=raiz_demanda->sig;
			pos_demanda++;
		}

	}
	printf("Demanda para Gastar: %d\n", raiz_demanda->base);

		while(pos_oferta != r_oferta){ // busca la Oferta para el caso
			if(raiz_oferta!=NULL){ // solo valido que no sea NULLz
				raiz_oferta=raiz_oferta->sig;
				pos_oferta++;
			}
		}
			printf("Oferta para Gastar: %d\n", raiz_oferta->base);

			if(raiz_oferta->base < raiz_demanda->base && (ptr->sts_sp==0)){
				ptr->expo= raiz_oferta->base;
				raiz_demanda->base = raiz_demanda->base - raiz_oferta->base;
				raiz_oferta->base = 0;
			}else if(raiz_oferta->base > raiz_demanda->base && (ptr->sts_sp==0)){
				ptr->expo=raiz_demanda->base;
				raiz_oferta->base=raiz_oferta->base - raiz_demanda->base;
				raiz_demanda->base = 0;
			}

		printf("Demanda Actual: %d\n", raiz_demanda->base);printf("  Oferta Actual: %d\n", raiz_oferta->base);
		printf("%d", ptr->base);printf("  Exponente: %d\n", ptr->expo);
		printf("-----------------------------------------------------------------------\n");
		// cada ciclo es una operacion

	new_fila=new_fila->abj; r_oferta++;
	}
	block_nodos_off(pt1, l_Oferta, l_Demanda);

	struct nodo *s_oferta, *s_demanda;
	int result_ofer, result_deman;
	s_oferta = l_Oferta;
	s_demanda = l_Demanda;
	// suma la ofer/demanda 

	while(s_oferta!=NULL){
		result_ofer = result_ofer + s_oferta->base;
		result_deman = result_deman + s_demanda->base;
		s_oferta = s_oferta->sig;
		s_demanda = s_demanda->sig;
	}
	printf("demanda sumatoria------> : %d\n", result_deman);
	printf("oferta sumatoria------> : %d\n", result_ofer);

	if(result_deman == 0){
		// ?? se termino el proceso
		v_cost_min();
	}else if(result_ofer == 0){
		// ?? se termino el proceso
		v_cost_min();
	}else{
		printf("Se sigue procesando....!!!\n");
		Operacion_costo_minimo(pt1, l_Oferta, l_Demanda);
	}


}


void block_nodos_off(struct nodo *raiz_matriz , struct nodo *raiz_oferta, struct nodo *raiz_demanda){  // if ofer=0 || demanda=0   ---> block nodos
	struct nodo *ptr_Oferta;
	struct nodo *ptr_Demanda;
	struct nodo *ptr_abj;
	struct nodo *ptr_sig;
	struct nodo *ptr_matriz;
	ptr_Oferta = raiz_oferta;
	ptr_matriz = ptr_sig = ptr_abj = raiz_matriz;


	int n_oferta=1, n_demanda=1, n_matriz_abj=1, n_matriz_sig=1, _matriz=1;

	// code // bloque nodo ofer=0--------------------------------------------------
	while(ptr_Oferta!=NULL){  // bloquar fila de oferta cero

		if(ptr_Oferta->base == 0){
			n_matriz_abj = n_oferta;

			while( _matriz != n_matriz_abj){ // busca la fila de la oferta
				_matriz++;
				ptr_abj=ptr_abj->abj;
			}

			ptr_sig = ptr_abj;

			while(ptr_sig!=NULL){
				ptr_sig->sts_sp=1; // ¡¡ ndo block !!
				ptr_sig=ptr_sig->sig;
			}

		}
		n_oferta++;
		ptr_Oferta=ptr_Oferta->sig;

	}

	// code // para bloquear nodos con demanda=0 ----------------------------------
	ptr_Demanda = raiz_demanda;
	ptr_matriz = ptr_sig = ptr_abj = raiz_matriz;
	n_oferta=1, n_demanda=1, n_matriz_abj=1, n_matriz_sig=1, _matriz=1;
	int n_sig_sig=1;


	while(ptr_Demanda!=NULL){

		if(ptr_Demanda->base == 0){
			ptr_abj = ptr_sig = raiz_matriz;
				while(ptr_abj!=NULL){
					n_sig_sig=1;
					while(n_sig_sig != n_demanda){
						n_sig_sig++;
							ptr_sig=ptr_sig->sig;
					}
					ptr_sig->sts_sp=1;   // block ndo ????
					if(ptr_abj!=NULL){
						ptr_abj=ptr_abj->abj;
						ptr_sig=ptr_abj;
					}

				}
		}

		n_demanda++;
		ptr_Demanda= ptr_Demanda->sig;
	}

}

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


//--------------------------------------- metodo principal---------------------------------------

int main(int argc, char const *argv[])
{
	
	/* code */
	// el ingreso de los datos es manual para el primer beta
	printf("Iniciando Metodo Multiplicadores\n");
	insert_fila_nodo(1,23,&pt1);
	insert_fila_nodo(1,6,&pt1);
	insert_fila_nodo(1,24,&pt1);
	close_line(1, pt1); //cierro linea de insercion

	insert_fila_nodo(1,20,&pt1);
	insert_fila_nodo(1,12,&pt1);
	insert_fila_nodo(1,11,&pt1);

	close_line(2, pt1); //cierro linea de insercion
	insert_fila_nodo(1,18,&pt1);
	insert_fila_nodo(1,20,&pt1);
	insert_fila_nodo(1,30,&pt1);

	


	inserta_demanda(120, &l_Demanda);
	inserta_demanda(80, &l_Demanda);
	inserta_demanda(100, &l_Demanda);

	inserta_oferta(100, &l_Oferta);
	inserta_oferta(200, &l_Oferta);
	inserta_oferta(100, &l_Oferta);
	ver_n(pt1);
	ver_Demanda_Oferta(l_Demanda, l_Oferta);

	printf("\n");
	Operacion_costo_minimo(pt1, l_Oferta, l_Demanda);

	//block_nodos_off(pt1, l_Oferta, l_Demanda);

	ver_n(pt1);

	printf("\n");
	return 0;
}
