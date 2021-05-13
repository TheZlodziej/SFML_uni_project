#include "Gun.h"

Gun::Gun(const sf::Vector2f& position, const int& durability, TextureManager* textures, const TEXTURE& texture, const GAME_OBJECT_TYPE& type):
Item(position, durability, textures, texture, type)
{}

Gun::~Gun()
{}

void Gun::Use()
{
}
