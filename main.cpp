#include <iostream>
#include <cstdlib>
#include <ctime>

#include "SFML/Graphics.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(2000, 1000), "SFML works!");

	sf::Font font;
	font.loadFromFile("font.ttf");

	sf::Text text("Points: ", font, 70);
	text.setFillColor(sf::Color::Red);
	sf::FloatRect bounds(text.getLocalBounds());
	text.setPosition(0, 0);

	sf::Texture texture;
	texture.loadFromFile("stars.jpg");
	sf::Sprite sprite(texture);
	sprite.setPosition(0, 0);
	sprite.scale((window.getSize().x/ sprite.getLocalBounds().width),(window.getSize().y/ sprite.getLocalBounds().height));

	sf::Texture texture2;
	texture2.loadFromFile("ufo.png");
	sf::Sprite sprite2(texture2);
	sprite2.setPosition(window.getSize().x / 2 - (bounds.left + bounds.width / 2), window.getSize().y - 200);
	sprite2.scale(0.15, 0.15);

	
	sf::CircleShape shapeArray[10];

	for (int i = 0; i < 10; i++) {
		shapeArray[i].setRadius(window.getSize().x / 80);
		shapeArray[i].setFillColor(sf::Color::White);
		shapeArray[i].setPosition(-50, -50);
	}

	std::srand(static_cast<unsigned>(std::time(0)));
	float randomNum = 0;

	sf::Text gameOver("GAME OVER", font, 150);
	gameOver.setFillColor(sf::Color::Red);
	sf::FloatRect bounds2(gameOver.getLocalBounds());
	gameOver.setPosition(window.getSize().x / 2 - (bounds2.left + bounds2.width / 2), window.getSize().y / 2 - (bounds2.top + bounds2.height / 2));


	sf::Clock clock;


	while (window.isOpen())
	{
		
		float time = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}

		}

		if (event.type == sf::Event::EventType::KeyPressed) {
			if (event.key.code == sf::Keyboard::Left) {
				sprite2.move(-1.0, 0);
			}
			if (event.key.code == sf::Keyboard::Right) {
				sprite2.move(1.0, 0);
			}
		}
		
		for (int i = 0; i < 5; i++) {
			for (int j = i; j < 10; j++) {
				for (int k = j; k < 10; k++)
				randomNum = std::rand() % 150;
				shapeArray[i].move(0, randomNum * time);

				if (shapeArray[i].getPosition().y > window.getSize().y) {
					randomNum = std::rand() % window.getSize().x;
					shapeArray[i].setPosition(randomNum, -20);
				}

			}
		}
		window.clear();
		
		for (int i = 0; i < 10; i++) {
			if (sprite2.getGlobalBounds().intersects(shapeArray[i].getGlobalBounds())) {
				window.draw(sprite);
				window.draw(gameOver);
				window.display();
				sf::sleep(sf::seconds(5));
				window.close();
			}
		}

		window.draw(sprite);
		window.draw(text);
		for (int i = 0; i < 10; ++i) {
			window.draw(shapeArray[i]);
		}
		window.draw(sprite2);
		window.display();

	}

	return 0;
}