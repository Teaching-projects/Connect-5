#include "Jatek.hpp"

Jatek::Jatek():size(10),tabla(NULL){
	tabla = new Tabla(10);
	lastx[0] = -1;
	lastx[1] = -1;
	lasty[0] = -1;
	lasty[1] = -1;
	srand(time(NULL));
}

Jatek::Jatek(int size):size(size){
	tabla = new Tabla(size);
	lastx[0] = -1;
	lastx[1] = -1;
	lasty[0] = -1;
	lasty[1] = -1;
	srand(time(NULL));
}

Jatek::Jatek(int size, std::string flag,int diff):size(size) {
	tabla = new Tabla(size);
	srand(time(NULL));

	if (flag == "Pvp") {
		p1 = new User;
		p2 = new User;
		p1->set_laststeps(-1, -1);
		p2->set_laststeps(-1, -1);
	}

	if (flag == "PvAi") {
		if (diff == 1) {
			p1 = new Ai_Easy;
			p2 = new User;
		}
		else if (diff == 2) {
			p1 = new Ai_Hard;
			p2 = new User;
		}
		p1->set_laststeps(-1, -1);
		p2->set_laststeps(-1, -1);
	}
}

Jatek::Jatek(const Jatek& j) {
	tabla = j.tabla;
	p1 = j.p1;
	p2 = j.p2;
}

Jatek::~Jatek(){
	delete p1;
	delete p2;
	delete tabla;
}

void Jatek::fancyPrint() const{
	std::cout << "| - ";
	for (int i = 0; i < tabla->getSize(); i++){
		std::cout << "| " << std::setfill(' ')<< std::setw(2) << i;
	}
	std::cout << "|\n";
	std::cout << std::setfill('-')<<std::setw(tabla->getSize()*4.5)<< "\n";
	for (int i = 0; i < tabla->getSize(); i++){
		for (int j = 0; j < tabla->getSize(); j++){
			if (j == 0) {
				std::cout << "|"<<std::setfill(' ')<<std::setw(2) << i << " | " << ((tabla->getTabla())[i][j]==1 ? 'X': (tabla->getTabla())[i][j]==2 ? 'O':' ' );
			}
			else{
				std::cout << " | " << ((tabla->getTabla())[i][j] == 1 ? 'X' : (tabla->getTabla())[i][j] == 2 ? 'O' : ' ');
			}
		}
		std::cout << " |\n";
		std::cout << std::setfill('-') << std::setw(tabla->getSize()*4.5) << "\n";
	}
}

bool Jatek::getMove(int x, int y){
	if (isValidMove(x, y)){
		if (tabla->isXkov()){
			(tabla->getTabla())[x][y] = 1;
			p1->set_laststeps(x, y);
			tabla->setXkov();
		}
		else{
			(tabla->getTabla())[x][y] = 2;
			p2->set_laststeps(x, y);
			tabla->setXkov();
		}
		if (((x == (tabla->getSize()) - 1) || y == (tabla->getSize()-1)) && tabla->getSize()<17){
			tabla->resizeRight();
		}
		if ((x == 0 || y == 0) && tabla->getSize()<17){
			tabla->resizeLeft();
		}
		return true;
	}
	else std::cout << "Hibas lepes.\n";
	return false;
}

bool Jatek::isValidMove(int x, int y) const{
	return tabla->isValidMove(x,y);
}

bool Jatek::isGameOver() const {
	for (int i = 0; i < tabla->getSize(); i++){
		for (int j = 0; j < tabla->getSize(); j++){
			if ((tabla->getTabla())[i][j]==0) return false;
		}
	}
	return true;
}

bool Jatek::isFinished() const{
	return tabla->isFinished(p1, p2);
}

Player* Jatek::getPlayer(int number)const {
	if (number == 1) return p1;
	else if (number == 2) return p2;
	else return NULL;
}

bool Jatek::isXkov() const {
	return tabla->isXkov();
}

void Jatek::setXkov() {
	tabla->setXkov();
}

Tabla* Jatek::getTabla() {
	return tabla;
}
