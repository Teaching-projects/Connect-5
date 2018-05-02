#include "Main.hpp"

int main(){
	//Memory Leak ellenőrzéshez.
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	
	
	menu();
	return 0;
}

void menu(){
	setlocale(LC_ALL, "");
	system(CLEAR);
	int x = 0;
	bool ok = false;
	int size;
	int diff;
	std::string name;
	Leaderboard* l;
	int start;
	int end;
	double sec;
	int* winner = new int;
	std::string time;

	l = new Leaderboard("leaderboard.txt");
	l->sort();

	do{
		std::cout << "5 in a row játék.\n\nVálasszon játékmódot!\nPvP: 1\nPvAI: 2\nLeaderboard: 3\nExit: 4" << std::endl;
		std::cin >> x;
		if (std::cin.fail()){
			std::cout << "Csak 1 és 4 közötti szám elfogadott." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else{
			if (x != 2 && x != 1 && x!=3 && x!=4){
				std::cout << "Csak 1 és 4 közötti szám elfogadott." << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else if (x == 1){
				size = tablameret();
				if (!PvP(size)) ok = true;
			}
			else if(x==2){
				name = getName();
				std::cout << std::endl;
				diff = nehezseg();
				size = tablameret();
				
				start = clock();
				if (!PvAi(size,diff,winner)) ok = true;
				end = clock();

				if (*(winner) != 0) {
					std::cout << name << " nyert, felkerül a leaderboardra." << std::endl;
					sec = (double)((end - start) / CLOCKS_PER_SEC);
					time.append(std::to_string((int)(sec / 60)));
					time.append(":");
					if ((((int)sec) % 60) < 10) {
						time.append("0");
					}
					time.append(std::to_string((int)sec % 60));
					Entry* e = new Entry(name, time, diff);
					l->addEntry(e);
				}
			}
			else if (x == 3) {
				if (l->getSize() == 0) {
					std::cout << "A Leaderboard üres." << std::endl;
					std::cout << "A visszalépéshez nyomjon meg egy gombot."<<std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.get();
					system(CLEAR);
				}
				else {
					if (l->getSize() < 10) std::cout << "A TOP " << l->getSize() << " játékos:" << std::endl;
					else std::cout << "A TOP 10 játékos:" << std::endl;
					std::cout << std::endl;
					for (int i = 0; i < 10 && i < l->getSize(); i++) {
						std::cout << "Név:\t" << l->getLeaderboard().at(i)->getName() << " ,Idő:\t" << l->getLeaderboard().at(i)->getTime() << ", Nehézség:\t";
						if (l->getLeaderboard().at(i)->getDiff() == 1) std::cout << "Könnyű" << std::endl;
						else std::cout << "Nehéz" << std::endl;
					}
					std::cout << std::endl;
					std::cout << "A visszalépéshez nyomjon meg egy gombot." << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.get();
					system(CLEAR);
				}
			}
			else ok = true;
		}
	} while (!ok);
	if (ok) ok = false;
	l->sort();
	l->fileKi();
	delete l;
	delete winner;
}

int tablameret(){
	int x=0;
	bool ok = false;
	std::cout << "Adja meg a tábla kívánt kezdeti méretét.(8-10)\nA pálya később dinamikusan nőni fog." << std::endl;
	do{

		if (!(std::cin >> x)){
			std::cout << "Csak egész szám elfogadott." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else{
			if (x<8 || x>10){
				std::cout << "Csak 8 és 10 közötti kezdőérték adható meg." << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else{
				return x;
				ok = true;
			}
		}
	} while (!ok);
	return 0;
}

bool PvAi(int size,int diff,int* winner){
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	bool ok = false;
	bool good = false;
	int x;
	Jatek *jatek;

	step move;

	if (diff == 1) {
		jatek=new Jatek(size,"PvAi",1);
	}
	else if (diff==2){
		jatek = new Jatek(size, "PvAi", 2);
	}

	jatek->fancyPrint();
	while (!jatek->isGameOver() && !ok){
		if (jatek->isXkov()) std::cout << "\nX következik: \n";
		move = jatek->getPlayer(1)->nextmove(jatek->getTabla(), jatek->getPlayer(2));
		if (move.x!=-1) {
			if (jatek->getMove(move.x, move.y)) {
				system(CLEAR);
				jatek->fancyPrint();
			}
		}
		if (jatek->isFinished()){
			ok = true;
			std::cout << "\nX nyert!!!" << std::endl;
			*winner = 0;
		}
		else{
			do{
				std::cout << "\nO következik: \n";
				move = jatek->getPlayer(2)->nextmove(NULL, NULL);
				if (move.x!=-1) {
					if (jatek->getMove(move.x, move.y)) {
						good = true;
						system(CLEAR);
						jatek->fancyPrint();
						if (jatek->isFinished()) {
							ok = true;
							std::cout << "\nO nyert!!!" << std::endl;
							*winner = 1;
						}
					}
				}
			} while (!good);
			if (good) good = false;
		}
	}
	std::cout << "\nSzeretne újat játszani?\nIgen: 1\nNem: 2" << std::endl;
	std::cin >> x;
	system(CLEAR);
	delete jatek;
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
	Jatek jatek(size,"Pvp",0);
	step move;

	jatek.fancyPrint();
	while (!jatek.isGameOver() && !jatek.isFinished()){
		do{
			if (jatek.isXkov()) { 
				std::cout << "\nX következik: \n"; 
				move = jatek.getPlayer(1)->nextmove(NULL, NULL);
				if (move.x!=-1) {
					if (jatek.getMove(move.x, move.y)) {
						good = true;
					}
				}
			}
			else {
				std::cout << "\nO következik: \n";
				move = jatek.getPlayer(2)->nextmove(NULL, NULL);
				if (move.x!=-1) {
					if (jatek.getMove(move.x, move.y)) {
						good = true;
					}
				}
			}	
		} while (!good);
		if (good) good = false;
		system(CLEAR);
		jatek.fancyPrint();
	}
	if (jatek.isFinished()){
		if (!jatek.isXkov()) std::cout << "\nX nyert!" << std::endl;
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
	std::cout << "Adja meg a kívánt nehézségi szintet!\nKönnyű: 1\nNehéz: 2\n";
	do{
		if (!(std::cin >> x)){
			std::cout << "Csak egész szám elfogadott." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else{
			if (x!=1 && x!=2){
				std::cout << "Csak 1 és 2 adható meg." << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else{
				return x;
				ok = true;
			}
		}
	} while (!ok);
	return 0;
}

std::string getName() {
	std::string name;
	std::cout << "Adja meg a nevét: ";
	std::cin >> name;

	return name;
}
