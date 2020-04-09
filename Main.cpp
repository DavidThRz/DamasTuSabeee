#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<time.h>
#include<stdlib.h>


//funciona bien el algoritmo minimax y la poda para el arbol acordado, pero falla al ampliarlo, revisar

#define DIM 8
#define MAX 1
#define MIN 0

using namespace std;


class Nodo {
public:
	//int tablero[DIM][DIM];

	//usar constructor para la incializacion de los nodos

	int depth;
	int value; 

	int alfa;
	int beta;
	unsigned int leaf;
	bool jugador;

	class Nodo* next;

	void init(int prof);

};

Nodo allocate();

int minimax(Nodo root);

int alfa_beta(Nodo root);

int pouring(Nodo root);

int eva(int valor,int alfa, int beta);

void main() {

	Nodo root = allocate();
	Nodo root1 = allocate();

	int num;
	srand(time(NULL));


	

	
	for (int i = 0; i < root.leaf; i++) {
		for (int j = 0; j < root.next[i].leaf; j++) {
			for (int k = 0; k < root.next[i].next[j].leaf; k++) {
				for (int h = 0; h < root.next[i].next[j].next[k].leaf; h++) {
					for (int p = 0; p < root.next[i].next[j].next[k].next[h].leaf; p++) {
					
					
					
					
						//cin >> root.next[i].next[j].next[k].value;
						
						num = rand() % 100 - 20; ///pruebas -----------------;
						root.next[i].next[j].next[k].next[h].next[p].value = root1.next[i].next[j].next[k].next[h].next[p].value = num;
						cout << num << endl;
						
						//root.next[i].next[j].next[k].next[h].next[p].value = root1.next[i].next[j].next[k].next[h].next[p].value = num;
						//cout << num << endl;
						//cin >> num;
						//root.next[i].next[j].next[k].value = root1.next[i].next[j].next[k].value = num;
						//root.next[i].next[j].next[k].next[h].next[p].value = root1.next[i].next[j].next[k].next[h].next[p].value = num;
					
					
						//root.next[i].next[j].next[k].next[h].next[p].value = rand() % 100;   //(rand() % 10-k-i)   con esto tengo  numeros aleatorios guays
					
					}
				}
			}
		}
	}


	/*root1.next[0].next[0].next[0].value=root.next[0].next[0].next[0].value = 2;
	root1.next[0].next[0].next[1].value=root.next[0].next[0].next[1].value = 3;
	root1.next[0].next[1].next[0].value =root.next[0].next[1].next[0].value = -1;
	root1.next[0].next[1].next[1].value=root.next[0].next[1].next[1].value = 0;
	root1.next[1].next[0].next[0].value=root.next[1].next[0].next[0].value = 2;
	root1.next[1].next[0].next[1].value =root.next[1].next[0].next[1].value = 4;
	root1.next[1].next[1].next[0].value=root.next[1].next[1].next[0].value = 6;
	root1.next[1].next[1].next[1].value=root.next[1].next[1].next[1].value = 7;*/
	
	cout << endl;

	
	root.value=minimax(root); 
	cout << root.value << endl;;
	
	root1.value = alfa_beta(root1);
	cout<<root1.value;
	
	cout << endl;
	cout << endl;

	cout << endl;
	cout << endl;

	/*for (int i = 0; i < root.leaf; i++) {
		for (int j = 0; j < root.next[i].leaf; j++) {
			for (int k = 0; k < root.next[i].next[j].leaf; k++) {
				for (int h = 0; h < root.next[i].next[j].next[k].leaf; h++) {
					cout << root.next[i].next[j].next[k].next[h].value << endl;
					cout << root1.next[i].next[j].next[k].next[h].value << endl;
					cout << endl;
				}
			}
		}
	}
	for (int i = 0; i < root.leaf; i++) {
		for (int j = 0; j < root.next[i].leaf; j++) {
			for (int k = 0; k < root.next[i].next[j].leaf; k++) {
				
					cout << root.next[i].next[j].next[k].value << endl;
					cout << root1.next[i].next[j].next[k].value << endl;
					cout << endl;
			}
			
		}
	}*/

	cout<<endl;
}

Nodo allocate(){
	Nodo root;	

	root.init(0);
	root.leaf = 3;
	root.next = new Nodo[root.leaf];

	for (int i=0; i < root.leaf; i++) {
		root.next[i].leaf = 3;
		root.next[i].init(1);
		root.next[i].next = new Nodo[root.next[i].leaf];
		

		for (int j = 0; j < root.next[i].leaf; j++) {
			root.next[i].next[j].leaf = 3;
			root.next[i].next[j].init(2);
			root.next[i].next[j].next = new Nodo[root.next[i].next[j].leaf];
			

			for (int k = 0; k < root.next[i].next[j].leaf ; k++) {
				root.next[i].next[j].next[k].leaf = 3;
				
				root.next[i].next[j].next[k].init(3);
				
				root.next[i].next[j].next[k].next = new Nodo[root.next[i].next[j].next[k].leaf];

				for (int h = 0; h < root.next[i].next[j].next[k].leaf; h++) {
					root.next[i].next[j].next[k].next[h].leaf = 3;
					root.next[i].next[j].next[k].next[h].init(4);
					root.next[i].next[j].next[k].next[h].next = new Nodo[root.next[i].next[j].next[k].next[h].leaf];

					/*for (int p = 0; p < root.next[i].next[j].next[k].next[h].leaf; p++) {
						root.next[i].next[j].next[k].next[h].init(5);
					}*/
				}
				
			}
		}
		
	}

	return root;
}

