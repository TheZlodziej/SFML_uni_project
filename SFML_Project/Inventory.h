#pragma once

#include "Item.h"

class Inventory
{
private:
	std::vector<Item*> items_;
	unsigned int curr_item_idx_;
	unsigned int size;				// size of inventory
public:
	Inventory();
	virtual ~Inventory();
	void Add(Item* item);
	void Remove(const unsigned int& item_idx);
};

