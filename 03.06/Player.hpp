#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include "CRT.h"
class Tabla;

class Player {
protected:
	int* arr;
public:
	virtual ~Player();
	Player();
	virtual int* nextmove(int *move)=0;
	virtual int* nextmove(Tabla* tabla,Player *p2,int* move)=0;
	void set_laststeps(int x_, int y_);
	int* get_laststeps()const;
};

#endif
