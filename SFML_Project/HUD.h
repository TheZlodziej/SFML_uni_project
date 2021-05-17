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
	TextureManager* textures_;
	std::unordered_map<HUD_ELEMENT, HudElement> hud_elements_;
	std::vector<HudElement> items_placeholder_;
	sf::Vector2f view_size_;				// for right positioning of elements

public:
	HUD(TextureManager* textures);
	virtual ~HUD();
	void UpdateInventory(Entity* entity);	// sets new textures for inventory
	void UpdatePosition(Entity* entity);	// updates position based on entity's movement
	void UpdateHealthBar(Entity* entity);	// updates health bar
	void InitalizeHudElements();			// sets default hud elements; call in constructor
	void InitializeHudTextures();			// loads textures for hud
	void InsertItems(Entity* entity, const float& item_box_width, const sf::Vector2f& inventory_scale); // resets new items palceholder
	void Update(Entity* entity);			// updates hud elements (sets their position relative to given Entity)
	void Draw(sf::RenderWindow& window);	// draws hud elements
};

