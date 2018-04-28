#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP
#include "Entry.hpp"
#include <vector>
#include <algorithm>
#include <functional>

class Leaderboard {
	std::vector<Entry*> leaderboard;

public:
	Leaderboard();
	~Leaderboard();
	std::vector<Entry*> getLeaderboard() const;
	int getSize() const;
	void addEntry(Entry* e);
	void sort();
};
#endif
