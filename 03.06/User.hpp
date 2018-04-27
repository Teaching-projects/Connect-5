#ifndef USER_HPP
#define USER_HPP
#include "Player.hpp"
#include "Tabla.hpp"

class User :public Player {
public:
	User();
	int* nextmove() override;
	int* nextmove(Tabla* tabla,Player* p2) override;
};

#endif // !USER_HPP

