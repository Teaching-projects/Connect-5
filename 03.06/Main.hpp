#ifndef MAIN_HPP
#define MAIN_HPP

#include "Jatek.hpp"
#include "Ai_Easy.hpp"
#include "Ai_Hard.hpp"
#include "User.hpp"
#include "CRT.h"
#include <stdlib.h>  
#include <iostream>
#include "Leaderboard.hpp"
#include <fstream>
#include <locale>
#include <time.h>

inline char separator() {
#ifdef _WIN32
	return '\\';
#else
	return '/';
#endif
}

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

void menu();
int tablameret();
bool PvAi(int size, int diff, int* winner);
bool PvP(int size);
int nehezseg();
Leaderboard* fileBe();
void fileKi(Leaderboard* l);
std::string getName();

#endif