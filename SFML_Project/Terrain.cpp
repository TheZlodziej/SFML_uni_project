#include "Terrain.h"

Terrain::Terrain(const float& push_back_force, const sf::Vector2f& position, const GAME_OBJECT_TYPE& type, TextureManager* textures, const TEXTURE& texture, const sf::Vector2f& scale,const sf::Vector2u& animation_frames, const float& animation_time):
	GameObject(position, type, textures, texture, push_back_force, animation_frames, animation_time)
{
	this->sprite_.setScale(scale);
	//set repeating texture??
}

Terrain::~Terrain()
{}

Terrain* Terrain::MakeTree(const sf::Vector2f& position, TextureManager* textures, const sf::Vector2f& scale)
{	
	return new Terrain(1.0f, position, GAME_OBJECT_TYPE::TERRAIN, textures, TEXTURE::TREE, scale);
}

Terrain* Terrain::MakeWall(const sf::Vector2f& position, TextureManager* textures, const sf::Vector2f& scale)
{
	return new Terrain(1.0f, position, GAME_OBJECT_TYPE::TERRAIN, textures, TEXTURE::WALL, scale);
}

Terrain* Terrain::MakeTerrain(const TERRAIN& type, TextureManager* textures, const sf::Vector2f& position, const sf::Vector2f& scale)
{
	switch (type)
	{
	case TERRAIN::TREE:
		return Terrain::MakeTree(position, textures, scale);

	case TERRAIN::WALL:
		return Terrain::MakeWall(position, textures, scale);
		
	default:
		return Terrain::MakeTree(position, textures, scale);
	}
}
