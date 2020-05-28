#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"Reina.h"
#include"ETSIDI.h"
const int ml = 8;
const int MaxStrLen = 100;
void DrawString(float x, float y, const char* c, int var = 0, bool v = false);

class Tablero
{
private:
	bool turno, elegido, fin;//0 turno de rojo, 1 turno de negro
	Casilla* Casillas[ml][ml];// casillas del tablero
	int chosenx, choseny;
public:
	Tablero();
	void dibuja();
	void revisa();
	bool elije(int x, int y);
	bool desplaza(int x, int y);
	void proceso(int x, int y);
	int contador();
};
