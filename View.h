#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class View
{
public: 
	View();
	~View() = default;

	void update();

	void setView(sf::RenderWindow& window) {
		window.setView(_view);
	}

private:
	sf::View _view;
	sf::Clock _clock;
};

