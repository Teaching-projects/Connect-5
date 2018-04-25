#ifndef AI_HARD_HPP
#define AI_HARD_HPP
#include "Player.hpp"

class Ai_Hard : public Player{

public:
	Ai_Hard();
	int* nextmove() override;
};

#endif // !AI_HARD_HPP

