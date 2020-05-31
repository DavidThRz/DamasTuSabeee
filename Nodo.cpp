#include "Nodo.h"

Nodo::Nodo(){
	alfa = -1000; beta = 1000;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Tablero[i][j] = NULL;
		}
	}
};

void Nodo::limpiar_nodo(){
	SetLeaf(0);
	SetBeta(1000);
	SetAlfa(-1000);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Tablero[i][j] = NULL;
		}
	}
}
