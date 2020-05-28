#pragma once
#include"Peon.h"
class Reina :public Peon
{
public:
	Reina(bool c, bool a = true, bool l = false, bool cap = false, bool m = false) :Peon(c, a, l, cap, m) {};
	void dibuja();
};

