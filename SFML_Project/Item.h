#pragma once

#include "GameObject.h"

class Item : public GameObject
{
protected:
	unsigned int uses_;
	unsigned int durability_;		// uses before item is destroyed
	float time_after_use_;			// time to check whether item can be used again
	float cooldown_time_;			// time after you can use the item again
	GameObject* owner_;				// owner of the item used to position item correctly
	sf::Sprite icon_;				// field so item can be displayed in inventory while the original one is in hand
public:
	Item(const sf::Vector2f& position,
		const unsigned int& duarbility,
		TextureManager* textures,
		GameObject* owner = nullptr,
		const float& cooldown = 2.0f,
		const TEXTURE& texture = TEXTURE::ITEM,
		const GAME_OBJECT_TYPE & type = GAME_OBJECT_TYPE::ITEM,
		const sf::Vector2u& animation_frames = sf::Vector2u(1, 1),
		const float& animation_time = 1.0f,
		const float& push_back_force = 1.0f
	);
	virtual ~Item();
	virtual void Use()=0;
	bool CanUse() const;			// checks is item is not on cooldown, has an owner and isn't destroyed
	void SetOwner(GameObject* entity);
	void RemoveOwner();
	void UpdateIcon();
	sf::Sprite& GetIcon();
	bool HasOwner() const;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Update(const float& delta_time) override;
};

