#ifndef AI_HPP
#define AI_HPP
#include "Player.hpp"
class Jatek;

class Ai : public Player{
public:
	Ai();
	int* nextmove() override;
	virtual int getResult(int x, int y,Jatek* jatek)=0;
};
#endif // !AI_HPP

