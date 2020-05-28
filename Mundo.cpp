#include "Mundo.h"
Mundo::Mundo()
{

};
void Mundo::raton(int x, int y)
{
	if (!menu) {
		int i, j;
		i = x / WinSize * ml;
		j = (WinSize - y) / WinSize * ml;//convertir pixeles a casillas
		MiTablero.proceso(i, j);
	};


};
void Mundo::dibuja()
{
	MiTablero.dibuja();
}