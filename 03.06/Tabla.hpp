#ifndef TABLA_HPP
#define TABLA_HPP
#include "Player.hpp"
#include "CRT.h"

class Tabla {
	int size;
	int **tabla;
	bool xkov;

public:
	~Tabla();
	Tabla(int size);
	bool isXkov() const;
	void setXkov();
	int **getTabla();
	void setTabla(int **ujtabla);
	void resizeRight();
	void resizeLeft();
	int getSize();
	bool isValidMove(int x, int y) const;
	bool isFinished(Player* p1,Player* p2) const;
};

#endif // !TABLA_HPP

