#include "Ai.hpp"

Ai::Ai():Player(){}

int* Ai::nextmove(Tabla* tabla, Player* p2,int* move) {
	int x, y;
	int max = 0;
	int tmp;
	int random;
	for (int i = 0; i < tabla->getSize(); i++) {
		for (int j = 0; j < tabla->getSize(); j++) {
			if (tabla->isValidMove(i, j)) {
				tmp = getResult(i, j, tabla,p2);
				if (tmp > max) {
					max = tmp;
					x = i;
					y = j;
				}
				else if (tmp == max) {
					random = rand() % ((100 - 0) + 1) + 0;
					if (random>95) {
						x = i;
						y = j;
					}
				}
			}
		}
	}
	move[0] = x;
	move[1] = y;
	return move;
}

Ai::~Ai(){}
