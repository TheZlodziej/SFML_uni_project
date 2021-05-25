#pragma once
#include "GameObject.h"

enum class TERRAIN {
	TREE,
	WALL
};

class Terrain : public GameObject
{
private:
public:
	Terrain(const float& push_back_force,
		const sf::Vector2f& position,
		const GAME_OBJECT_TYPE& type,
		TextureManager* textures,
		const TEXTURE& texture = TEXTURE::DEFAULT,
		const sf::Vector2f& scale = {1.0f, 1.0f},
		const sf::Vector2u& animation_frames = { 1,1 },
		const float& animation_time = 1.0f);
	virtual ~Terrain();

	static Terrain* MakeTree(const sf::Vector2f& position, TextureManager* textures, const sf::Vector2f& scale);
	static Terrain* MakeWall(const sf::Vector2f& position, TextureManager* textures, const sf::Vector2f& scale);
	static Terrain* MakeTerrain(const TERRAIN& type, TextureManager* textures, const sf::Vector2f& position, const sf::Vector2f& scale = {1.0f, 1.0f});
};

