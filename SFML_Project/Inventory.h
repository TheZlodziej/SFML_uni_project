#pragma once

#include "Item.h"

class Inventory
{
private:
	std::vector<Item*> items_;
	unsigned int curr_item_idx_;
	unsigned int size_;				// maximum size of inventory
public:
	Inventory();
	virtual ~Inventory();
	void Add(Item* item);
	void SetCurrentItemIdx(const int& item_index);
	void Remove(const unsigned int& item_idx);
	void Draw(sf::RenderWindow& window) const;
	unsigned int GetCurrentItemIndex() const;
	unsigned int GetSize() const;
	std::vector<Item*> GetItems();
};

