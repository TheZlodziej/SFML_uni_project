#include "HpBar.h"

HpBar::HpBar(const float& max_hp) :
	hp(max_hp),
	max_hp(max_hp)
{
	using namespace GAME_CONST;

	bar.setOrigin(static_cast<float>(HP_BAR_WIDTH) * 0.5f, static_cast<float>(HP_BAR_HEIGHT) * 0.5f);
	bar.setSize(sf::Vector2f(HP_BAR_WIDTH, HP_BAR_HEIGHT));
	bar.setFillColor(sf::Color(HP_BAR_R, HP_BAR_G, HP_BAR_B));
}

void HpBar::UpdatePosition(GameObject* relative_to)
{
	sf::Sprite* sprite = &relative_to->GetSprite();
	sf::Vector2f pos = sprite->getPosition();

	float offset =  -sprite->getGlobalBounds().height * 0.5f - 30.0f;
	pos.y += offset;

	this->bar.setPosition(pos);
}

void HpBar::UpdateSize()
{
	this->bar.setSize(sf::Vector2f(this->hp / this->max_hp * GAME_CONST::HP_BAR_WIDTH, GAME_CONST::HP_BAR_HEIGHT)); //maybe bug with origin
}

void HpBar::Draw(sf::RenderWindow& window)
{
	window.draw(this->bar);
}

void HpBar::Update(GameObject* relative_to)
{
	this->UpdatePosition(relative_to);
	this->UpdateSize();
}