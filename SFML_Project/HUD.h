#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "TextureManager.h"

class HUD
{
private:
	TextureManager _textures;
	std::vector<sf::Sprite> _hud_elements;

public:
	HUD();
	virtual ~HUD();
	void InitalizeHudElements();			// sets default hud elements; call in constructor
	void InitializeHudTextures();			// loads textures for hud
	void Update(const Entity* entity);		// updates hud elements (sets their position relative to given Entity)
	void Draw(sf::RenderWindow& window);	// draws hud elements
};

