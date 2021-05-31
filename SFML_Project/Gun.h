#pragma once
#include "Item.h"
#include "Bullet.h"

//debug
#include <iostream>

class Gun : public Item
{
private:
	std::vector<Bullet> bullets_;
public:
	Gun(const sf::Vector2f& position,
		const unsigned int& durability,
		TextureManager* textures,
		GameObject* owner = nullptr,
		const float& cooldown = 2.0f,
		const float& range = 600.0f,
		const float& power = 20.0f,
		const TEXTURE& texture = TEXTURE::ITEM_GUN,
		const GAME_OBJECT_TYPE& type = GAME_OBJECT_TYPE::ITEM,
		const sf::Vector2u& animation_frames = sf::Vector2u(2, 1),
		const float& animation_time = 1.0f,
		const float& push_back_force = 1.0f
	);
	virtual ~Gun();
	virtual void Use() override;
	virtual bool CheckCollision(GameObject* object) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Update(const float& delta_time) override;
};

