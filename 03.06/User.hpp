#ifndef USER_HPP
#define USER_HPP
#include "Player.hpp"
#include "Tabla.hpp"
#include <limits> 
#include "CRT.h"
class User :public Player {
public:
	User();
	~User();
	step nextmove(Tabla* tabla,Player* p2) override;
};

#endif // !USER_HPP

