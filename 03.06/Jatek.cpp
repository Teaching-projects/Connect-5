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
	if (x < 0 || x>tabla->getSize()-1 || y < 0 || y>tabla->getSize()-1) return false;
	else if ((tabla->getTabla())[x][y]!=0) return false;
	else return true;
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
	int tmpx=-1;
	int tmpy=-1;
	int szam;
	int db = 0;

	if (tabla->isXkov()){
		tmpx = (p2->get_laststeps())[0];
		tmpy = (p2->get_laststeps())[1];
		szam = 2;
	}
	else{
		tmpx = (p1->get_laststeps())[0];
		tmpy = (p1->get_laststeps())[1];
		szam = 1;
	}

	if (tmpx != -1){
		/*függõleges*/
		db = 0;
		for (int i = 0; i < tabla->getSize()-1; i++){
			if ((tabla->getTabla())[i][tmpy] == szam) db++;
			else if (db != 5){
				db = 0;
			}
		}
		if (db == 5){
			return true;
		}

		/*vízszintes*/
		db = 0;
		for (int i = 0; i < tabla->getSize()-1; i++){
			if ((tabla->getTabla())[tmpx][i] == szam) db++;
			else if (db != 5){
				db = 0;
			}
		}
		if (db == 5){
			return true;
		}


		/*fõátló*/
		db = 0;
		int i = tmpx;
		int j = tmpy;
		while (i>0 && j>0 && (tabla->getTabla())[i - 1][j - 1] == szam){
			i--;
			j--;
		}


		while (db < 5 && i < tabla->getSize() && j < tabla->getSize()){
			if ((tabla->getTabla())[i][j] == szam){
				db++;
			}
			else if (db != 5){
				db = 0;
			}
			i++;
			j++;
		}
		if (db == 5){
			return true;
		}


		/*mellékátló*/
		db = 0;
		i = tmpx;
		j = tmpy;
		while (i>0 && i<tabla->getSize()-1 && j>0 && j<tabla->getSize()-1 && (tabla->getTabla())[i - 1][j + 1] == szam){
			i--;
			j++;
		}
		while (db < 5 && i < tabla->getSize() && j>=0){
			if ((tabla->getTabla())[i][j] == szam){
				db++;
			}
			else if (db != 5){
				db = 0;
			}
			i++;
			j--;
		}
		if (db == 5){
			return true;
		}
	}
	return false;
}

int Jatek::getResult(int x, int y,int diff){
	(tabla->getTabla())[x][y] = 1;
	int tmpx;
	int tmpy;
	int db;
	int max = 0;
	int min = 0;

	tmpx = lastx[0];
	tmpy = lastx[1];
	lastx[0] = x;
	lastx[1] = y;

	if (isFinished()){
		lastx[0] = tmpx;
		lastx[1] = tmpy;
		(tabla->getTabla())[x][y] = 0;
		return 5;
	}
	else{
		db = 0;
		int i = x;
		int j = y;
		while (i>0 && j>0 && (tabla->getTabla())[i-1][j] == 1){
			i--;
		}


		while (db < 5 && i < tabla->getSize() && j < tabla->getSize()){
			if ((tabla->getTabla())[i][j] == 1){
				db++;
				i++;
			}
			else{
				if (db != 5){
					if (db > max){
						max = db;
					}
					db = 0;
				}
				i = tabla->getSize();
			}
		}
		if (db > max){
			max = db;
		}
		db = 0;


		/*vízszintes*/
		db = 0;
		i = x;
		j = y;
		while (i>0 && j>0 && (tabla->getTabla())[i][j-1] == 1){
			j--;
		}


		while (db < 5 && i < tabla->getSize() && j < tabla->getSize()){
			if ((tabla->getTabla())[i][j] == 1){
				db++;
				j++;
			}
			else{
				if (db != 5){
					if (db > max){
						max = db;
					}
					db = 0;
				}
				j = tabla->getSize();
			}
		}
		if (db > max){
			max = db;
		}
		db = 0;


		/*fõátló*/
		db = 0;
		i = x;
		j = y;
		while (i>0 && j>0 && (tabla->getTabla())[i - 1][j - 1] == 1){
			i--;
			j--;
		}


		while (db < 5 && i < tabla->getSize() && j < tabla->getSize()){
			if ((tabla->getTabla())[i][j] == 1){
				db++;
				i++;
				j++;
			}
			else{
				if (db != 5){
					if (db > max){
						max = db;
					}
					db = 0;
				}
				i = tabla->getSize();
				j = tabla->getSize();
			}
		}
		if (db > max){
			max = db;
		}
		db = 0;


		/*mellékátló*/
		db = 0;
		i = x;
		j = y;
		while (i>0 && i<tabla->getSize() - 1 && j>0 && j<tabla->getSize() - 1 && (tabla->getTabla())[i - 1][j + 1] == 1){
			i--;
			j++;
		}
		while (db < 5 && i < tabla->getSize() && j >= 0){
			if ((tabla->getTabla())[i][j] == 1){
				db++;
				i++;
				j--;
			}
			else{
				if (db != 5){
					if (db > max){
						max = db;
					}
					db = 0;
				}
				i = tabla->getSize();
				j = tabla->getSize();
			}
		}
		if (db > max){
			max = db;
		}
		db = 0;
	}
	lastx[0] = tmpx;
	lastx[1] = tmpy;
	(tabla->getTabla())[x][y] = 0;

	if (diff == 2){
		if (lasty[0] != -1) min = getDefence(x, y);
		if (min >= 4 && max < min) return min;
	}
	return max;
}

