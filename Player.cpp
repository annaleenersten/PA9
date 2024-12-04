#include "Player.hpp"

Player::Player() {
	points = 0;

	texture.loadFromFile("spaceship.png");
	setTexture(texture);
	scale(0.1, 0.1);
}

void Player::setPoints(const int newPoints) {
	points = newPoints;
}
int Player::getPoints() const {
	return points;
}

sf::Text Player::displayPoints(sf::Font &font){
	std::string points = std::to_string(getPoints());
	sf::Text text("Points: " + points, font, 70);
	text.setFillColor(sf::Color::Red);
	sf::FloatRect bounds(text.getLocalBounds());
	text.setPosition(0, 0);
	return text;
}

void  Player::movePlayer(sf::Event event) {

	if (event.type == sf::Event::EventType::KeyPressed) {
		if (event.key.code == sf::Keyboard::Left) {
			move(-1.7, 0);


		}
		if (event.key.code == sf::Keyboard::Right) {
			move(1.7, 0);

		}
	}
}

