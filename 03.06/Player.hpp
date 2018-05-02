#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include "CRT.h"
class Tabla;

struct step {
	int x;
	int y;
	step() :x(-1), y(-1) {};
	step(int x, int y) :x(x), y(y) {};
};
class Player {
	step l;
public:
	virtual ~Player();
	Player();
	virtual step nextmove(Tabla* tabla,Player *p2)=0;
	void set_laststeps(int x_, int y_);
	step get_laststeps()const;
};

#endif
