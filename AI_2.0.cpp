#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<time.h>
#include<stdlib.h>

#define DIM 8
#define MAX 1
#define MIN 0

using namespace std;


class Nodo {
private:

	int value;
	int alfa;
	int beta;
	unsigned int leaf;

	
public:
	
	class Nodo* next;
	Nodo() { alfa = -1000; beta = 1000; };

	//FUNCIONES PARA MODIFICAR EL NODO
	void SetVal(int val);
	void SetBeta(int b);
	void SetAlfa(int a);
	void SetLeaf(int hoja);

	//FUNCIONES PARA OBTENER DATOS DEL NODO
	int Getleaf() { return leaf; };
	int GetVal() { return value; };
	int GetAlfa() { return alfa; };
	int GetBeta() { return beta; };

};

class IA {
public:
	Nodo root;

	//ALGORTIMOS JUEGO
	void minimax();
	void alfa_beta();

	//FUNCIONES AXULIARES
	int pouring(Nodo root);
	int pouring_condition(int valor, int alfa, int beta);
	void allocate();
	void deleteTree();
		
};


void main() {
	IA damas;
	damas.allocate();
	int num;
	srand(time(NULL));

	for (int i = 0; i < damas.root.Getleaf(); i++) {
		for (int j = 0; j < damas.root.next[i].Getleaf(); j++) {
			for (int k = 0; k < damas.root.next[i].next[j].Getleaf(); k++) {
				for (int h = 0; h < damas.root.next[i].next[j].next[k].Getleaf(); h++) {
					for (int p = 0; p < damas.root.next[i].next[j].next[k].next[h].Getleaf(); p++) {
						num = rand() % 100 - 45;
						damas.root.next[i].next[j].next[k].next[h].next[p].SetVal(num);
					}
				}
			}
		}
	}
	damas.minimax();
	cout << damas.root.GetVal() << endl;
	damas.deleteTree();
}


void IA::minimax(){

	for (int i = 0; i < root.Getleaf(); i++) {
		for (int j = 0; j < root.next[i].Getleaf(); j++) {
			for (int k = 0; k < root.next[i].next[j].Getleaf(); k++) {
				for (int h = 0; h < root.next[i].next[j].next[k].Getleaf(); h++) {
					for (int p = 0; p < root.next[i].next[j].next[k].next[h].Getleaf(); p++) {
						root.next[i].next[j].next[k].next[h].SetAlfa(max(root.next[i].next[j].next[k].next[h].GetAlfa(), root.next[i].next[j].next[k].next[h].next[p].GetVal()));
					}
					root.next[i].next[j].next[k].next[h].SetVal(root.next[i].next[j].next[k].next[h].GetAlfa());
				}
			}
		}
	}

	for (int i = 0; i < root.Getleaf(); i++) {
		for (int j = 0; j < root.next[i].Getleaf(); j++) {
			for (int k = 0; k < root.next[i].next[j].Getleaf(); k++) {
				for (int h = 0; h < root.next[i].next[j].next[k].Getleaf(); h++) {
					root.next[i].next[j].next[k].SetBeta(min(root.next[i].next[j].next[k].GetBeta(), root.next[i].next[j].next[k].next[h].GetVal()));
				}
				root.next[i].next[j].next[k].SetVal(root.next[i].next[j].next[k].GetBeta());
			}
		}
	}

	for (int i = 0; i < root.Getleaf(); i++) {
		for (int j = 0; j < root.next[i].Getleaf(); j++) {
			for (int k = 0; k < root.next[i].next[j].Getleaf(); k++) {
				root.next[i].next[j].SetAlfa(max(root.next[i].next[j].GetAlfa(), root.next[i].next[j].next[k].GetVal()));
			}
			root.next[i].next[j].SetVal(root.next[i].next[j].GetAlfa());
		}
	}


	for (int i = 0; i < root.Getleaf(); i++) {
		for (int j = 0; j < root.next[i].Getleaf(); j++) {
			root.next[i].SetBeta(min(root.next[i].GetBeta(), root.next[i].next[j].GetVal()));
		}
		root.next[i].SetVal(root.next[i].GetBeta());
	}

	for (int i = 0; i < root.Getleaf(); i++) {
		root.SetAlfa(max(root.GetAlfa(), root.next[i].GetVal()));
	}
	root.SetVal(root.GetAlfa());
}

