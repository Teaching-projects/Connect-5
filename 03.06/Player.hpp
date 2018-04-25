#ifndef PLAYER_HPP
#define PLAYER_HPP
	
class Player {
protected:
	int x;
	int y;
public:
	Player();
	virtual int* nextmove() = 0;
	void set_laststeps(int x_, int y_);
	int* get_laststeps()const;
};

#endif
