#pragma once
#include"Casilla.h"
class Peon : public Casilla
{
public:
	Peon(bool c, bool a=false, bool l=false, bool cap=false, bool m=false) :Casilla(c, a, l, cap, m) {};
	virtual void dibuja();
};

