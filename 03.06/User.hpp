#ifndef USER_HPP
#define USER_HPP
#include "Player.hpp"
#include "Tabla.hpp"
#include "CRT.h"
class User :public Player {
public:
	User();
	~User();
	int* nextmove(Tabla* tabla,Player* p2,int* move) override;
};

#endif // !USER_HPP

