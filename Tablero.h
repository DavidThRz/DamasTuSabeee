#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"Nodo.h"
#include"Reina.h"
#include"ETSIDI.h"
#include<fstream>
#include<algorithm>
#include<algorithm>

using namespace std;

const int ml = 8;
const int nl = 48;
const int MaxStrLen = 100;
void DrawString(float x, float y, const char* c, int var = 0, bool v = false);

class Tablero{
private:
	bool turno, elegido, fin;//0 turno de rojo, 1 turno de negro
	Casilla* Casillas[ml][ml];// casillas del tablero
	int chosenx, choseny;
	int destinox[4], destinoy[4];

public:

	Tablero();
	void dibuja();
	void revisa();
	bool elije(int x, int y);
	bool desplaza(int x, int y);
	void destinos();
	void proceso(int x, int y);
	int contador(Casilla c[ml][ml],bool turno,Casilla cubo[nl][ml][ml]); //uso exclusivo IA
	void guardar();
	void leer();
	void copiar_tab(Casilla c[ml][ml]) {for (int i = 0; i < ml; i++)for (int j = 0; j < ml; j++)c[i][j] = *Casillas[i][j];}; //uso exclusivo IA

};

