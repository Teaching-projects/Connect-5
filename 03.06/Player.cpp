#include "Player.hpp"

Player::Player():arr(new int[2]) {}

void Player::set_laststeps(int x_, int y_) {
	arr[0] = x_;
	arr[1] = y_;
}

int* Player::get_laststeps()const {
	return arr;
}

Player::~Player() {
	delete[] arr;
}