#ifndef AI_HARD_HPP
#define AI_HARD_HPP
#include "Ai.hpp"

class Ai_Hard : public Ai{
	int* laststeps;
public:
	Ai_Hard();
	int* nextmove() override;
};

#endif // !AI_HARD_HPP

