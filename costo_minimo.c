//===-------------- costo_minimo.c ---------------------------------------===//
//
// Autor: Rafael Fernando Garcia Sagastume.
// Escuintla, Guatemala
//
// Test de libreria [costo_minimo] con el metodo multiplicadores
//
// compilacion: gcc costo_minimo.c -o costo_minimo
//
// Copyright © 2017 Rafael Fernando Garcia Sagastume.
//===----------------------------------------------------------------------===//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "costo_minimo.h"



int main(int argc, char const *argv[])
{
	/* code */
	printf("Iniciando Metodo Multiplicadores\n");
	insert_fila_nodo(1,5,&pt1);
	insert_fila_nodo(1,2,&pt1);
	insert_fila_nodo(1,7,&pt1);
	insert_fila_nodo(1,3,&pt1);
	close_line(1, pt1); //cierro linea de insercion

	insert_fila_nodo(1,3,&pt1);
	insert_fila_nodo(1,6,&pt1);
	insert_fila_nodo(1,6,&pt1);
	insert_fila_nodo(1,1,&pt1);
	close_line(2, pt1); //cierro linea de insercion

	insert_fila_nodo(1,6,&pt1);
	insert_fila_nodo(1,1,&pt1);
	insert_fila_nodo(1,2,&pt1);
	insert_fila_nodo(1,4,&pt1);
	close_line(3, pt1); //cierro linea de insercion

	insert_fila_nodo(1,4,&pt1);
	insert_fila_nodo(1,3,&pt1);
	insert_fila_nodo(1,6,&pt1);
	insert_fila_nodo(1,6,&pt1);
	close_line(4, pt1); //cierro linea de insercion

	// ------------------------------------------------------------------------------
	inserta_demanda(70, &l_Demanda);
	inserta_demanda(40, &l_Demanda);
	inserta_demanda(70, &l_Demanda);
	inserta_demanda(35, &l_Demanda);

	inserta_oferta(80, &l_Oferta);
	inserta_oferta(30, &l_Oferta);
	inserta_oferta(60, &l_Oferta);
	inserta_oferta(45, &l_Oferta);
	//ver_n(pt1);
	ver_Demanda_Oferta(l_Demanda, l_Oferta);

	printf("\n");

	ver_n(pt1);
	Operacion_costo_minimo(pt1, l_Oferta, l_Demanda);

	v_cost_min();
	ver_n(pt1);

	printf("\n");
	return 0;
}
