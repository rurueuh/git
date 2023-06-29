#pragma once

#include "Map.h"
#include "View.h"

constexpr unsigned int WINDOW_WIDTH = 1920;
constexpr unsigned int WINDOW_HEIGHT = 1080;
constexpr unsigned int FPS = 240;

class Game
{
	public:
	Game();
	~Game() = default;
	void run();

private:

	Map _map = Map::Map(500, 300);
	View _view;
	void update();
	void render();
	void processEvents();

	void setCaseInMap();

	sf::RenderWindow _window;
};