void IA::alfa_beta(){

	for (int i = 0; i < root.Getleaf(); i++) {
		for (int j = 0; j < root.next[i].Getleaf(); j++) {
			for (int k = 0; k < root.next[i].next[j].Getleaf(); k++) {
				root.next[i].next[j].next[k].SetVal(pouring(root.next[i].next[j].next[k]));
			}
		}
	}

	for (int i = 0; i < root.Getleaf(); i++) {
		root.next[i].SetVal(pouring(root.next[i]));
	}

	for (int i = 0; i < root.Getleaf(); i++) {
		root.SetAlfa(max(root.GetAlfa(), root.next[i].GetVal()));
	}

	root.SetVal(root.GetAlfa());
	
}

int IA::pouring(Nodo root){

	for (int j = 0; j < root.Getleaf(); j++) {
		root.next[j].SetBeta(root.GetBeta());

		for (int k = 0; k < root.next[j].Getleaf(); k++) {
			if (pouring_condition(root.next[j].next[k].GetVal(), root.next[j].GetAlfa(), root.next[j].GetBeta()) != 3000) {
				root.next[j].SetVal(pouring_condition(root.next[j].next[k].GetVal(), root.next[j].GetAlfa(), root.GetBeta()));
				root.next[j].SetAlfa(root.next[j].GetVal());
			}
			else {
				root.next[j].SetVal(root.next[j].next[k].GetVal());
				break;
			}
		}
		if (root.next[j].GetVal() < root.next[j].GetBeta()) {
			root.SetBeta( root.next[j].GetVal());
		}
	}

	return root.GetBeta();
}

int IA::pouring_condition(int valor, int alfa, int beta){

	alfa = max(alfa, valor);
	if (alfa >= beta) {
		return 3000;
	}
	else {
		return alfa;
	}
}

void IA::allocate(){

	root.SetLeaf(2);
	root.next = new Nodo[root.Getleaf()];

	for (int i = 0; i < root.Getleaf(); i++) {
		root.next[i].SetLeaf(2);
		root.next[i].next = new Nodo[root.next[i].Getleaf()];

		for (int j = 0; j < root.next[i].Getleaf(); j++) {
			root.next[i].next[j].SetLeaf(2);
			root.next[i].next[j].next = new Nodo[root.next[i].next[j].Getleaf()];

			for (int k = 0; k < root.next[i].next[j].Getleaf(); k++) {
				root.next[i].next[j].next[k].SetLeaf(2);
				root.next[i].next[j].next[k].next = new Nodo[root.next[i].next[j].next[k].Getleaf()];

				for (int h = 0; h < root.next[i].next[j].next[k].Getleaf(); h++) {
					root.next[i].next[j].next[k].next[h].SetLeaf(2);
					root.next[i].next[j].next[k].next[h].next = new Nodo[root.next[i].next[j].next[k].next[h].Getleaf()];
				}
			}
		}
	}


}

void IA::deleteTree(){

	for (int i = 0; i < root.Getleaf(); i++) {
		for (int j = 0; j < root.next[i].Getleaf(); j++) {
			for (int k = 0; k < root.next[i].next[j].Getleaf(); k++) {
				for (int h = 0; h < root.next[i].next[j].next[k].Getleaf(); h++) {
					delete[] root.next[i].next[j].next[k].next[h].next;
				}
				delete[] root.next[i].next[j].next[k].next;
			}
			delete[] root.next[i].next[j].next;
		}
		delete[] root.next[i].next;
	}
	
	delete[] root.next;
	
}


void Nodo::SetVal(int val){
	value = val;
}

void Nodo::SetBeta(int b){
	beta = b;
}

void Nodo::SetAlfa(int a){
	alfa = a;
}

void Nodo::SetLeaf(int hoja){
	leaf = hoja;
}
