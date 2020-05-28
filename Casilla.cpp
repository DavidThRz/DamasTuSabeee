#include "Casilla.h"
Casilla::Casilla(bool c, bool a, bool l, bool cap, bool m) {
	libre = l;
	color = c;
	capturable = cap;
	movible = m;
	acoronado = a;
}
Casilla& Casilla::operator= (const Casilla& a)
{
	libre = a.libre;
	color = a.color;
	capturable = a.capturable;
	movible = a.movible;
	acoronado = a.acoronado;
	return(*this);
};
void Casilla::dibuja()
{
	glBegin(GL_QUADS);
	glVertex3d(-0.5, -0.5, 0);
	glVertex3d(0.5, -0.5, 0);
	glVertex3d(0.5, 0.5, 0);
	glVertex3d(-0.5, 0.5, 0);
	glEnd();
};