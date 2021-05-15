#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
private:
	sf::Vector2u animation_frames_; // this is max size of animations
	sf::Vector2u current_frame_;	// row & col of current animation
	float animation_frame_time_;	// time of 1 frame of animation (total_time/frames)
	float elapsed_time_;			// time elapsed since last frame
	sf::IntRect frame_rect_;		// size of single frame
	
public:
	Animation(sf::Texture& texture, const sf::Vector2u& animation_frames, const float& animation_time);
	virtual ~Animation();
	void UpdateFrame(const unsigned int& animation_row);						 // updates index of current frame
	void UpdateTextureRect();													 // updates current texture if the frame has to change
	void Update(const float& delta_time, const unsigned int& animation_row = 0); // first argument is to determinate which row of texture we're currently using; delta time is for animation time
	sf::IntRect GetFrameRect() const;											 // returns int rect that can be applied to sprite
};

