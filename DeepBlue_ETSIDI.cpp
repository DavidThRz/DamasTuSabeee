#include"DeepBlue_ETSIDI.h"

void DeepBlue_ETSIDI::reset_tab() {
	for (int i = 0; i < nl; i++) {
		for (int j = 0; j < ml; j++) {
			for (int k = 0; k < ml; k++) {
				Aux_Cas[i][j][k] = NULL;
			}
		}
	}
}

void DeepBlue_ETSIDI::fill_tab(Nodo c) {
	for (int i = 0; i < 48; i++) {
		if (Aux_Cas[i] != NULL) {///podria fallar 
			for (int x = 0; x < ml; x++) {
				for (int y = 0; y < ml; y++) {
					c.next[i].Tablero[x][y] = Aux_Cas[i][x][y];
				}
			}
		}
	}
	reset_tab();
}


void DeepBlue_ETSIDI::minimax() {

	for (int i = 0; i < root.GetLeaf(); i++) {
		for (int j = 0; j < root.next[i].GetLeaf(); j++) {
			for (int k = 0; k < root.next[i].next[j].GetLeaf(); k++) {
				for (int h = 0; h < root.next[i].next[j].next[k].GetLeaf(); h++) {
					for (int p = 0; p < root.next[i].next[j].next[k].next[h].GetLeaf(); p++) {
						root.next[i].next[j].next[k].next[h].SetAlfa(max(root.next[i].next[j].next[k].next[h].GetAlfa(), root.next[i].next[j].next[k].next[h].next[p].GetVal()));
					}
					root.next[i].next[j].next[k].next[h].SetVal(root.next[i].next[j].next[k].next[h].GetAlfa());
				}
			}
		}
	}

	for (int i = 0; i < root.GetLeaf(); i++) {
		for (int j = 0; j < root.next[i].GetLeaf(); j++) {
			for (int k = 0; k < root.next[i].next[j].GetLeaf(); k++) {
				for (int h = 0; h < root.next[i].next[j].next[k].GetLeaf(); h++) {
					root.next[i].next[j].next[k].SetBeta(min(root.next[i].next[j].next[k].GetBeta(), root.next[i].next[j].next[k].next[h].GetVal()));
				}
				root.next[i].next[j].next[k].SetVal(root.next[i].next[j].next[k].GetBeta());
			}
		}
	}

	for (int i = 0; i < root.GetLeaf(); i++) {
		for (int j = 0; j < root.next[i].GetLeaf(); j++) {
			for (int k = 0; k < root.next[i].next[j].GetLeaf(); k++) {
				root.next[i].next[j].SetAlfa(max(root.next[i].next[j].GetAlfa(), root.next[i].next[j].next[k].GetVal()));
			}
			root.next[i].next[j].SetVal(root.next[i].next[j].GetAlfa());
		}
	}


	for (int i = 0; i < root.GetLeaf(); i++) {
		for (int j = 0; j < root.next[i].GetLeaf(); j++) {
			root.next[i].SetBeta(min(root.next[i].GetBeta(), root.next[i].next[j].GetVal()));
		}
		root.next[i].SetVal(root.next[i].GetBeta());
	}

	for (int i = 0; i < root.GetLeaf(); i++) {
		root.SetAlfa(max(root.GetAlfa(), root.next[i].GetVal()));
	}
	root.SetVal(root.GetAlfa());
}

void DeepBlue_ETSIDI::alfa_beta() {

	for (int i = 0; i < root.GetLeaf(); i++) {
		for (int j = 0; j < root.next[i].GetLeaf(); j++) {
			for (int k = 0; k < root.next[i].next[j].GetLeaf(); k++) {
				root.next[i].next[j].next[k].SetVal(pouring(root.next[i].next[j].next[k]));
			}
		}
	}

	for (int i = 0; i < root.GetLeaf(); i++) {
		root.next[i].SetVal(pouring(root.next[i]));
	}

	for (int i = 0; i < root.GetLeaf(); i++) {
		root.SetAlfa(max(root.GetAlfa(), root.next[i].GetVal()));
	}

	root.SetVal(root.GetAlfa());

}

