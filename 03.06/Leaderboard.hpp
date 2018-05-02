#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP
#include "Entry.hpp"
#include <vector>
#include <algorithm>
#include <functional>
#include <fstream>
#include <iostream>
#include <string>

class Leaderboard {
	std::string file;
	std::vector<Entry*> leaderboard;

public:
	Leaderboard(std::string file);
	Leaderboard();
	~Leaderboard();
	std::vector<Entry*> getLeaderboard() const;
	int getSize() const;
	void addEntry(Entry* e);
	void sort();
	void fileKi();
};
#endif
