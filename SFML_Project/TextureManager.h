#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

enum class TEXTURE {
	DEFAULT,
	PLAYER,
	ENEMY_1,
	HP_BAR,
	ITEM_1
};

class TextureManager
{
private:
	std::unordered_map<TEXTURE, sf::Texture> textures;
	
public:
	TextureManager();
	~TextureManager();
	void Add(const TEXTURE& texture_key, const std::string& filename);
	sf::Texture& Get(const TEXTURE& texture_key);
};

