#include "Terrain.h"

Terrain::Terrain(const float& push_back_force, const sf::Vector2f& position, const GAME_OBJECT_TYPE& type, TextureManager* textures, const TEXTURE& texture, const sf::Vector2f& scale,const sf::Vector2u& animation_frames, const float& animation_time):
	GameObject(position, type, textures, texture, animation_frames, animation_time),
	push_back_force_(std::clamp(push_back_force, 0.0f, 1.0f))
{
	this->sprite_.setScale(scale);
	//set repeating texture??
}

Terrain::~Terrain()
{}

Terrain* Terrain::MakeTree(const sf::Vector2f& scale)
{
	return nullptr;
}

Terrain* Terrain::MakeWall(const sf::Vector2f& scale)
{
	return nullptr;
}

Terrain* Terrain::MakeTerrain(const TERRAIN& type, const sf::Vector2f& scale)
{
	switch (type)
	{
	case TERRAIN::TREE:
		return Terrain::MakeTree(scale);

	case TERRAIN::WALL:
		return Terrain::MakeWall(scale);
		
	default:
		return Terrain::MakeTree(scale);
	}
}
