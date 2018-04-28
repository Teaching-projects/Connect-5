#include "Leaderboard.hpp"

Leaderboard::Leaderboard() {}

Leaderboard::~Leaderboard() {
	for (int i = 0; i < leaderboard.size(); i++) {
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