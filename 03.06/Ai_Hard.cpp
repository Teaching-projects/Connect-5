#include "Ai_Hard.hpp"
#include "Jatek.hpp"

Ai_Hard::Ai_Hard():Ai() {}

int Ai_Hard::getResult(int x, int y, Tabla* tabla,Player* p2) {
	(tabla->getTabla())[x][y] = 1;
	int tmpx;
	int tmpy;
	int db;
	int max = 0;
	int min = 0;


	tmpx = (this->get_laststeps())[0];
	tmpy = (this->get_laststeps())[1];
	this->set_laststeps(x, y);

	if (tabla->isFinished(this,p2)) {
		this->set_laststeps(tmpx, tmpy);
		(tabla->getTabla())[x][y] = 0;
		return 5;
	}
	else {
		db = 0;
		int i = x;
		int j = y;
		while (i>0 && j>0 && (tabla->getTabla())[i - 1][j] == 1) {
			i--;
		}


		while (db < 5 && i < tabla->getSize() && j < tabla->getSize()) {
			if ((tabla->getTabla())[i][j] == 1) {
				db++;
				i++;
			}
			else {
				if (db != 5) {
					if (db > max) {
						max = db;
					}
					db = 0;
				}
				i = tabla->getSize();
			}
		}
		if (db > max) {
			max = db;
		}
		db = 0;


		/*vízszintes*/
		db = 0;
		i = x;
		j = y;
		while (i>0 && j>0 && (tabla->getTabla())[i][j - 1] == 1) {
			j--;
		}


		while (db < 5 && i < tabla->getSize() && j < tabla->getSize()) {
			if ((tabla->getTabla())[i][j] == 1) {
				db++;
				j++;
			}
			else {
				if (db != 5) {
					if (db > max) {
						max = db;
					}
					db = 0;
				}
				j = tabla->getSize();
			}
		}
		if (db > max) {
			max = db;
		}
		db = 0;


		/*fõátló*/
		db = 0;
		i = x;
		j = y;
		while (i>0 && j>0 && (tabla->getTabla())[i - 1][j - 1] == 1) {
			i--;
			j--;
		}


		while (db < 5 && i < tabla->getSize() && j < tabla->getSize()) {
			if ((tabla->getTabla())[i][j] == 1) {
				db++;
				i++;
				j++;
			}
			else {
				if (db != 5) {
					if (db > max) {
						max = db;
					}
					db = 0;
				}
				i = tabla->getSize();
				j = tabla->getSize();
			}
		}
		if (db > max) {
			max = db;
		}
		db = 0;


		/*mellékátló*/
		db = 0;
		i = x;
		j = y;
		while (i>0 && i<tabla->getSize() - 1 && j>0 && j<tabla->getSize() - 1 && (tabla->getTabla())[i - 1][j + 1] == 1) {
			i--;
			j++;
		}
		while (db < 5 && i < tabla->getSize() && j >= 0) {
			if ((tabla->getTabla())[i][j] == 1) {
				db++;
				i++;
				j--;
			}
			else {
				if (db != 5) {
					if (db > max) {
						max = db;
					}
					db = 0;
				}
				i = tabla->getSize();
				j = tabla->getSize();
			}
		}
		if (db > max) {
			max = db;
		}
		db = 0;
	}
	this->set_laststeps(tmpx, tmpy);
	(tabla->getTabla())[x][y] = 0;

	if (p2->get_laststeps()[0] != -1) min = getDefence(x, y,tabla,p2);
	if (min >= 4 && max < min) return min;
	return max;
}

int Ai_Hard::getDefence(int x, int y,Tabla* tabla,Player* p2) {
	(tabla->getTabla())[x][y] = 2;
	int tmpx;
	int tmpy;
	int db;
	int max = 0;

	tmpx = p2->get_laststeps()[0];
	tmpy = p2->get_laststeps()[1];
	p2->set_laststeps(x, y);

	tabla->setXkov();

	if (tabla->isFinished(this,p2)) {
		p2->set_laststeps(tmpx, tmpy);
		(tabla->getTabla())[x][y] = 0;
		tabla->setXkov();
		return 5;
	}
	else {
		db = 0;
		int i = x;
		int j = y;
		while (i>0 && j>0 && (tabla->getTabla())[i - 1][j] == 2) {
			i--;
		}


		while (db < 5 && i < tabla->getSize() && j < tabla->getSize()) {
			if ((tabla->getTabla())[i][j] == 2) {
				db++;
				i++;
			}
			else {
				if (db != 5) {
					if (db > max) {
						max = db;
					}
					db = 0;
				}
				i = tabla->getSize();
			}
		}
		if (db > max) {
			max = db;
		}
		db = 0;


		/*vízszintes*/
		db = 0;
		i = x;
		j = y;
		while (i>0 && j>0 && (tabla->getTabla())[i][j - 1] == 2) {
			j--;
		}


		while (db < 5 && i < tabla->getSize() && j < tabla->getSize()) {
			if ((tabla->getTabla())[i][j] == 2) {
				db++;
				j++;
			}
			else {
				if (db != 5) {
					if (db > max) {
						max = db;
					}
					db = 0;
				}
				j = tabla->getSize();
			}
		}
		if (db > max) {
			max = db;
		}
		db = 0;


		/*fõátló*/
		db = 0;
		i = x;
		j = y;
		while (i>0 && j>0 && (tabla->getTabla())[i - 1][j - 1] == 2) {
			i--;
			j--;
		}


		while (db < 5 && i < tabla->getSize() && j < tabla->getSize()) {
			if ((tabla->getTabla())[i][j] == 2) {
				db++;
				i++;
				j++;
			}
			else {
				if (db != 5) {
					if (db > max) {
						max = db;
					}
					db = 0;
				}
				i = tabla->getSize();
				j = tabla->getSize();
			}
		}
		if (db > max) {
			max = db;
		}
		db = 0;


		/*mellékátló*/
		db = 0;
		i = x;
		j = y;
		while (i>0 && i<tabla->getSize() - 1 && j>0 && j<tabla->getSize() - 1 && (tabla->getTabla())[i - 1][j + 1] == 2) {
			i--;
			j++;
		}
		while (db < 5 && i < tabla->getSize() && j >= 0) {
			if ((tabla->getTabla())[i][j] == 2) {
				db++;
				i++;
				j--;
			}
			else {
				if (db != 5) {
					if (db > max) {
						max = db;
					}
					db = 0;
				}
				i = tabla->getSize();
				j = tabla->getSize();
			}
		}
		if (db > max) {
			max = db;
		}
		db = 0;
	}
	p2->set_laststeps(tmpx, tmpy);
	(tabla->getTabla())[x][y] = 0;
	tabla->setXkov();
	return max;
}

Ai_Hard::~Ai_Hard(){}