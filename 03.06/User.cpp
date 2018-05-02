#include "User.hpp"

User::User():Player(){}

step User::nextmove(Tabla* tabla, Player* p2){
	int x;
	int y;

	std::cin >> x;
	if (std::cin.good()) {
		std::cin >> y;
		if (std::cin.good()) {
			set_laststeps(x, y);
			return get_laststeps();
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Csak egész szaám adható meg.\n";
			return step();
		}
	}
	else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Csak egész szám adható meg.\n";
		return step();
	}
}

User::~User() {}