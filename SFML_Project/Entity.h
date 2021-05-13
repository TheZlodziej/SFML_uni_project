#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>

#include "GameObject.h"
#include "Inventory.h"
#include "GameConstants.h"
#include "HelperFunctions.h"

//debug
#include <iostream>

class Entity : public GameObject
{
protected:
	float strength_;
	float hp_;
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
		const GAME_OBJECT_TYPE& type = GAME_OBJECT_TYPE::ENTITY
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
	void UpdateVelocity(const float& delta_time);				// updates entity's velocity
	sf::Vector2f GetDirection(const Entity* entity) const;		// returns direction to entity given in argument
	sf::Vector2f GetAcceleration() const;						// remove later maybe?? (not used)
	float GetHp() const;										// returns percentage of hp
	void LoseHp(const float& percentage);						// removes % of players hp -> new hp = (curr hp - arg)%
};

