#include "Ai_Hard.hpp"
#include "Jatek.hpp"
Ai_Hard::Ai_Hard():Ai() {
	
}

int* Ai_Hard::nextmove(Jatek* jatek) {
	int x, y;
	int max = 0;
	int tmp;
	int random;
	int* move;
	for (int i = 0; i < jatek->getTabla()->getSize(); i++) {
		for (int j = 0; j < jatek->getTabla()->getSize(); j++) {
			if (jatek->isValidMove(i, j)) {
				tmp = getResult(i, j, jatek);
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
	move = new int[2];
	move[0] = x;
	move[1] = y;
	return move;
}

int Ai_Hard::getResult(int x, int y, Jatek* jatek) {
	(jatek->getTabla()->getTabla())[x][y] = 1;
	int tmpx;
	int tmpy;
	int db;
	int max = 0;
	int min = 0;


	tmpx = (jatek->getPlayer(1)->get_laststeps())[0];
	tmpy = (jatek->getPlayer(1)->get_laststeps())[1];
	jatek->getPlayer(1)->set_laststeps(x, y);

	if (jatek->isFinished()) {
		jatek->getPlayer(1)->set_laststeps(tmpx, tmpy);
		(jatek->getTabla()->getTabla())[x][y] = 0;
		return 5;
	}
	else {
		db = 0;
		int i = x;
		int j = y;
		while (i>0 && j>0 && (jatek->getTabla()->getTabla())[i - 1][j] == 1) {
			i--;
		}


		while (db < 5 && i < jatek->getTabla()->getSize() && j < jatek->getTabla()->getSize()) {
			if ((jatek->getTabla()->getTabla())[i][j] == 1) {
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
				i = jatek->getTabla()->getSize();
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
		while (i>0 && j>0 && (jatek->getTabla()->getTabla())[i][j - 1] == 1) {
			j--;
		}


		while (db < 5 && i < jatek->getTabla()->getSize() && j < jatek->getTabla()->getSize()) {
			if ((jatek->getTabla()->getTabla())[i][j] == 1) {
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
				j = jatek->getTabla()->getSize();
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
		while (i>0 && j>0 && (jatek->getTabla()->getTabla())[i - 1][j - 1] == 1) {
			i--;
			j--;
		}


		while (db < 5 && i < jatek->getTabla()->getSize() && j < jatek->getTabla()->getSize()) {
			if ((jatek->getTabla()->getTabla())[i][j] == 1) {
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
				i = jatek->getTabla()->getSize();
				j = jatek->getTabla()->getSize();
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
		while (i>0 && i<jatek->getTabla()->getSize() - 1 && j>0 && j<jatek->getTabla()->getSize() - 1 && (jatek->getTabla()->getTabla())[i - 1][j + 1] == 1) {
			i--;
			j++;
		}
		while (db < 5 && i < jatek->getTabla()->getSize() && j >= 0) {
			if ((jatek->getTabla()->getTabla())[i][j] == 1) {
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
				i = jatek->getTabla()->getSize();
				j = jatek->getTabla()->getSize();
			}
		}
		if (db > max) {
			max = db;
		}
		db = 0;
	}
	jatek->getPlayer(2)->set_laststeps(tmpx, tmpy);
	(jatek->getTabla()->getTabla())[x][y] = 0;

	if (jatek->getPlayer(2)->get_laststeps()[0] != -1) min = getDefence(x, y,jatek);
	if (min >= 4 && max < min) return min;
	return max;
}

int Ai_Hard::getDefence(int x, int y,Jatek* jatek) {
	(jatek->getTabla()->getTabla())[x][y] = 2;
	int tmpx;
	int tmpy;
	int db;
	int max = 0;
	int min = 0;

	tmpx = jatek->getPlayer(2)->get_laststeps()[0];
	tmpy = jatek->getPlayer(2)->get_laststeps()[1];
	jatek->getPlayer(2)->set_laststeps(x, y);

	jatek->getTabla()->setXkov();

	if (jatek->isFinished()) {
		jatek->getPlayer(2)->set_laststeps(tmpx, tmpy);
		(jatek->getTabla()->getTabla())[x][y] = 0;
		jatek->getTabla()->setXkov();
		return 5;
	}
	else {
		db = 0;
		int i = x;
		int j = y;
		while (i>0 && j>0 && (jatek->getTabla()->getTabla())[i - 1][j] == 2) {
			i--;
		}


		while (db < 5 && i < jatek->getTabla()->getSize() && j < jatek->getTabla()->getSize()) {
			if ((jatek->getTabla()->getTabla())[i][j] == 2) {
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
				i = jatek->getTabla()->getSize();
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
		while (i>0 && j>0 && (jatek->getTabla()->getTabla())[i][j - 1] == 2) {
			j--;
		}


		while (db < 5 && i < jatek->getTabla()->getSize() && j < jatek->getTabla()->getSize()) {
			if ((jatek->getTabla()->getTabla())[i][j] == 2) {
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
				j = jatek->getTabla()->getSize();
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
		while (i>0 && j>0 && (jatek->getTabla()->getTabla())[i - 1][j - 1] == 2) {
			i--;
			j--;
		}


		while (db < 5 && i < jatek->getTabla()->getSize() && j < jatek->getTabla()->getSize()) {
			if ((jatek->getTabla()->getTabla())[i][j] == 2) {
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
				i = jatek->getTabla()->getSize();
				j = jatek->getTabla()->getSize();
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
		while (i>0 && i<jatek->getTabla()->getSize() - 1 && j>0 && j<jatek->getTabla()->getSize() - 1 && (jatek->getTabla()->getTabla())[i - 1][j + 1] == 2) {
			i--;
			j++;
		}
		while (db < 5 && i < jatek->getTabla()->getSize() && j >= 0) {
			if ((jatek->getTabla()->getTabla())[i][j] == 2) {
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
				i = jatek->getTabla()->getSize();
				j = jatek->getTabla()->getSize();
			}
		}
		if (db > max) {
			max = db;
		}
		db = 0;
	}
	jatek->getPlayer(2)->set_laststeps(tmpx, tmpy);
	(jatek->getTabla()->getTabla())[x][y] = 0;
	jatek->getTabla()->setXkov();
	return max;
}