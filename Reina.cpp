#include "Reina.h"
void Reina::dibuja()
{
	Peon::dibuja();
	glTranslatef(0, 0, 0.5);
	glColor4f(1, 1, 0, 1);
	glutSolidSphere(0.2, 20, 20);
	glTranslatef(0, 0, -0.5);
};