#include "User.hpp"

User::User():Player(){

}

int* User::nextmove(){
	int x;
	int y;
	int *move;

	std::cin >> x;
	if (std::cin.good()) {
		std::cin >> y;
		if (std::cin.good()) {
			move = new int[2];
			move[0] = x;
			move[1] = y;
			return move;
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Csak egész szaám adható meg.\n";
			return NULL;
		}
	}
	else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Csak egész szám adható meg.\n";
		return NULL;
	}
}

int* User::nextmove(Jatek* jatek) {
	return NULL;
}