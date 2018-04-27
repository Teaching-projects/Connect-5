#ifndef AI_EASY_HPP
#define AI_EASY_HPP
#include "Ai.hpp"

class Ai_Easy : public Ai {
public:
	Ai_Easy();
	int getResult(int x, int y,Tabla* tabla,Player* p2);
};

#endif // !AI_HARD_HPP

