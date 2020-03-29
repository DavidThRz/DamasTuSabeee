#include<stdio.h>
#include<iostream>

#include"Damas.h"

using namespace std;
using namespace Damas;

#define DIM 12


void main() {

	Tablero tablero;
	Ficha negra[DIM];
	Ficha blanca[DIM];


	tablero.init_tab();

	negra->init_piezas(negra,2,0,0,DIM);
	negra->init_allocate(negra,negra[0].GetVal());

	blanca->init_piezas(blanca,1, 0, 0,DIM);
	blanca->init_allocate(blanca, blanca[0].GetVal());
	
	tablero.refill_tab(blanca, negra,DIM);
	tablero.print_tab();





	cout << endl;


}