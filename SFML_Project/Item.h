#pragma once

#include "GameObject.h"

class Item : public GameObject
{
protected:
	int durability_;		// uses before item is destroyed

public:
	Item(const sf::Vector2f& position,
		const int& duarbility,
		TextureManager* textures, 
		const TEXTURE& texture = TEXTURE::ITEM,
		const GAME_OBJECT_TYPE & type = GAME_OBJECT_TYPE::ITEM,
		const sf::Vector2u& animation_frames = sf::Vector2u(1, 1),
		const float& animation_time = 1.0f
	);
	virtual ~Item();
	virtual void Use()=0;
	void Draw(sf::RenderWindow& window) override;
	void Update(const float& delta_time) override;
};

