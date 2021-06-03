#include "Animation.h"

Animation::Animation(sf::Texture& texture, const sf::Vector2u& animation_frames, const float& animation_time):
animation_frames_(animation_frames),
elapsed_time_(0.0f),
current_frame_(0,0),
state_(ANIMATION_STATE::IDLE)
{
	this->frame_rect_.width = texture.getSize().x / animation_frames.x;
	this->frame_rect_.height = texture.getSize().y / animation_frames.y;
	this->animation_frame_time_ = animation_time / static_cast<float>(animation_frames.x);
}

Animation::~Animation()
{
}

void Animation::UpdateFrame()
{
	unsigned int state_row = static_cast<unsigned int>(this->state_);

	if (this->elapsed_time_ < this->animation_frame_time_) { return; }

	if (this->current_frame_.y == state_row)
	{
		this->current_frame_.x = (this->current_frame_.x + 1) % this->animation_frames_.x;
	}
	else
	{
		this->current_frame_ = sf::Vector2u(0, state_row);
	}

	this->UpdateTextureRect();
}

void Animation::UpdateTextureRect()
{
	this->frame_rect_.left = this->current_frame_.x * this->frame_rect_.width;
	this->frame_rect_.top = this->current_frame_.y * this->frame_rect_.height;
	this->elapsed_time_ = 0.0f;
}

void Animation::Update(const float& delta_time)
{
	this->elapsed_time_ += delta_time;
	this->UpdateFrame();
}

sf::IntRect Animation::GetFrameRect() const
{
	return this->frame_rect_;
}

void Animation::UpdateState(const ANIMATION_STATE& state)
{
	this->state_ = state;
}
