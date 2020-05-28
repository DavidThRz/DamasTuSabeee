#pragma once
#include<freeglut.h>
class Casilla
{
private:
	bool libre;//false=vacio,true=ocupado
	bool color;//negro=true;rojo==false
	bool capturable;//true=se puede capturar en este turno
	bool movible;//true=puede mover en este turno
	bool acoronado;//true= acoronado
public:
	Casilla(bool c=false, bool a=false, bool l=true, bool cap = false , bool m=false);
	virtual void dibuja();
	Casilla& operator= (const Casilla&);//operador miembro de asignacion sobrecargado
	bool getLibre() { return libre; };
	bool getColor() { return color; };
	bool getCap() { return capturable; };
	bool getMov() { return movible; };
	bool getAcor() { return acoronado; };
	void setLibre(bool l) { libre = l; };
	void setColor(bool c) { color = c; };
	void setCap(bool c) { capturable = c; };
	void setMov(bool m) { movible=m; };
	void setAcor(bool a) { acoronado = a; };
};

