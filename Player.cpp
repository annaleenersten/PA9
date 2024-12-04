#include "Player.hpp"

Player::Player() {
	points = 0;

	texture.loadFromFile("level1Ship.png");
	setTexture(texture);
	scale(0.9, 0.9);
}

void Player::setPoints(const int newPoints) {
	points = newPoints;
}
int Player::getPoints() const {
	return points;
}

void Player::level2() {
	texture.loadFromFile("spaceship.png");
	setTexture(texture);
	scale(1, 1);
}
void Player::level3() {

}