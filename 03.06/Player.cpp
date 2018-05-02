#include "Player.hpp"

Player::Player():l(){
	
}

void Player::set_laststeps(int x_, int y_) {
	l.x = x_;
	l.y = y_;
}

step Player::get_laststeps()const {
	return l;
}

Player::~Player() {

}
