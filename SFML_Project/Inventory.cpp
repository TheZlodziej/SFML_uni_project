#include "Inventory.h"

Inventory::Inventory():
	curr_item_idx_(0),
	size(9)
{}

Inventory::~Inventory()
{
	for (auto& item : this->items_)
	{
		delete item;
	}
}

void Inventory::Add(Item* item)
{
	if (this->items_.size() < this->size)
	{
		this->items_.emplace_back(item);
	}
}

void Inventory::Remove(const unsigned int& item_idx)
{
	if (item_idx < this->items_.size())
	{
		auto item_it = this->items_.begin() + item_idx;
		item_it = this->items_.erase(item_it);
	}
}