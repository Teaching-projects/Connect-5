#include "Jatek.hpp"

Jatek::Jatek():size(10),tabla(NULL){
	tabla = new int*[size];
	for (int i = 0; i < size; i++){
		tabla[i] = new int[size];
	}
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			tabla[i][j] = 0;
		}
	}
	xkov = true;
	lastx[0] = -1;
	lastx[1] = -1;
	lasty[0] = -1;
	lasty[1] = -1;
	srand(time(NULL));
}

Jatek::Jatek(int size):size(size){
	tabla = new int*[size];
	for (int i = 0; i < size; i++){
		tabla[i] = new int[size];
	}
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			tabla[i][j] = 0;
		}
	}
	xkov = true;
	lastx[0] = -1;
	lastx[1] = -1;
	lasty[0] = -1;
	lasty[1] = -1;
	srand(time(NULL));
}

Jatek::~Jatek(){
	for (int i = 0; i < size; i++){
		delete(tabla[i]);
	}
	delete tabla;
}

void Jatek::print() const{
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			std::cout << tabla[i][j]<<" ";
		}
		std::cout << "\n";
	}
}

void Jatek::fancyPrint() const{
	std::cout << "| - ";
	for (int i = 0; i < size; i++){
		std::cout << "| " << std::setfill(' ')<< std::setw(2) << i;
	}
	std::cout << "|\n";
	std::cout << std::setfill('-')<<std::setw(size*4.5)<< "\n";
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (j == 0) {
				std::cout << "|"<<std::setfill(' ')<<std::setw(2) << i << " | " << (tabla[i][j]==1 ? 'X': tabla[i][j]==2 ? 'O':' ' );
			}
			else{
				std::cout << " | " << (tabla[i][j] == 1 ? 'X' : tabla[i][j] == 2 ? 'O' : ' ');
			}
		}
		std::cout << " |\n";
		std::cout << std::setfill('-') << std::setw(size*4.5) << "\n";
	}
}

bool Jatek::getMove(int x, int y){
	if (isValidMove(x, y)){
		if (isXkov()){
			tabla[x][y] = 1;
			lastx[0] = x;
			lastx[1] = y;
			setXkov();
		}
		else{
			tabla[x][y] = 2;
			lasty[0] = x;
			lasty[1] = y;
			setXkov();
		}
		if ((x == size - 1 || y == size - 1) && size<17){
			resizeRight();
		}
		if ((x == 0 || y == 0) && size<17){
			resizeLeft();
		}
		return true;
	}
	else std::cout << "Hibas lepes.\n";
	return false;
}

bool Jatek::isValidMove(int x, int y) const{
	if (x < 0 || x>size-1 || y < 0 || y>size-1) return false;
	else if (tabla[x][y]!=0) return false;
	else return true;
}

bool Jatek::isGameOver() const {
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (tabla[i][j]==0) return false;
		}
	}
	return true;
}

bool Jatek::isXkov() const{
	return xkov;
}

void Jatek::setXkov(){
	if (isXkov()) xkov = false;
	else xkov = true;
}