int DeepBlue_ETSIDI::pouring(Nodo root) {

	for (int j = 0; j < root.GetLeaf(); j++) {
		root.next[j].SetBeta(root.GetBeta());

		for (int k = 0; k < root.next[j].GetLeaf(); k++) {
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
			root.SetBeta(root.next[j].GetVal());
		}
	}

	return root.GetBeta();
}

int DeepBlue_ETSIDI::pouring_condition(int valor, int alfa, int beta) {

	alfa = max(alfa, valor);
	if (alfa >= beta) {
		return 3000;
	}
	else {
		return alfa;
	}
}

void DeepBlue_ETSIDI::allocate() {
	t.copiar_tab(Aux_Tab);
	for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)root.Tablero[i][j] = Aux_Tab[i][j];

	root.SetJugador(true); //indica que jugador mueve
	root.SetLeaf(t.contador(root.Tablero,root.GetJugador(),Aux_Cas));
	root.next = new Nodo[root.GetLeaf()];
	fill_tab(root);


	for (int i = 0; i < root.GetLeaf(); i++) {
		root.next[i].SetJugador(false); //indica que jugador mueve
		root.next[i].SetLeaf(t.contador(root.next[i].Tablero,root.next[i].GetJugador(),Aux_Cas));
		root.next[i].next = new Nodo[root.next[i].GetLeaf()];
		fill_tab(root.next[i]);

		for (int j = 0; j < root.next[i].GetLeaf(); j++) {
			root.next[i].next[j].SetJugador(true);//indica que jugador mueve
			root.next[i].next[j].SetLeaf(t.contador(root.next[i].next[j].Tablero,root.next[i].next[j].GetJugador(),Aux_Cas));
			root.next[i].next[j].next = new Nodo[root.next[i].next[j].GetLeaf()];
			fill_tab(root.next[i].next[j]);

			for (int k = 0; k < root.next[i].next[j].GetLeaf(); k++) {
				root.next[i].next[j].next[k].SetJugador(false);//indica que jugador mueve
				root.next[i].next[j].next[k].SetLeaf(t.contador(root.next[i].next[j].next[k].Tablero, root.next[i].next[j].next[k].GetJugador(),Aux_Cas));
				root.next[i].next[j].next[k].next = new Nodo[root.next[i].next[j].next[k].GetLeaf()];
				fill_tab(root.next[i].next[j].next[k]);


				for (int h = 0; h < root.next[i].next[j].next[k].GetLeaf(); h++) {
					root.next[i].next[j].next[k].next[h].SetJugador(true);//indica que jugador mueve
					root.next[i].next[j].next[k].next[h].SetLeaf(t.contador(root.next[i].next[j].next[k].Tablero, root.next[i].next[j].next[k].next[h].GetJugador(), Aux_Cas));
					root.next[i].next[j].next[k].next[h].next = new Nodo[root.next[i].next[j].next[k].next[h].GetLeaf()];
					fill_tab(root.next[i].next[j].next[k].next[h]);

				}
			}
		}
	}

}

void DeepBlue_ETSIDI::deleteTree() {

	for (int i = 0; i < root.GetLeaf(); i++) {
		for (int j = 0; j < root.next[i].GetLeaf(); j++) {
			for (int k = 0; k < root.next[i].next[j].GetLeaf(); k++) {
				for (int h = 0; h < root.next[i].next[j].next[k].GetLeaf(); h++) {
					delete[] root.next[i].next[j].next[k].next[h].next;
				}
				delete[] root.next[i].next[j].next[k].next;
			}
			delete[] root.next[i].next[j].next;
		}
		delete[] root.next[i].next;
	}

	delete[] root.next;

	root.limpiar_nodo();

}

void DeepBlue_ETSIDI::DeepBlue_mov() {
	int movimiento = -1000;
	for (int i = 0; i < root.GetLeaf(); i++) {
		movimiento = max(root.next[i].GetVal(), movimiento);
	}

	for (int i = 0; i < ml; i++) {
		for (int j = 0; j < ml; j++) {
			Aux_Tab[i][j] = root.next[movimiento].Tablero[i][j];
		}
	}
}