#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "TextureManager.h"

enum class HUD_ELEMENT {
	HP = 0,
	ITEMS_BG = 1,
	SELECTED_ITEM = 2
};

class HUD
{
private:
	TextureManager* textures_;
	std::unordered_map<HUD_ELEMENT, sf::Sprite> hud_elements_;

public:
	HUD(TextureManager* textures);
	virtual ~HUD();
	void InitalizeHudElements();			// sets default hud elements; call in constructor
	void InitializeHudTextures();			// loads textures for hud
	void Update(const Entity* entity);		// updates hud elements (sets their position relative to given Entity)
	void Draw(sf::RenderWindow& window);	// draws hud elements
};

