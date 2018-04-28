#include "Main.hpp"

int main(){
	//Memory Leak ellen�rz�shez.
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	
	
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
	std::string name;
	Leaderboard* l;
	clock_t start;
	clock_t end;
	double sec;
	int* winner = new int;
	std::string time;

	l=fileBe();
	if (!l) {
		l = new Leaderboard;
		std::cout << "A leaderboard f�jl l�tre lett hozva." << std::endl;
	}
	l->sort();

	do{
		std::cout << "5 in a row j�t�k.\n\nV�lasszon j�t�km�dot!\nPvP: 1\nPvAI: 2\nLeaderboard: 3\nExit: 4" << std::endl;
		std::cin >> x;
		if (std::cin.fail()){
			std::cout << "Csak 1 �s 4 k�z�tti sz�m elfogadott." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else{
			if (x != 2 && x != 1 && x!=3 && x!=4){
				std::cout << "Csak 1 �s 4 k�z�tti sz�m elfogadott." << std::endl;
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

				if (*(winner)!=0) {
					std::cout << name << " nyert, felker�l a leaderboardra." << std::endl;
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
					std::cout << "A Leaderboard �res." << std::endl;
					std::cout << "A visszal�p�shez nyomjon meg egy gombot."<<std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.get();
					system(CLEAR);
				}
				else {
					if (l->getSize() < 10) std::cout << "A TOP " << l->getSize() << " j�t�kos:" << std::endl;
					else std::cout << "A TOP 10 j�t�kos:" << std::endl;
					std::cout << std::endl;
					for (int i = 0; i < 10 && i < l->getSize(); i++) {
						std::cout << "N�v:\t" << l->getLeaderboard().at(i)->getName() << " ,Id�:\t" << l->getLeaderboard().at(i)->getTime() << ", Neh�zs�g:\t";
						if (l->getLeaderboard().at(i)->getDiff() == 1) std::cout << "K�nny�" << std::endl;
						else std::cout << "Neh�z" << std::endl;
					}
					std::cout << std::endl;
					std::cout << "A visszal�p�shez nyomjon meg egy gombot." << std::endl;
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
	fileKi(l);
	delete l;
	delete winner;
}

int tablameret(){
	int x=0;
	bool ok = false;
	std::cout << "Adja meg a t�bla k�v�nt kezdeti m�ret�t.(8-10)\nA p�lya k�s�bb dinamikusan n�ni fog." << std::endl;
	do{

		if (!(std::cin >> x)){
			std::cout << "Csak eg�sz sz�m elfogadott." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else{
			if (x<8 || x>10){
				std::cout << "Csak 8 �s 10 k�z�tti kezd��rt�k adhat� meg." << std::endl;
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

bool PvAi(int size,int diff,int* winner){
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	bool ok = false;
	bool good = false;
	int x;
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
		if (jatek->isXkov()) std::cout << "\nX k�vetkezik: ";
		if (jatek->getPlayer(1)->nextmove(jatek->getTabla(),jatek->getPlayer(2),move)) {
			if (jatek->getMove(move[0], move[1])) {
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
				std::cout << "\nO k�vetkezik: ";
				if (jatek->getPlayer(2)->nextmove(NULL,NULL,move)) {
					if (jatek->getMove(move[0], move[1])) {
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
	std::cout << "\nSzeretne �jat j�tszani?\nIgen: 1\nNem: 2" << std::endl;
	std::cin >> x;
	system(CLEAR);
	delete move;
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
	int* move = new int[2];
	Jatek jatek(size,"Pvp",0);

	jatek.fancyPrint();
	while (!jatek.isGameOver() && !jatek.isFinished()){
		do{
			if (jatek.isXkov()) { 
				std::cout << "\nX k�vetkezik: "; 
				if (jatek.getPlayer(1)->nextmove(NULL,NULL,move)) {
					if (jatek.getMove(move[0], move[1])) {
						good = true;
					}
				}
			}
			else {
				std::cout << "\nO k�vetkezik: ";
				if (jatek.getPlayer(2)->nextmove(NULL,NULL,move)) {
					if (jatek.getMove(move[0], move[1])) {
						good = true;
					}
				}
			}	
		} while (!good);
		if (good) good = false;
		system("cls");
		jatek.fancyPrint();
	}
	if (jatek.isFinished()){
		if (!jatek.isXkov()) std::cout << "\nX nyert!" << std::endl;
		else std::cout << "\nO nyert!\n";
	}
	std::cout << "\nSzeretne �jat j�tszani?\nIgen: 1\nNem: 2\n";
	std::cin >> x;
	system(CLEAR);
	delete move;
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
	std::cout << "Adja meg a k�v�nt neh�zs�gi szintet!\nK�nny�: 1\nNeh�z: 2\n";
	do{
		if (!(std::cin >> x)){
			std::cout << "Csak eg�sz sz�m elfogadott." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else{
			if (x!=1 && x!=2){
				std::cout << "Csak 1 �s 2 adhat� meg." << std::endl;
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

Leaderboard* fileBe() {
	std::string name;
	std::string time;
	std::string diff;
	int db=0;
	int i = 0;

	std::ifstream file;
	Leaderboard* l = new Leaderboard;

	file.open("leaderboard.txt");
	if (file.is_open()) {
		while (getline(file, name)) {
			db++;
		}
		file.close();
		file.open("leaderboard.txt");

		while (i<db) {
			getline(file, name, '\t');
			getline(file, time, '\t');
			getline(file, diff, '\n');

			Entry* e = new Entry(name, time, std::stoi(diff, NULL, 10));
			l->addEntry(e);
			i++;
		}
		return l;
	}
	else {
		std::cout << "A leaderboard f�jl nem nyithat� meg." << std::endl;
		return NULL;
	}
}

void fileKi(Leaderboard* l) {
	std::ofstream file;
	file.open("leaderboard.txt");

	for (int i = 0; i < l->getSize(); i++) {
		file << l->getLeaderboard().at(i)->getName();
		file << "\t";
		file << l->getLeaderboard().at(i)->getTime();
		file << "\t";		
		file << l->getLeaderboard().at(i)->getDiff();
		file << "\n";
	}
	file.close();
}

std::string getName() {
	std::string name;
	std::cout << "Adja meg a nev�t: ";
	std::cin >> name;

	return name;
}