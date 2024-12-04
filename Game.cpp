#include "Game.hpp"
#include <vector>

void Game::create() {

	sf::RenderWindow window(sf::VideoMode(2000, 1000), "SFML works!");//window

	Player player1;//player
	player1.setPosition(window.getSize().x / 2 - 100, window.getSize().y - 250);//position

	sf::Font font;//fonts
	font.loadFromFile("font.ttf");

	sf::Texture texture;//background texture	
	texture.loadFromFile("stars.jpg");
	sf::Sprite sprite(texture);//set sprite to texture
	sprite.setPosition(0, 0);
	sprite.scale((window.getSize().x / sprite.getLocalBounds().width), (window.getSize().y / sprite.getLocalBounds().height));


	sf::Texture alienSpriteTexture;//alien sprite texture array
	alienSpriteTexture.loadFromFile("purpleAlien.png");

	sf::Sprite shapeArray[10];//sprite array

	for (int i = 0; i < 10; i++) {//set shape size, color, position

		shapeArray[i].setTexture(alienSpriteTexture);//set sprite texture
		shapeArray[i].setScale(0.15f, 0.15f);//set scale
		shapeArray[i].setPosition(-150, -150);//set pos
	}


	sf::Text gameOver("GAME OVER", font, 150);//game over stuff
	gameOver.setFillColor(sf::Color::Red);
	sf::FloatRect bounds2(gameOver.getLocalBounds());
	gameOver.setPosition(window.getSize().x / 2 - (bounds2.left + bounds2.width / 2), window.getSize().y / 2 - (bounds2.top + bounds2.height / 2));

	run(window, player1, font, shapeArray, gameOver, sprite);
}

void Game::run(sf::RenderWindow& window, Player& player, sf::Font& font, sf::Sprite shapeArray[], sf::Text gameOver, sf::Sprite sprite) {
	
	std::srand(static_cast<unsigned>(std::time(0)));
	float randomNum = 0;
	sf::Clock clock;

	std::vector<sf::CircleShape> laser;

	while (window.isOpen())
	{
	

		float time = clock.restart().asSeconds();

		//window closing event
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}

		}

		player.movePlayer(event);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if (laser.size() < 30) {
				sf::CircleShape circle;
				circle.setRadius(window.getSize().x / 150);
				circle.setFillColor(sf::Color::Red);
				circle.setPosition(player.getPosition().x, player.getPosition().y);
				laser.push_back(circle);
			}
		}
	

		for (int i = 0; i < laser.size(); ++i) {
			laser[i].move(0, -1.5);  // Move laser upwards

			if (laser[i].getPosition().y < 0) {
				laser.pop_back();
			}
		}

		for (int i = 0; i < laser.size(); ++i) {
			for (int j = 0; j < 10; j++) {
				if (laser[i].getGlobalBounds().intersects(shapeArray[j].getGlobalBounds())) {
					player.setPoints(player.getPoints() + 1);
					laser[i].setFillColor(sf::Color::Transparent);
					shapeArray[j].move(0, -2);
				}
			}
		}
			

		for (int i = 0; i < 5; i++) {
			for (int j = i; j < 10; j++) {
				for (int k = j; k < 10; k++)
					randomNum = std::rand() % 120;
				shapeArray[i].move(0, randomNum * time);

				if (shapeArray[i].getPosition().y > window.getSize().y) {
					randomNum = std::rand() % window.getSize().x;
					shapeArray[i].setPosition(randomNum, -20);
				}

			}
		}

		window.clear();

		//end of game code
		for (int i = 0; i < 10; i++) {
			if (player.getGlobalBounds().intersects(shapeArray[i].getGlobalBounds())) {
				window.draw(sprite);
				window.draw(gameOver);
				window.display();
				sf::sleep(sf::seconds(5));
				window.close();
			}
		}


		window.draw(sprite);
		window.draw(player.displayPoints(font));
		for (int i = 0; i < 10; ++i) {
			window.draw(shapeArray[i]);
		}
		for (int i = 0; i < laser.size(); ++i) {
			window.draw(laser[i]);
		}
		
		window.draw(player);
		window.display();

	}
}

