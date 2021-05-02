#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>

#include "GameObject.h"
#include "Inventory.h"

class Entity : public GameObject
{
protected:
	float strength_;
	sf::Vector2f velocity_;
	sf::Vector2f acceleration_;
	Inventory inventory_;

public:
	Entity(const sf::Sprite& sprite,
		const sf::Vector2f& velocity = sf::Vector2f(0.0f, 0.0f),
		const sf::Vector2f& acceleration = sf::Vector2f(0.0f, 0.0f),
		const float& strength = 10.0f);
	virtual ~Entity();

	void Draw(sf::RenderWindow& window) override;
	void Update(const float& delta_time) override;
	void AddToInventory(Item* item);
	void RemoveFromInventory(const unsigned int& item_idx);
	void SetAcceleration(const sf::Vector2f& new_acceleration);
	void UpdateAcceleration(const float& delta_time);
	void Move(const float& delta_time);
	void UpdateVelocity(const float& delta_time);
	sf::Vector2f GetAcceleration() const;
};

