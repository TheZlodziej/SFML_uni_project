#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
protected:
	sf::Sprite sprite_;

public:
	GameObject(const sf::Sprite& sprite);
	virtual ~GameObject();
	virtual void Update(const float& delta_time, const std::vector<GameObject*>& collidable_objects)=0;
	virtual void Draw(sf::RenderWindow& window)=0;
	bool CollidingWith(const GameObject* object) const; // simple rectangle collision detection with another game object
	bool CollidingWith(const sf::Sprite sprite) const; // simple rectangle collision detection with sf::Sprite
	bool CollidingWith(const sf::FloatRect rect) const; // simple rectangle collision detection with sf::FloatRect
	
	//bool CircularCollision(const GameObject* object) const;
	sf::Vector2f GetPosition() const;
};

