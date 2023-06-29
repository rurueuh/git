#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <string>


class Texture
{
public:
	static sf::Texture &createTexture(std::string name) {
		if (!_texture.count(name)) {
			sf::Texture texture;
			if (!texture.loadFromFile(name)) {
				std::cout << "Error loading texture: " << name << std::endl;
			}
			_texture[name] = texture;
			return _texture[name];
		}
		else {
			return _texture[name];
		}
	}
private:
	static std::map<std::string, sf::Texture> _texture;
};

inline std::map<std::string,sf::Texture> Texture::_texture = {};

