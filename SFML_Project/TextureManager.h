#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

enum class TEXTURE {
	DEFAULT,
	PLAYER,
	ENEMY_0,
	ENEMY_1,
	ENEMY_2,
	HP_BAR,
	ITEM,
	ITEM_BG,
	SELECTED_ITEM,
	ITEM_GUN,
	TREE,
	WALL
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

