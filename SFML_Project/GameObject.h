#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
protected:
	sf::Sprite sprite_;

public:
	GameObject(const sf::Sprite& sprite);
	virtual ~GameObject();
	virtual void Update(const float& delta_time)=0;
	virtual void Draw(sf::RenderWindow& window)=0;
	bool CollidingWith(const GameObject* object) const; // simple rectangle collision detection with another game object
	sf::Vector2f GetPosition() const;
};

