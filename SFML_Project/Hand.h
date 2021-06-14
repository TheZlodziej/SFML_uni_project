#pragma once
#include "Item.h"
class Hand : public Item
{
private:
	bool dealt_dmg_;
public:
	Hand(const sf::Vector2f& position,
		const unsigned int& durability,
		TextureManager* textures,
		GameObject* owner = nullptr,
		const float& cooldown = 1.5f,
		const float& range = 150.0f,
		const float& power = 20.0f,
		const TEXTURE& texture = TEXTURE::HAND,
		const GAME_OBJECT_TYPE& type = GAME_OBJECT_TYPE::ITEM,
		const sf::Vector2u& animation_frames = sf::Vector2u(1, 1),
		const float& animation_time = 1.0f,
		const float& push_back_force = 1.0f);
	virtual ~Hand();
	virtual bool CheckCollision(GameObject* object);
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Use();
};

