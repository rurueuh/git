#include "View.h"

View::View()
{
	_view.setCenter(sf::Vector2f(0, 0));
	_view.setSize(sf::Vector2f(1920, 1080));
}

void View::update()
{
	if (_clock.getElapsedTime().asSeconds() > 0.01f) {
		float speed = 3 * (_view.getSize().x / 1920);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			speed = 10;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			_view.move(0, -speed);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			_view.move(0, speed);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			_view.move(-speed, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			_view.move(speed, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
			_view.zoom(0.99f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
			_view.zoom(1.01f);
		_clock.restart();
	}
}
