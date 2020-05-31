#pragma once
#include<iostream>
#include"Casilla.h"

class Nodo{
private:

	bool jugador;
	int value;
	int alfa;
	int beta;
	unsigned int leaf;

public:
	Casilla Tablero[8][8];
	class Nodo* next;
	Nodo();
	virtual ~Nodo() { delete [] next; next = NULL; };

	//FUNCIONES PARA MODIFICAR EL NODO
	void SetVal(int val) { value = val; };
	void SetBeta(int b) { beta = b; };
	void SetAlfa(int a) { alfa = a; };
	void SetLeaf(int hoja) { leaf = hoja; };
	void SetJugador(bool j) { jugador = j; };
	

	//FUNCIONES PARA OBTENER DATOS DEL NODO
	int GetLeaf() { return leaf; };
	int GetVal() { return value; };
	int GetAlfa() { return alfa; };
	int GetBeta() { return beta; };
	bool GetJugador() { return jugador; };

	//FUNCION PARA PARA LIMPIAR EL NODO RAIZ
	void limpiar_nodo();
};

