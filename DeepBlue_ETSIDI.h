#pragma once
#include"Nodo.h"
#include"Tablero.h"
#include<algorithm>

#define MAX 50

using namespace std;

class DeepBlue_ETSIDI{
public:

	Tablero t;
	Nodo root;
	Casilla Aux_Cas[nl][ml][ml];
	Casilla Aux_Tab[ml][ml];

	
	//ALGORTIMOS JUEGO
	void minimax();
	void alfa_beta();

	//FUNCIONES AXULIARES
	int pouring(Nodo root);
	int pouring_condition(int valor, int alfa, int beta);
	void allocate();
	void deleteTree();
	void DeepBlue_mov();
	void reset_tab();
	void fill_tab(Nodo c);

};

