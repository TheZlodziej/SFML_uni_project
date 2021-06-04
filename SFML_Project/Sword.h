#pragma once
#include "Item.h"
class Sword : public Item
{
private:

public:
	Sword(const sf::Vector2f& position,
		const unsigned int& durability,
		TextureManager* textures,
		GameObject* owner = nullptr,
		const float& cooldown = 3.0f,
		const float& range = 1000.0f,
		const float& power = 30.0f,
		const TEXTURE& texture = TEXTURE::SWORD,
		const GAME_OBJECT_TYPE& type = GAME_OBJECT_TYPE::ITEM,
		const sf::Vector2u& animation_frames = sf::Vector2u(1, 1),
		const float& animation_time = 1.0f,
		const float& push_back_force = 1.0f
	);

	virtual ~Sword();
	virtual void Use() override;
	virtual bool CheckCollision(GameObject* object) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Update(const float& delta_time) override;
};

