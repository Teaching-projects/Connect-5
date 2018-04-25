#ifndef JATEK HPP
#define JATEK HPP

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <locale>
#include "User.hpp"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

class Jatek{
	int **tabla;
	bool xkov;
	int lastx[2];
	int lasty[2];
	int size;
	Player * p1;
	Player * p2;



public:
	Jatek();
	Jatek(int size);
	Jatek(int size, std::string flag);
	~Jatek();
	Player* getPlayer(int number) const;
	void print() const;
	void fancyPrint() const;
	bool getMove(int x, int y);
	bool isValidMove(int x, int y) const;
	bool isGameOver() const;
	bool isXkov() const;
	void setXkov();
	bool isFinished() const;
	void resizeRight();
	void resizeLeft();
	int getResult(int x, int y,int diff);
	void aiMove(int diff);
	int getDefence(int x, int y);
};
#endif