#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
class Tabla;

class Player {
protected:
	int x;
	int y;
public:
	Player();
	virtual int* nextmove()=0;
	virtual int* nextmove(Tabla* tabla,Player *p2)=0;
	void set_laststeps(int x_, int y_);
	int* get_laststeps()const;
};

#endif
