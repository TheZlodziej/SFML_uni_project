#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>

#include "GameObject.h"
#include "Inventory.h"
#include "GameConstants.h"
#include "HelperFunctions.h"
#include "HpBar.h"

//debug
#include <iostream>

class Entity : public GameObject
{
protected:
	float strength_;
	HpBar hp_bar_;
	sf::Vector2f velocity_;
	sf::Vector2f acceleration_;
	Inventory inventory_;
	
public:
	Entity(const sf::Vector2f& position,
		TextureManager* textures,
		const TEXTURE& texture = TEXTURE::DEFAULT,
		const sf::Vector2f& velocity = sf::Vector2f(0.0f, 0.0f),
		const sf::Vector2f& acceleration = sf::Vector2f(0.0f, 0.0f),
		const float& strength = 10.0f,
		const float& hp = 1.0f,
		const float& push_back_force = 0.5f,
		const GAME_OBJECT_TYPE& type = GAME_OBJECT_TYPE::ENTITY,
		const sf::Vector2u& animation_frames = sf::Vector2u(1,1),
		const float& animation_time = 1.0f
		);
	virtual ~Entity();
	virtual void Draw(sf::RenderWindow& window) override;		// draws entity to the given render window
	virtual void Update(const float& delta_time) override;		// calls other update functions
	Inventory* GetInventory();									// returns referance to entity's inventory
	void SetAcceleration(const sf::Vector2f& acceleration);		// sets entity's acceleration to given value
	void ApplyDrag();											// decreases entity's velocity by constant factor
	void UpdateAcceleration();									// updates entity's acceleration
	void Move();												// calls sf::Sprite::move function
	void Stop();												// stops movement of the object (sets vel & acc to 0)
	void UseItem();												// calls Use() on item that is currently selected
	void UpdateVelocity(const float& delta_time);				// updates entity's velocity
	sf::Vector2f GetDirection(const Entity* entity) const;		// returns direction to entity given in argument
	sf::Vector2f GetAcceleration() const;						// remove later maybe?? (not used)
	void LoseHp(const float& amount);							// removes % of players hp -> new hp = (curr hp - arg)%
	void LookAt(GameObject* object);							// rotates entity to look at specific object
};

