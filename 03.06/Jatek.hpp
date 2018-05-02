#ifndef JATEK_HPP
#define JATEK_HPP

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <locale>
#include "User.hpp"
#include "Ai_Easy.hpp"
#include "Ai_Hard.hpp"
#include "Tabla.hpp"
#include "CRT.h"

class Jatek{
	int size;
	Tabla *tabla;
	int lastx[2];
	int lasty[2];
	Player* p1;
	Player* p2;

public:
	Jatek();
	Jatek(int size);
	Jatek(int size, std::string flag,int diff);
	Jatek(const Jatek& j);
	~Jatek();
	Player* getPlayer(int number) const;
	void fancyPrint() const;
	bool getMove(int x, int y);
	bool isValidMove(int x, int y) const;
	bool isGameOver() const;
	bool isFinished() const;
	bool isXkov() const;
	void setXkov();
	Tabla* getTabla();
};
#endif