int minimax(Nodo root) {

	//Evaluacion del nivel 5
	for (int i = 0; i < root.leaf; i++) {
		for (int j = 0; j < root.next[i].leaf; j++) {
			for (int k = 0; k < root.next[i].next[j].leaf; k++) {
				for (int h = 0; h < root.next[i].next[j].next[k].leaf; h++) {
					for (int p = 0; p < root.next[i].next[j].next[k].next[h].leaf; p++) {
						root.next[i].next[j].next[k].next[h].alfa = max(root.next[i].next[j].next[k].next[h].alfa, root.next[i].next[j].next[k].next[h].next[p].value);
					}
					root.next[i].next[j].next[k].next[h].value = root.next[i].next[j].next[k].next[h].alfa;
				}
			}
		}
	}

	//Evaluacion del nivel 4
	for (int i = 0; i < root.leaf; i++) {
		for (int j = 0; j < root.next[i].leaf; j++) {
			for (int k = 0; k < root.next[i].next[j].leaf; k++) {
				for (int h = 0; h < root.next[i].next[j].next[k].leaf; h++) {
					root.next[i].next[j].next[k].beta = min(root.next[i].next[j].next[k].beta, root.next[i].next[j].next[k].next[h].value);
				}
				root.next[i].next[j].next[k].value = root.next[i].next[j].next[k].beta;
			}
		}
	}


	//evaluacion nivel 3 
	for (int i = 0; i < root.leaf; i++) {
		for (int j = 0; j<root.next[i].leaf; j++) {
			for (int k = 0; k < root.next[i].next[j].leaf; k++) {
				root.next[i].next[j].alfa = max(root.next[i].next[j].alfa, root.next[i].next[j].next[k].value);
			}
			root.next[i].next[j].value = root.next[i].next[j].alfa;
		}
	}
	
	//evaluacion nivel 2
	for (int i = 0; i < root.leaf; i++) {
		for (int j = 0; j < root.next[i].leaf; j++) {
			root.next[i].beta = min(root.next[i].beta, root.next[i].next[j].value);
		}
		root.next[i].value = root.next[i].beta;
	}
	
	//evaluacion nivel 1
	for (int i = 0; i < root.leaf; i++) {
		root.alfa = max(root.alfa, root.next[i].value);
	}
	root.value = root.alfa;

	return root.value;
	
}

int eva(int valor, int alfa, int beta){

	alfa = max(alfa, valor);
	if (alfa >= beta) {
		return 3000; //referencia a Iron Man
	}
	else {
		return alfa;
	}

}
	
int alfa_beta(Nodo root){ //pseudo poda alfa beta
	int best_move = -1000;

	
	for (int i = 0; i < root.leaf; i++) {
		for (int j = 0; j < root.next[i].leaf; j++) {
			for (int k = 0; k < root.next[i].next[j].leaf; k++) {
				root.next[i].next[j].next[k].value = pouring(root.next[i].next[j].next[k]);
			}
		}
	}

	for (int i = 0; i < root.leaf; i++) { //algoritmo poda
		root.next[i].value=pouring(root.next[i]);
	}

	
	for (int i = 0; i < root.leaf; i++) { //maximo valor
		best_move = max(best_move, root.next[i].value);
	}
	root.value = best_move;
	return root.value;
}

int pouring(Nodo root){ //

	for (int j = 0; j < root.leaf; j++) {
		root.next[j].beta = root.beta; //push beta para comprobacion previa

		for (int k = 0; k < root.next[j].leaf; k++) {
			if (eva(root.next[j].next[k].value, root.next[j].alfa, root.next[j].beta) != 3000) {  //actualizacion nodo---iron man 3000
				root.next[j].value = eva(root.next[j].next[k].value, root.next[j].alfa, root.beta);
				root.next[j].alfa = root.next[j].value;
			}
			else { // poda
				root.next[j].value = root.next[j].next[k].value;
				break;
			}
		}
		if (root.next[j].value < root.next[j].beta) {
			root.beta = root.next[j].value;
		}		
	}

	return root.beta;
}

void Nodo::init(int prof){
	if (prof % 2 == 0) {
		jugador = MAX;
		alfa = -1000;
		beta = 1000;
		depth = prof;
	}
	else {
		jugador = MIN;
		alfa = -1000;
		beta = 1000;
		depth = prof;
	}
}
