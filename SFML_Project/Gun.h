#pragma once
#include "Item.h"

//debug
#include <iostream>

class Gun : public Item
{
private:
	 
public:
	Gun(const sf::Vector2f& position,
		const unsigned int& durability,
		TextureManager* textures,
		const float& cooldown = 1.0f,
		const TEXTURE& texture = TEXTURE::ITEM_GUN,
		const GAME_OBJECT_TYPE& type = GAME_OBJECT_TYPE::ITEM,
		const sf::Vector2u& animation_frames = sf::Vector2u(1, 1),
		const float& animation_time = 1.0f
	);
	virtual ~Gun();
	virtual void Use() override;
};

