#ifndef AI_HPP
#define AI_HPP
#include "Player.hpp"
#include "Tabla.hpp"

class Ai : public Player{
public:
	Ai();
	int* nextmove(Tabla* tabla, Player* p2);
	int* nextmove() override;
	virtual int getResult(int x, int y, Tabla* tabla, Player* p2)=0;
};
#endif // !AI_HPP

