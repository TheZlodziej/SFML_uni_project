#pragma once

#include "GameObject.h"
#include "Item.h"

class Inventory
{
private:
	std::vector<Item*> items_;
	unsigned int curr_item_idx_;
	unsigned int capacity_;												// maximum size of inventory
	sf::RectangleShape items_bg_;
	sf::RectangleShape selected_item_bg_;
	sf::Vector2f view_size_;

public:
	Inventory();
	virtual ~Inventory();
	void Add(Item* item);
	void SetCurrentItemIdx(const int& item_index);
	void Remove(const unsigned int& item_idx);
	void Draw(sf::RenderWindow& window);							    // draws inventory on screen
	void Update(GameObject* relative_to, const float& delta_time);		// calls update for items and position
	void UpdateItems(const float& delta_time);							// calls update for each item
	void UpdatePosition(GameObject* relative_to);						// moves inventory relative to given game object
	unsigned int GetCurrentItemIndex() const;
	unsigned int GetCapacity() const;									// returns maximum size of inventory
	unsigned int GetSize() const;										// returns number of items in inventory
	std::vector<Item*> GetItems();
	Item* GetCurrentItem();
	void SelectBestItem();												// selects best item in inventory
};

