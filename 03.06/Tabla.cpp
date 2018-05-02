#include "Tabla.hpp"

Tabla::Tabla(int size) :size(size) {
	tabla = new int*[size];
	for (int i = 0; i < size; i++) {
		tabla[i] = new int[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tabla[i][j] = 0;
		}
	}
	xkov = true;
}

int** Tabla::getTabla(){
	return tabla;
}

void Tabla::setTabla(int **ujtabla) {
	tabla = ujtabla;
}


bool Tabla::isXkov() const {
	return xkov;
}
void Tabla::setXkov() {
	if (isXkov()) xkov = false;
	else xkov = true;
}

void Tabla::resizeRight() {
	size++;
	int **ujtabla = new int*[size];
	for (int i = 0; i < size; i++) {
		ujtabla[i] = new int[size];
		for (int j = 0; j < size; j++) {
			ujtabla[i][j] = 0;
		}
	}

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1; j++) {
			ujtabla[i][j] = tabla[i][j];
		}
		delete[] tabla[i];
	}
	delete[] tabla;
	tabla=ujtabla;
}
void Tabla::resizeLeft() {
	size++;
	int **ujtabla = new int*[size];
	for (int i = 0; i < size; i++) {
		ujtabla[i] = new int[size];
		for (int j = 0; j < size; j++) {
			ujtabla[i][j] = 0;
		}
	}

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1; j++) {
			ujtabla[i + 1][j + 1] = tabla[i][j];
		}
		delete[] tabla[i];
	}
	delete[] tabla;
	tabla=ujtabla;
}

int Tabla::getSize() {
	return size;
}

bool Tabla::isValidMove(int x, int y) const {
	if (x < 0 || x>size - 1 || y < 0 || y>size - 1) return false;
	else if (tabla[x][y] != 0) return false;
	else return true;
}

bool Tabla::isFinished(Player* p1, Player* p2) const {
	int tmpx = -1;
	int tmpy = -1;
	int szam;
	int db = 0;

	if (isXkov()) {
		tmpx = (p2->get_laststeps()).x;
		tmpy = (p2->get_laststeps()).y;
		szam = 2;
	}
	else {
		tmpx = (p1->get_laststeps()).x;
		tmpy = (p1->get_laststeps()).y;
		szam = 1;
	}

	if (tmpx != -1) {
		/*függõleges*/
		db = 0;
		for (int i = 0; i < size - 1; i++) {
			if (tabla[i][tmpy] == szam) db++;
			else if (db != 5) {
				db = 0;
			}
		}
		if (db == 5) {
			return true;
		}

		/*vízszintes*/
		db = 0;
		for (int i = 0; i < size - 1; i++) {
			if (tabla[tmpx][i] == szam) db++;
			else if (db != 5) {
				db = 0;
			}
		}
		if (db == 5) {
			return true;
		}


		/*fõátló*/
		db = 0;
		int i = tmpx;
		int j = tmpy;
		while (i>0 && j>0 && tabla[i - 1][j - 1] == szam) {
			i--;
			j--;
		}


		while (db < 5 && i < size && j < size) {
			if (tabla[i][j] == szam) {
				db++;
			}
			else if (db != 5) {
				db = 0;
			}
			i++;
			j++;
		}
		if (db == 5) {
			return true;
		}


		/*mellékátló*/
		db = 0;
		i = tmpx;
		j = tmpy;
		while (i>0 && i<size - 1 && j>0 && j<size - 1 && tabla[i - 1][j + 1] == szam) {
			i--;
			j++;
		}
		while (db < 5 && i < size && j >= 0) {
			if (tabla[i][j] == szam) {
				db++;
			}
			else if (db != 5) {
				db = 0;
			}
			i++;
			j--;
		}
		if (db == 5) {
			return true;
		}
	}
	return false;
}

Tabla::~Tabla() {
	for (int i = 0; i < size; i++) {
		delete[] tabla[i];
	}
	delete[] tabla;
}