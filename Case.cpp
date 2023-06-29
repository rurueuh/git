#include "Case.h"

Case::Case(sf::Vector2i pos)
	: _position(pos)
{
	sf::Texture& texture = Texture::createTexture("block.png");
	_sprite.setTexture(texture);
	_sprite.setTextureRect(_rectsTexture[_state]);
	_sprite.setPosition(_position.x * CASE_WIDTH, _position.y * CASE_HEIGHT);
}

void Case::draw(sf::RenderTarget& target)
{
	target.draw(_sprite);
}

void Case::setState(State newstate)
{
	_state = newstate;
	_sprite.setTextureRect(_rectsTexture[_state]);
}
