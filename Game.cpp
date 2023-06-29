#include "Game.h"

Game::Game()
{
	_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dante's Inferno");
	_window.setFramerateLimit(FPS);
}

void Game::run()
{
	while (_window.isOpen()) {
		this->update();
		this->render();
		this->processEvents();
	}
}

void Game::update()
{
	static sf::Clock clock;
	sf::Time elapsed = clock.restart();
	const float dt = elapsed.asSeconds();

	setCaseInMap();
	_view.update();
}

void Game::render()
{
	_view.setView(_window);
	_window.clear();
	_map.draw(_window);
	_window.display();
}

void Game::processEvents()
{
	sf::Event event;
	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			_window.close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				_window.close();
			}
			if (event.key.code == sf::Keyboard::Space) {
				try {
					static sf::Clock clock;
					clock.restart();
					_map.findPath();
					sf::Time elapsed = clock.restart();
					std::cout << "time for find Path : " << elapsed.asMilliseconds() << " ms \n";
				}
				catch (std::exception& e) {
					std::cout << e.what() << std::endl;
				}
			}
		}
	}
}

void Game::setCaseInMap()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		Case::State state = Case::Wall;
		if (!_map.isStartInMap()) {
			state = Case::Start;
			std::cout << "Start is not already in map" << std::endl;
		}
		else if (!_map.isEndInMap()) {
			state = Case::End;
		}
		try {
			auto pos = sf::Mouse::getPosition(_window);
			auto posf = _window.mapPixelToCoords(pos);
			pos = sf::Vector2i(posf.x, posf.y);
			Case& block = _map.getCase(pos.x, pos.y);
			if (block.getState() == Case::Start || block.getState() == Case::End) {
				return;
			}
			block.setState(state);
		}
		catch (std::exception& e) {};
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		try {
			auto pos = sf::Mouse::getPosition(_window);
			auto posf = _window.mapPixelToCoords(pos);
			pos = sf::Vector2i(posf.x, posf.y);
			Case& block = _map.getCase(pos.x, pos.y);
			block.setState(Case::None);
		}
		catch (std::exception& e) {};
	}
}
