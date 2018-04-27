#ifndef AI_HPP
#define AI_HPP
#include "Player.hpp"
#include "Tabla.hpp"
#include "CRT.h"

class Ai : public Player{
public:
	~Ai();
	Ai();
	int* nextmove(Tabla* tabla, Player* p2,int* move);
	int* nextmove(int* move) override;
	virtual int getResult(int x, int y, Tabla* tabla, Player* p2)=0;
};
#endif // !AI_HPP

