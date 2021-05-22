#include "Inventory.h"

Inventory::Inventory():
	curr_item_idx_(0),
	capacity_(6)
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
	if (this->items_.size() < this->capacity_)
	{
		this->items_.emplace_back(item);
	}
}

void Inventory::SetCurrentItemIdx(const int& item_index)
{
	if (item_index < 0)
	{
		this->curr_item_idx_ = static_cast<unsigned int>(this->capacity_ - 1);
	}
	else
	{
		this->curr_item_idx_ = static_cast<unsigned int>(item_index % this->capacity_);
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
	for (unsigned int i = 0; i < this->GetCapacity(); i++)
	{
		std::cout << " " << i;
		// draw square
		if (i == this->curr_item_idx_)
		{
			// make it stand out
			std::cout << "<-";
			
		}

		if (i < this->GetSize())
		{
			sf::Sprite* sprite = &this->items_[i]->GetSprite();
			sprite->setPosition(i*100.0f, 100.0f);
			this->items_[i]->Draw(window);
		}
	}
	std::cout << "\n";
}

unsigned int Inventory::GetCurrentItemIndex() const
{
	return this->curr_item_idx_;
}

unsigned int Inventory::GetCapacity() const
{
	return this->capacity_;
}

unsigned int Inventory::GetSize() const
{
	return this->items_.size();
}

std::vector<Item*> Inventory::GetItems()
{
	return this->items_;
}

Item* Inventory::GetCurrentItem()
{
	if (this->GetCurrentItemIndex() < this->GetSize())
	{
		return this->items_[this->curr_item_idx_];
	}

	return nullptr;
}

void Inventory::Update(const float& delta_time)
{
	for (auto& it : this->items_)
	{
		it->Update(delta_time);
	}
}