void Jatek::aiMove(int diff){
	int x, y;
	int max = 0;
	int tmp;
	int random;
	for (int i = 0; i < tabla->getSize(); i++){
		for (int j = 0; j < tabla->getSize(); j++){
			if (isValidMove(i, j)){
				tmp = getResult(i, j,diff);
				if (tmp > max){
					max = tmp;
					x = i;
					y = j;
				}
				else if (tmp == max){
					random = rand() % ((100 - 0 )+ 1) + 0;
					if (random>95){
						x = i;
						y = j;
					}
				}
			}
		}
	}
	(tabla->getTabla())[x][y] = 1;
	lastx[0] = x;
	lastx[1] = y;
	//std::cout << lastx[0] << " " << lastx[1] << "\n";


	if ((x == tabla->getSize() - 1 || y == tabla->getSize() - 1 )&& tabla->getSize()<17){
		tabla->resizeRight();
	}

	if ((x == 0 || y == 0) && tabla->getSize()<17){
		tabla->resizeLeft();
	}

	tabla->setXkov();
}


int Jatek::getDefence(int x, int y){
	(tabla->getTabla())[x][y] = 2;
	int tmpx;
	int tmpy;
	int db;
	int max = 0;
	int min = 0;

	tmpx = lasty[0];
	tmpy = lasty[1];
	lasty[0] = x;
	lasty[1] = y;
	tabla->setXkov();

	if (isFinished()){
		lasty[0] = tmpx;
		lasty[1] = tmpy;
		(tabla->getTabla())[x][y] = 0;
		tabla->setXkov();
		return 5;
	}
	else{
		db = 0;
		int i = x;
		int j = y;
		while (i>0 && j>0 && (tabla->getTabla())[i - 1][j] == 2){
			i--;
		}


		while (db < 5 && i < tabla->getSize() && j < tabla->getSize()){
			if ((tabla->getTabla())[i][j] == 2){
				db++;
				i++;
			}
			else{
				if (db != 5){
					if (db > max){
						max = db;
					}
					db = 0;
				}
				i = tabla->getSize();
			}
		}
		if (db > max){
			max = db;
		}
		db = 0;


		/*vízszintes*/
		db = 0;
		i = x;
		j = y;
		while (i>0 && j>0 && (tabla->getTabla())[i][j - 1] == 2){
			j--;
		}


		while (db < 5 && i < tabla->getSize() && j < tabla->getSize()){
			if ((tabla->getTabla())[i][j] == 2){
				db++;
				j++;
			}
			else{
				if (db != 5){
					if (db > max){
						max = db;
					}
					db = 0;
				}
				j = tabla->getSize();
			}
		}
		if (db > max){
			max = db;
		}
		db = 0;


		/*fõátló*/
		db = 0;
		i = x;
		j = y;
		while (i>0 && j>0 && (tabla->getTabla())[i - 1][j - 1] == 2){
			i--;
			j--;
		}


		while (db < 5 && i < tabla->getSize() && j < tabla->getSize()){
			if ((tabla->getTabla())[i][j] == 2){
				db++;
				i++;
				j++;
			}
			else{
				if (db != 5){
					if (db > max){
						max = db;
					}
					db = 0;
				}
				i = tabla->getSize();
				j = tabla->getSize();
			}
		}
		if (db > max){
			max = db;
		}
		db = 0;


		/*mellékátló*/
		db = 0;
		i = x;
		j = y;
		while (i>0 && i<tabla->getSize() - 1 && j>0 && j<tabla->getSize() - 1 && (tabla->getTabla())[i - 1][j + 1] == 2){
			i--;
			j++;
		}
		while (db < 5 && i < tabla->getSize() && j >= 0){
			if ((tabla->getTabla())[i][j] == 2){
				db++;
				i++;
				j--;
			}
			else{
				if (db != 5){
					if (db > max){
						max = db;
					}
					db = 0;
				}
				i = tabla->getSize();
				j = tabla->getSize();
			}
		}
		if (db > max){
			max = db;
		}
		db = 0;
	}
	lasty[0] = tmpx;
	lasty[1] = tmpy;
	(tabla->getTabla())[x][y] = 0;
	tabla->setXkov();
	return max;
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
