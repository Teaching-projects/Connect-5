#ifndef AI_HARD_HPP
#define AI_HARD_HPP
#include "Ai.hpp"

class Ai_Hard : public Ai{
public:
	Ai_Hard();
	int getResult(int x, int y, Tabla* tabla, Player* p2) ;
	int getDefence(int x, int y,Tabla* tabla, Player* p2) ;
};

#endif // !AI_HARD_HPP

