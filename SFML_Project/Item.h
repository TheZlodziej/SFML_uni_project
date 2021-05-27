#pragma once

#include "GameObject.h"
#include "Entity.h"

class Item : public GameObject
{
protected:
	unsigned int uses_;
	unsigned int durability_;		// uses before item is destroyed
	float time_after_use_;			// time to check whether item can be used again
	float cooldown_time_;			// time after you can use the item again
	//Entity* owner_;				// owner of the item used to position item correctly
public:
	Item(const sf::Vector2f& position,
		const unsigned int& duarbility,
		TextureManager* textures,
		//Entity* owner = nullptr,
		const float& cooldown = 2.0f,
		const TEXTURE& texture = TEXTURE::ITEM,
		const GAME_OBJECT_TYPE & type = GAME_OBJECT_TYPE::ITEM,
		const sf::Vector2u& animation_frames = sf::Vector2u(1, 1),
		const float& animation_time = 1.0f,
		const float& push_back_force = 1.0f
	);
	virtual ~Item();
	virtual void Use()=0;
	bool CanUse() const;			// checks is item is not on cooldown
	//void SetOwner(Entity* entity);
	//void RemoveOwner();
	//bool HasOwner() const;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Update(const float& delta_time) override;
};

