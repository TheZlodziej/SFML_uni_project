#pragma once

#include "Item.h"

class Inventory
{
private:
	std::vector<Item*> items_;
	unsigned int curr_item_idx_;
	unsigned int capacity_;							// maximum size of inventory

public:
	Inventory();
	virtual ~Inventory();
	void Add(Item* item);
	void SetCurrentItemIdx(const int& item_index);
	void Remove(const unsigned int& item_idx);
	void Draw(sf::RenderWindow& window) const;		// idk about this?
	void Update(const float& delta_time);			// calls update on each of the items
	unsigned int GetCurrentItemIndex() const;
	unsigned int GetCapacity() const;				// returns maximum size of inventory
	unsigned int GetSize() const;					// returns number of items in inventory
	std::vector<Item*> GetItems();
	Item* GetCurrentItem();
	
};

