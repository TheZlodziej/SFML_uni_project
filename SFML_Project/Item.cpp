#include "Item.h"

Item::Item(const sf::Sprite& sprite, int durability):
	GameObject(sprite),
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