#ifndef AI_EASY_HPP
#define AI_EASY_HPP
#include "Ai.hpp"

class Ai_Easy : public Ai {
	int* laststeps;
public:
	Ai_Easy();
	int* nextmove()override;
};

#endif // !AI_HARD_HPP

