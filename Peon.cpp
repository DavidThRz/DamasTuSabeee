#include "Peon.h"
void Peon::dibuja()
{
	Casilla::dibuja();
	getColor() ? glColor4f(1, 1, 1, 1) : glColor4f(1, 0, 0, 1);
	glutSolidSphere(0.4, 20, 20);
}
