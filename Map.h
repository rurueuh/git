#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Case.h"

class Map
{
public:
	Map(int x, int y);
	~Map() = default;

	void update();
	void draw(sf::RenderTarget &target);
	Case& getCase(int x, int y);
	Case* getCasePtr(int x, int y);

	void findPath();

	Case& getStartCase();
	Case& getEndCase();

	bool isStartInMap();
	bool isEndInMap();
private:
	int _x;
	int _y;
	std::vector<std::vector<Case>> _map;
};

