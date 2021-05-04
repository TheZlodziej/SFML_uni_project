#pragma once

#include <SFML/Graphics.hpp>
#include "GameConstants.h"
#include "GameObject.h"

class Camera
{
private:
	sf::View view_;

public:
	Camera();
	virtual ~Camera();
	void Update(const sf::Vector2f& pos);
	void Attach(sf::RenderWindow& window);
	void SetZoom(const float& zoom);
	void Resize(const sf::RenderWindow& window);
	sf::View& GetCamera();
};

