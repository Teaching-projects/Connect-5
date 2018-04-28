#include "Entry.hpp"

Entry::Entry(std::string name, std::string time, int diff):name(name),time(time),diff(diff) {}

std::string Entry::getName()const {
	return name;
}

std::string Entry::getTime()const {
	return time;
}

int Entry::getDiff()const {
	return diff;
}

bool Entry::operator <(const Entry& e2) const {
	return time < e2.getTime();
}