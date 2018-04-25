#ifndef PLAYER_HPP
#define PLAYER_HPP
	
class Player {
protected:
	int *laststeps;

public:
	virtual int* nextmove() = 0;
};

#endif
