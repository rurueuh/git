#include "Map.h"

Map::Map(int x, int y) : _x(x), _y(y)
{
	for (int i = 0; i < y; i++)
	{
		std::vector<Case> line;
		for (int j = 0; j < x; j++)
		{
			line.push_back(Case({j, i}));
		}
		_map.push_back(line);
	}
}

void Map::update()
{
}

void Map::draw(sf::RenderTarget& target)
{
	static sf::Clock clock;
	clock.restart();
	for (auto& line : _map)
	{
		for (auto& sprite : line)
		{
			sprite.draw(target);
		}
	}
	std::cout << clock.getElapsedTime().asMilliseconds() << std::endl;
}

Case& Map::getCase(int x, int y)
{
	sf::Vector2i pos(x / CASE_WIDTH, y / CASE_HEIGHT);
	if (pos.x < 0 || pos.x >= _x || pos.y < 0 || pos.y >= _y)
		throw std::out_of_range("Out of range");
	return _map[pos.y][pos.x];
}

Case* Map::getCasePtr(int x, int y)
{
	if (x < 0 || x >= _x || y < 0 || y >= _y)
		return nullptr;
	return &_map[y][x];
}

void Map::findPath()
{
	if (isStartInMap() == false || isEndInMap() == false)
		throw std::runtime_error("Start or end not in map");
	for (auto& line : _map)
	{
		for (auto& sprite : line)
		{
			sprite.setIsVisited(false);
			if (sprite.getState() == Case::Path || sprite.getState() == Case::Checked)
				sprite.setState(Case::None);
			sprite.valueFind = INT_FAST32_MAX;
		}
	}
	Case& start = getStartCase();
	Case& end = getEndCase();
	std::vector<std::pair<Case*, int>> toUpdate;
	std::vector<std::pair<Case*, int>> visited;
	toUpdate.push_back(std::make_pair<Case *, int>(&start, 0));
	bool find = false;

	int value = 0;
	while (!find)
	{
		if (toUpdate.empty())
			throw std::runtime_error("No path found");
		auto &it = toUpdate.front();
		const auto toRemove = toUpdate.begin();
		visited.push_back(it);
		toUpdate.erase(toRemove);
		value = it.second;
		Case* current = it.first;
		current->setIsVisited(true);
		if (current->getState() == Case::End) {
			find = true;
			break;
		}
		Case* up = getCasePtr(current->getPosition().x, current->getPosition().y - 1);
		Case* down = getCasePtr(current->getPosition().x, current->getPosition().y + 1);
		Case* left = getCasePtr(current->getPosition().x - 1, current->getPosition().y);
		Case* right = getCasePtr(current->getPosition().x + 1, current->getPosition().y);
		if (up && up->getIsVisited() == false && up->getState() != Case::Wall) {
			toUpdate.push_back(std::make_pair<Case*, int>(&*up, value + 1));
			up->setIsVisited(true);
		}
		if (down && down->getIsVisited() == false && down->getState() != Case::Wall) {
			toUpdate.push_back(std::make_pair<Case*, int>(&*down, value + 1));
			down->setIsVisited(true);
		}
		if (left && left->getIsVisited() == false && left->getState() != Case::Wall) {
			toUpdate.push_back(std::make_pair<Case*, int>(&*left, value + 1));
			left->setIsVisited(true);
		}
		if (right && right->getIsVisited() == false && right->getState() != Case::Wall) {
			toUpdate.push_back(std::make_pair<Case*, int>(&*right, value + 1));
			right->setIsVisited(true);
		}
	}

	for (auto& it : visited)
	{
		it.first->valueFind = it.second;
		if (it.first->getState() == Case::None)
			it.first->setState(Case::Checked);
	}

	Case* travel = &end;
	travel->valueFind = value;
	
 	while (1) {
		if (travel->getState() == Case::Start)
			break;
		if (travel->getState() == Case::Checked) {
			travel->setState(Case::Path);
		}
		Case* up = getCasePtr(travel->getPosition().x, travel->getPosition().y - 1);
		Case* down = getCasePtr(travel->getPosition().x, travel->getPosition().y + 1);
		Case* left = getCasePtr(travel->getPosition().x - 1, travel->getPosition().y);
		Case* right = getCasePtr(travel->getPosition().x + 1, travel->getPosition().y);

		int upValue = INT_FAST32_MAX, downValue = INT_FAST32_MAX, leftValue = INT_FAST32_MAX, rightValue = INT_FAST32_MAX;
		if (up) {
			upValue = up->valueFind;
		}
		if (down) {
			downValue = down->valueFind;
		}
		if (left) {
			leftValue = left->valueFind;
		}
		if (right) {
			rightValue = right->valueFind;
		}

		if (upValue <= downValue && upValue <= leftValue && upValue <= rightValue) {
			travel = up;
		}
		else if (downValue <= upValue && downValue <= leftValue && downValue <= rightValue) {
			travel = down;
		}
		else if (leftValue <= upValue && leftValue <= downValue && leftValue <= rightValue) {
			travel = left;
		}
		else if (rightValue <= upValue && rightValue <= downValue && rightValue <= leftValue) {
			travel = right;
		}
		else {
			throw std::runtime_error("Error in findPath");
		}
	}
}

Case& Map::getStartCase()
{
	for (auto& line : _map)
	{
		for (auto& sprite : line)
		{
			if (sprite.getState() == Case::Start)
				return sprite;
		}
	}
	throw std::runtime_error("Start not in map");
}

Case& Map::getEndCase()
{
	for (auto& line : _map)
	{
		for (auto& sprite : line)
		{
			if (sprite.getState() == Case::End)
				return sprite;
		}
	}
	throw std::runtime_error("End not in map");
}

bool Map::isStartInMap()
{
	for (auto& line : _map)
	{
		for (auto& sprite : line)
		{
			if (sprite.getState() == Case::Start)
				return true;
		}
	}
	return false;
}

bool Map::isEndInMap()
{
	for (auto& line : _map)
	{
		for (auto& sprite : line)
		{
			if (sprite.getState() == Case::End)
				return true;
		}
	}
	return false;
}
