#pragma once
#include"Tablero.h"
const float WinSize = 600;
class Mundo
{
public:
	Tablero MiTablero;
	Mundo();
	bool menu;
	void raton(int x, int y);
	void dibuja();

};

