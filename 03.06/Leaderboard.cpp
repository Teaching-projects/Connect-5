#include "Leaderboard.hpp"

Leaderboard::Leaderboard() {};

Leaderboard::Leaderboard(std::string file):file(file) {
	std::string name;
	std::string time;
	std::string diff;
	int db = 0;
	int i = 0;

	std::ifstream File;

	File.open(file);
	if (File.is_open()) {
		while (getline(File, name)) {
			db++;
		}
		File.close();
		File.open(file);

		while (i<db) {
			getline(File, name, '\t');
			getline(File, time, '\t');
			getline(File, diff, '\n');

			Entry* e = new Entry(name, time, std::stoi(diff, NULL, 10));
			this->addEntry(e);
			i++;
		}
	}
	else {
		std::cout << "A leaderboard fájl nem nyitható meg, létre lesz hozva egy új." << std::endl;
		Leaderboard();
	}
}

Leaderboard::~Leaderboard() {
	for (unsigned int i = 0; i < leaderboard.size(); i++) {
		delete leaderboard.at(i);
	}
	leaderboard.clear();
}

std::vector<Entry*> Leaderboard::getLeaderboard() const {
	return leaderboard;
}

int Leaderboard::getSize() const {
	return leaderboard.size();
}

void Leaderboard::addEntry(Entry* e) {
	leaderboard.push_back(e);
}

static bool cmpEntry(const Entry* lhs, const Entry* rhs) { return *lhs < *rhs; }

void Leaderboard::sort() {
	std::sort(leaderboard.begin(), leaderboard.end(), cmpEntry);
}

void Leaderboard::fileKi() {
	std::ofstream File;
	File.open(this->file);

	for (int i = 0; i < this->getSize(); i++) {
		File << this->getLeaderboard().at(i)->getName();
		File << "\t";
		File << this->getLeaderboard().at(i)->getTime();
		File << "\t";
		File << this->getLeaderboard().at(i)->getDiff();
		File << "\n";
	}
	File.close();
}