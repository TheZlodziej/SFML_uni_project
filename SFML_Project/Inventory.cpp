#include "Inventory.h"

Inventory::Inventory():
	curr_item_idx_(0),
	capacity_(6),
	view_size_(1.0f, 1.0f)
{
	using namespace GAME_CONST;

	this->items_bg_.setFillColor(sf::Color(ITEMS_BG_R, ITEMS_BG_G, ITEMS_BG_B));
	this->items_bg_.setSize(sf::Vector2f(INVENTORY_ITEM_SIZE * this->capacity_, INVENTORY_ITEM_SIZE));
	this->items_bg_.setOrigin(sf::Vector2f(INVENTORY_ITEM_SIZE, INVENTORY_ITEM_SIZE));

	this->selected_item_bg_.setFillColor(sf::Color(SELECTED_ITEM_R, SELECTED_ITEM_G, SELECTED_ITEM_B));
	this->selected_item_bg_.setSize(sf::Vector2f(INVENTORY_ITEM_SIZE, INVENTORY_ITEM_SIZE));
	this->selected_item_bg_.setOrigin(sf::Vector2f(INVENTORY_ITEM_SIZE, INVENTORY_ITEM_SIZE));
}

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

void Inventory::Draw(sf::RenderWindow& window)
{
	this->view_size_ = sf::Vector2f(window.getView().getSize());
	window.draw(this->items_bg_);
	window.draw(this->selected_item_bg_);

	for (unsigned int i = 0; i < this->GetCapacity(); i++)
	{
		if (i < this->GetSize())
		{
			sf::Sprite* sprite = &this->items_[i]->GetSprite();
			this->items_[i]->Draw(window);
		}
	}
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

void Inventory::Update(GameObject* relative_to, const float& delta_time)
{
	this->UpdateItems(delta_time);
	this->UpdatePosition(relative_to);
}

void Inventory::UpdateItems(const float& delta_time)
{
	for (auto& it : this->items_)
	{
		it->Update(delta_time);
	}
}

void Inventory::UpdatePosition(GameObject* relative_to)
{
	using namespace GAME_CONST;

	sf::Vector2f pos = relative_to->GetPosition();
	sf::Vector2f offset(INVENTORY_OFFSET_X, INVENTORY_OFFSET_Y);
	ScaleVec2f(offset, this->view_size_);

	this->items_bg_.setPosition(pos + offset);
	this->selected_item_bg_.setPosition(pos + offset + sf::Vector2f(INVENTORY_ITEM_SIZE * this->GetCurrentItemIndex(), 0.0f));

	for (unsigned int i = 0; i < this->GetSize(); i++)
	{
		sf::Sprite* it_spr = &this->items_[i]->GetSprite();
		float it_offset_x = INVENTORY_OFFSET_X - INVENTORY_ITEM_SIZE * 0.5f + INVENTORY_ITEM_SIZE * i;
		float it_offset_y = INVENTORY_OFFSET_Y - INVENTORY_ITEM_SIZE * 0.5f;
		sf::Vector2f item_offset(it_offset_x, it_offset_y);
		ScaleVec2f(item_offset, this->view_size_);

		it_spr->setPosition(pos+item_offset);
	}
}
