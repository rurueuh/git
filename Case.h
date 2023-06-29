#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Texture.h"

constexpr unsigned int CASE_WIDTH = 32;
constexpr unsigned int CASE_HEIGHT = 32;


class Case
{
public:

	enum State {
		None = 0,
		Wall = 1,
		Path = 2,
		Start = 3,
		End = 4,
		Checked = 5,
	};


	Case(sf::Vector2i pos);
	~Case() = default;
	void draw(sf::RenderTarget &target);

	void setState(State newstate);
	State getState() { return _state; }

	sf::Vector2i getPosition() { return _position; };

	bool getIsVisited() { return _isVisited; };
	void setIsVisited(bool isVisited) { _isVisited = isVisited; };
	
	int valueFind = INT_FAST32_MAX;

private:
	static std::vector<sf::IntRect> _rectsTexture;
	sf::Vector2i _position;
	sf::Sprite _sprite;
	State _state = None;
	bool _isVisited = false;
};

inline std::vector<sf::IntRect> Case::_rectsTexture = {
	{32, 0, CASE_WIDTH, CASE_HEIGHT},
	{0 , 0, CASE_WIDTH, CASE_HEIGHT},
	{64, 0, CASE_WIDTH, CASE_HEIGHT},
	{96, 0, CASE_WIDTH, CASE_HEIGHT},
	{128, 0, CASE_WIDTH, CASE_HEIGHT},
	{160, 0, CASE_WIDTH, CASE_HEIGHT},
};

