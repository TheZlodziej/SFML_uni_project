#include "Item.h"

Item::Item(const sf::Sprite& sprite, int durability, TextureManager* textures, const TEXTURE& texture, const GAME_OBJECT_TYPE& type):
	GameObject(sprite, type, textures, texture),
	durability_(durability)
{}

Item::~Item()
{}

void Item::Draw(sf::RenderWindow& window)
{

}

void Item::Update(const float& delta_time)
{

}