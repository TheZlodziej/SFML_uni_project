#pragma once

#include <SFML/Graphics.hpp>
#include <map>

enum class TEXTURE {
	PLAYER,
	ENEMY_1
};

class TextureManager
{
private:
	std::map<TEXTURE, sf::Texture> textures;
	
public:
	TextureManager();
	~TextureManager();
	void Add(const TEXTURE& texture_key, const std::string& filename);
	sf::Texture& Get(const TEXTURE& texture_key);
};

