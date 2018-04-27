#ifndef USER_HPP
#define USER_HPP
#include "Player.hpp"

class User :public Player {
public:
	User();
	int* nextmove() override;
	int* nextmove(Jatek* jatek) override;
};

#endif // !USER_HPP

