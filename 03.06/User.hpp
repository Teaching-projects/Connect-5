#ifndef USER_HPP
#define USER_HPP
#include "Player.hpp"
#include <iostream>

class User :public Player {
public:
	User();
	int* nextmove() override;
};

#endif // !USER_HPP

