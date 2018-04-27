#ifndef AI_HARD_HPP
#define AI_HARD_HPP
#include "Ai.hpp"

class Ai_Hard : public Ai{

public:
	Ai_Hard();
	int* nextmove(Jatek* jatek);
	int getResult(int x, int y, Jatek* jatek) override;
	int getDefence(int x, int y,Jatek* jatek) ;
};

#endif // !AI_HARD_HPP