bool Jatek::isFinished() const{
	int tmpx=-1;
	int tmpy=-1;
	int szam;
	int db = 0;

	if (isXkov()){
		tmpx = lasty[0];
		tmpy = lasty[1];
		szam = 2;
	}
	else{
		tmpx = lastx[0];
		tmpy = lastx[1];
		szam = 1;
	}

	if (tmpx != -1){
		/*függõleges*/
		db = 0;
		for (int i = 0; i < size-1; i++){
			if (tabla[i][tmpy] == szam) db++;
			else if (db != 5){
				db = 0;
			}
		}
		if (db == 5){
			return true;
		}

		/*vízszintes*/
		db = 0;
		for (int i = 0; i < size-1; i++){
			if (tabla[tmpx][i] == szam) db++;
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
		while (i>0 && j>0 && tabla[i - 1][j - 1] == szam){
			i--;
			j--;
		}


		while (db < 5 && i < size && j < size){
			if (tabla[i][j] == szam){
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
		while (i>0 && i<size-1 && j>0 && j<size-1 && tabla[i - 1][j + 1] == szam){
			i--;
			j++;
		}
		while (db < 5 && i < size && j>=0){
			if (tabla[i][j] == szam){
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

void Jatek::resizeRight(){
	size++;
	int **ujtabla = new int*[size];
	for (int i = 0; i < size; i++){
		ujtabla[i] = new int[size];
		for (int j = 0; j < size; j++){
			ujtabla[i][j] = 0;
		}
	}

	for (int i = 0; i < size - 1; i++){
		for (int j = 0; j < size - 1; j++){
			ujtabla[i][j] = tabla[i][j];
		}
		delete(tabla[i]);
	}
	delete tabla;
	tabla = ujtabla;
}

void Jatek::resizeLeft(){
	size++;
	int **ujtabla = new int*[size];
	for (int i = 0; i < size; i++){
		ujtabla[i] = new int[size];
		for (int j = 0; j < size; j++){
			ujtabla[i][j] = 0;
		}
	}

	for (int i = 0; i < size-1; i++){
		for (int j = 0; j < size-1; j++){
			ujtabla[i+1][j+1] = tabla[i][j];
		}
		delete(tabla[i]);
	}
	delete tabla;
	tabla = ujtabla;
}

int Jatek::getResult(int x, int y,int diff){
	tabla[x][y] = 1;
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
		tabla[x][y] = 0;
		return 5;
	}
	else{
		db = 0;
		int i = x;
		int j = y;
		while (i>0 && j>0 && tabla[i-1][j] == 1){
			i--;
		}


		while (db < 5 && i < size && j < size){
			if (tabla[i][j] == 1){
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
				i = size;
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
		while (i>0 && j>0 && tabla[i][j-1] == 1){
			j--;
		}


		while (db < 5 && i < size && j < size){
			if (tabla[i][j] == 1){
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
				j = size;
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
		while (i>0 && j>0 && tabla[i - 1][j - 1] == 1){
			i--;
			j--;
		}


		while (db < 5 && i < size && j < size){
			if (tabla[i][j] == 1){
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
				i = size;
				j = size;
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
		while (i>0 && i<size - 1 && j>0 && j<size - 1 && tabla[i - 1][j + 1] == 1){
			i--;
			j++;
		}
		while (db < 5 && i < size && j >= 0){
			if (tabla[i][j] == 1){
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
				i = size;
				j = size;
			}
		}
		if (db > max){
			max = db;
		}
		db = 0;
	}
	lastx[0] = tmpx;
	lastx[1] = tmpy;
	tabla[x][y] = 0;

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
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
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
	tabla[x][y] = 1;
	lastx[0] = x;
	lastx[1] = y;
	//std::cout << lastx[0] << " " << lastx[1] << "\n";


	if ((x == size - 1 || y == size - 1 )&& size<17){
		resizeRight();
	}

	if ((x == 0 || y == 0) && size<17){
		resizeLeft();
	}

	setXkov();
}


int Jatek::getDefence(int x, int y){
	tabla[x][y] = 2;
	int tmpx;
	int tmpy;
	int db;
	int max = 0;
	int min = 0;

	tmpx = lasty[0];
	tmpy = lasty[1];
	lasty[0] = x;
	lasty[1] = y;
	setXkov();

	if (isFinished()){
		lasty[0] = tmpx;
		lasty[1] = tmpy;
		tabla[x][y] = 0;
		setXkov();
		return 5;
	}
	else{
		db = 0;
		int i = x;
		int j = y;
		while (i>0 && j>0 && tabla[i - 1][j] == 2){
			i--;
		}


		while (db < 5 && i < size && j < size){
			if (tabla[i][j] == 2){
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
				i = size;
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
		while (i>0 && j>0 && tabla[i][j - 1] == 2){
			j--;
		}


		while (db < 5 && i < size && j < size){
			if (tabla[i][j] == 2){
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
				j = size;
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
		while (i>0 && j>0 && tabla[i - 1][j - 1] == 2){
			i--;
			j--;
		}


		while (db < 5 && i < size && j < size){
			if (tabla[i][j] == 2){
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
				i = size;
				j = size;
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
		while (i>0 && i<size - 1 && j>0 && j<size - 1 && tabla[i - 1][j + 1] == 2){
			i--;
			j++;
		}
		while (db < 5 && i < size && j >= 0){
			if (tabla[i][j] == 2){
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
				i = size;
				j = size;
			}
		}
		if (db > max){
			max = db;
		}
		db = 0;
	}
	lasty[0] = tmpx;
	lasty[1] = tmpy;
	tabla[x][y] = 0;
	setXkov();
	return max;
}
