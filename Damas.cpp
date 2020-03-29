#include<stdio.h>
#include<iostream>
#include"Damas.h"
#define DIM 12

using namespace std;


namespace Damas {

    void Tablero::init_tab() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                tablero[i][j] = 0;
            }
        }
    }

    void Tablero::print_tab(){
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cout <<" " <<tablero[i][j];
            }
            cout << endl;
        }
    }

    void Tablero::refill_tab(class Ficha a[], class Ficha b[],int dim){
		for (int i = 0; i < dim; i++) {
			tablero[a[i].x][a[i].y] = a[i].valor;
			tablero[b[i].x][b[i].y] = b[i].valor;
		}
    }



	void Ficha::SetVal(int val) { //modifico el valor de la ficha
		if (0 < val < 3) { //el valor 1 es para las blancas y el dos para las negras
			valor = val;
		}
		else {
			perror("Ha habido un error");
		}
	}

	int Ficha::GetVal() { //extraigo el valor de la ficha
		return valor;
	}

	void Ficha::SetPos(int posx, int posy) { //modifico la posicion de la ficha
		x = posx;
		y = posy;
	}

	void Ficha::init_piezas(class Ficha a[], int val, int posx, int posy,int dim) {
		for (int i = 0; i < dim; i++) {
			a[i].coronada = false; //inicialmente las piezas son peones
			a[i].SetVal(val);	   //inicialmente doy un valor a las piezas blancas o negras
			a[i].SetPos(posx, posy); //inicialmente le doy una posicion a cada pieza, por defecto todas 0,0
		}
		;

	}

	void Ficha::init_allocate(class Ficha a[], int val) {
		int k = 0;
		if (val == 2) {//las negras, se situaran en las posiciones mas bajas de la matriz
			for (int i = 5; i < 8; i++) { //coloco fichas en fila 6 a la 8 en nomenclatura ajedrez  
				for (int j = 0; j < 8; j++) {
					if (i % 2 == 1) { //la columna a tiene ficha 
						a[k].x = i, a[k].y = j;
						k++;
						j++;
					}
					if (i % 2 == 0) { //la columna b tiene ficha
						j++;
						a[k].x = i, a[k].y = j;
						k++;
					}

				}
			}
		}
		else {//las blancas, se situaran en las posiciones mas altas de la matriz
			for (int i = 0; i < 3; i++) { //coloco fichas en fila 1 a la 2 en nomenclatura ajedrez  
				for (int j = 0; j < 8; j++) {
					if (i % 2 == 1) { //la columna a tiene ficha 
						a[k].x = i, a[k].y = j;
						k++;
						j++;
					}
					if (i % 2 == 0) { //la columna b tiene ficha
						j++;
						a[k].x = i, a[k].y = j;
						k++;
					}
				}
			}
		}

	}
}