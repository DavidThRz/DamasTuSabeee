#include<stdio.h>
#define TAM 8


namespace Damas {

	class Tablero {
	public:
		int tablero[TAM][TAM];

		void init_tab();	//inicio el tablero todo a ceros
		void print_tab();	//imprime el tablero en pantalla
		void refill_tab(class Ficha a[],class Ficha b[],int dim);	//rellena los valores del tablero segun los cambios que hallan habido

		friend class Pieza; //permito a tablero acceder a las piezas
	};
	
	class Ficha {
	public:
		int x; //posicion en el eje x
		int y; //posicion en el eje y
		int valor;
		bool coronada;

		void SetVal(int val);	//introduce el valor de la ficha
		int GetVal();	//obtiene el valor de la ficha
		void SetPos(int posx, int posy);	//Establece la posicion de la ficha
		void init_piezas(class Ficha a[], int  val, int posx, int posy,int dim);	//inicia un vector de fichas 
		void init_allocate(class Ficha a[], int val);	//coloca las fichas sobre el tablero en la posicion inicial 

	};
	
}