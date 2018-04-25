#ifndef AI_EASY_HPP
#define AI_EASY_HPP
#include "Player.hpp"

class Ai_Easy : public Player {
public:
	Ai_Easy();
	int* nextmove()override;
};

#endif // !AI_HARD_HPP

