#include "Jatek.hpp"
#include "Ai_Easy.hpp"
#include "Ai_Hard.hpp"
#include "User.hpp"

void menu();
int tablameret();
bool PvAi(int size,int diff);
bool PvP(int size);
int nehezseg();

int main(){
	/*
	Player* p1;
	Player* p2;

	p1 = new User;
	p2 = new Ai_Easy;

	std::cout<< (p1->get_laststeps())[0];
	std::cout << (p1->get_laststeps())[0];
	*/


	menu();
	return 0;
}

void menu(){
	setlocale(LC_ALL, "");
	system(CLEAR);
	int x = 0;
	bool ok = false;
	bool good = false;
	int size;
	int diff;

	do{
		std::cout << "5 in a row játék.\n\nVálasszon játékmódot!\nPvP: 1\nPvAI: 2\nExit: 3\n";
		std::cin >> x;
		if (std::cin.fail()){
			std::cout << "Csak 1 és 3 közötti szám elfogadott.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else{
			if (x != 2 && x != 1 && x!=3){
				std::cout << "Csak 1-es és 2-es szám elfogadott.\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else if (x == 1){
				size = tablameret();
				if (!PvP(size)) ok = true;
			}
			else if(x==2){
				diff = nehezseg();
				size = tablameret();
				if (!PvAi(size,diff)) ok = true;
			}
			else ok = true;
		}
	} while (!ok);
	if (ok) ok = false;
}

int tablameret(){
	int x=0;
	bool ok = false;
	std::cout << "Adja meg a tábla kívánt kezdeti méretét.(8-10)\nA pálya késõbb dinamikusan nõni fog.\n";
	do{

		if (!(std::cin >> x)){
			std::cout << "Csak egész szám elfogadott.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else{
			if (x<8 || x>10){
				std::cout << "Csak 8 és 10 közötti kezdõérték adható meg.\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else{
				return x;
				ok = true;
			}
		}
	} while (!ok);
}

bool PvAi(int size,int diff){
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	bool ok = false;
	bool good = false;
	int x;
	int y;
	int *move = new int[2];
	Jatek *jatek;

	if (diff == 1) {
		jatek=new Jatek(size,"PvAi",1);
	}
	else if (diff==2){
		jatek = new Jatek(size, "PvAi", 2);
	}


	jatek->fancyPrint();
	while (!jatek->isGameOver() && !ok){
		if (jatek->isXkov()) std::cout << "\nX következik: \n";
		jatek->aiMove(diff);
		system(CLEAR);
		jatek->fancyPrint();
		if (jatek->isFinished()){
			ok = true;
			std::cout << "\nX nyert!!!\n";
		}
		else{
			do{
				std::cout << "\nO következik: ";
				if (move = jatek->getPlayer(2)->nextmove()) {
					if (jatek->getMove(move[0], move[1])) {
						good = true;
						system(CLEAR);
						jatek->fancyPrint();
						if (jatek->isFinished()) {
							ok = true;
							std::cout << "\nO nyert!!!\n";
						}
					}
				}
			} while (!good);
			if (good) good = false;
		}
	}
	std::cout << "\nSzeretne újat játszani?\nIgen: 1\nNem: 2\n";
	std::cin >> x;
	system(CLEAR);
	if (std::cin.good()){
		if (x == 1) return true;
		else return false;
	}
	else return false;
}

bool PvP(int size){
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	bool good = false;
	int x;
	int* move = new int[2];
	Jatek jatek(size,"Pvp",0);

	jatek.fancyPrint();
	while (!jatek.isGameOver() && !jatek.isFinished()){
		do{
			if (jatek.isXkov()) { 
				std::cout << "\nX következik: \n"; 
				if (move=jatek.getPlayer(1)->nextmove()) {
					if (jatek.getMove(move[0], move[1])) {
						good = true;
					}
				}
			}
			else {
				std::cout << "\nO következik: \n";
				if (move = jatek.getPlayer(2)->nextmove()) {
					if (jatek.getMove(move[0], move[1])) {
						good = true;
					}
				}
			}	
		} while (!good);
		if (good) good = false;
		jatek.fancyPrint();
	}
	if (jatek.isFinished()){
		if (!jatek.isXkov()) std::cout << "\nX nyert!\n";
		else std::cout << "\nO nyert!\n";
	}
	std::cout << "\nSzeretne újat játszani?\nIgen: 1\nNem: 2\n";
	std::cin >> x;
	system(CLEAR);
	if (std::cin.good()){
		if (x == 1) return true;
		else return false;
	}
	else return false;
}

int nehezseg(){
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	int x = 0;
	bool ok = false;
	std::cout << "Adja meg a kívánt nehézségi szintet!\nKönnyû: 1\nNehéz: 2\n";
	do{
		if (!(std::cin >> x)){
			std::cout << "Csak egész szám elfogadott.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else{
			if (x!=1 && x!=2){
				std::cout << "Csak 1 és 2 adható meg.\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else{
				return x;
				ok = true;
			}
		}
	} while (!ok);
}

