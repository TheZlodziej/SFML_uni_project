#include "Inventory.h"

Inventory::Inventory():
	curr_item_idx_(0),
	size_(9)
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
	if (this->items_.size() < this->size_)
	{
		this->items_.emplace_back(item);
	}
}

void Inventory::SetCurrentItemIdx(const int& item_index)
{
	if (item_index < 0)
	{
		this->curr_item_idx_ = static_cast<unsigned int>(this->size_ - 1);
	}
	else
	{
		this->curr_item_idx_ = static_cast<unsigned int>(item_index % this->size_);
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
#include <iostream>
void Inventory::Draw(sf::RenderWindow& window) const
{
	// draw empty square && draw item miniature inside
	for (unsigned int i = 0; i < this->size_; i++)
	{
		std::cout << " " << i;
		// draw square
		if (i == this->curr_item_idx_)
		{
			// make it stand out
			std::cout << "<-";
			
		}

		if (i < this->items_.size())
		{
			// draw item
		}
	}
	std::cout << "\n";
}

unsigned int Inventory::GetCurrentItemIndex() const
{
	return this->curr_item_idx_;
}
