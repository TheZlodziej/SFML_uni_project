#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "TextureManager.h"
#include "HelperFunctions.h"

enum class HUD_ELEMENT {
	HP = 0,
	ITEM_BG = 1,
	SELECTED_ITEM = 2,
	ITEM = 3
};

struct HudElement 
{
	sf::Sprite sprite;
	sf::Vector2f default_position;
	sf::Vector2f current_offset = sf::Vector2f(0.0f, 0.0f);
};

class HUD
{
private:
	Entity* entity_;						// ptr to object that the hud belongs to
	TextureManager* textures_;
	std::unordered_map<HUD_ELEMENT, HudElement> hud_elements_;
	std::vector<HudElement> items_placeholder_;
	sf::Vector2f view_size_;				// for right positioning of elements

public:
	HUD(Entity* entity, TextureManager* textures);
	virtual ~HUD();
	
	void UpdatePosition(const float& delta_time);	// updates position based on entity's movement
	void UpdateHealthBar(const float& delta_time);	// updates health bar
	void InitalizeHudElements();			// sets default hud elements; call in constructor
	void InitializeHudTextures();			// loads textures for hud
	void Update(const float& delta_time);	// updates hud elements (sets their position relative to given Entity)
	void Draw(sf::RenderWindow& window);	// draws hud elements
};

