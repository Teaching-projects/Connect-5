#ifndef ENTRY_HPP
#define ENTRY_HPP
#include <string>

class Entry{
	 std::string name;
	 std::string time;
	 int diff;
public:
	Entry(std::string name,std::string time,int diff);
	std::string getName()const;
	std::string getTime()const;
	int getDiff()const;
	bool operator <(const Entry& e2) const;
};
#endif
