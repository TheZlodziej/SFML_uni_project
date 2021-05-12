#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "TextureManager.h"
#include "HelperFunctions.h"

enum class HUD_ELEMENT {
	HP = 0,
	ITEMS_BG = 1,
	SELECTED_ITEM = 2
};

struct HudElement {
	sf::Sprite sprite;
	sf::Vector2f default_position;
	sf::Vector2f current_offset = sf::Vector2f(0.0f, 0.0f);
};

class HUD
{
private:
	TextureManager* textures_;
	std::unordered_map<HUD_ELEMENT, HudElement> hud_elements_;
	sf::Vector2f view_size_;				// for right positioning of elements

public:
	HUD(TextureManager* textures);
	virtual ~HUD();
	void InitalizeHudElements();			// sets default hud elements; call in constructor
	void InitializeHudTextures();			// loads textures for hud
	void Update(Entity* entity);			// updates hud elements (sets their position relative to given Entity)
	void Draw(sf::RenderWindow& window);	// draws hud elements
};

