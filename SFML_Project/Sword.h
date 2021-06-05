#pragma once
#include "Item.h"
class Sword : public Item
{
private:
	float animation_rotation_;	// this variable is beign used for animating the sword
	bool animating_;
	bool dealt_dmg_;

public:
	Sword(const sf::Vector2f& position,
		const unsigned int& durability,
		TextureManager* textures,
		GameObject* owner = nullptr,
		const float& cooldown = GAME_CONST::SWORD_MAX_ROTATION*2.0f/GAME_CONST::SWORD_SPEED,
		const float& range = 175.0f,
		const float& power = GAME_CONST::SWORD_POWER,
		const TEXTURE& texture = TEXTURE::SWORD,
		const GAME_OBJECT_TYPE& type = GAME_OBJECT_TYPE::ITEM,
		const sf::Vector2u& animation_frames = sf::Vector2u(1, 1),
		const float& animation_time = 1.0f,
		const float& push_back_force = 1.0f
	);

	virtual ~Sword();
	void Animate(const float& delta_time);
	virtual void Use() override;
	virtual bool CheckCollision(GameObject* object) override;
	virtual void Update(const float& delta_time) override;
	virtual bool CanUse() const override;
};

