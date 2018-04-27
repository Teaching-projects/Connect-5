#include "Player.hpp"

Player::Player():x(-1),y(-1) {}

void Player::set_laststeps(int x_, int y_) {
	x = x_;
	y = y_;
}

int* Player::get_laststeps()const {
	int *arr = new int[2];
	arr[0] = x;
	arr[1] = y;

	return arr;
}