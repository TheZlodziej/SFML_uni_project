#pragma once
#include "Item.h"
class Gun : public Item
{
private:

public:
	Gun(const sf::Vector2f& position,
		const int& durability,
		TextureManager* textures,
		const TEXTURE& texture = TEXTURE::ITEM_GUN,
		const GAME_OBJECT_TYPE& type = GAME_OBJECT_TYPE::ITEM
	);
	virtual ~Gun();
	virtual void Use() override;
};

