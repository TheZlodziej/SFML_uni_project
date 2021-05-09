#include "Collider.h"

Collider::Collider(sf::Sprite& sprite):
	sprite_(sprite)
{}

Collider::~Collider()
{}

void Collider::Move(sf::Vector2f direction)
{
	this->sprite_.move(direction);
}

bool Collider::CheckCollision(Collider& obj, float back_force)
{
	sf::Vector2f this_pos = this->sprite_.getPosition();
	sf::Vector2f obj_pos = obj.sprite_.getPosition();

	sf::FloatRect this_rect = this->sprite_.getGlobalBounds();
	sf::FloatRect obj_rect = obj.sprite_.getGlobalBounds();

	sf::Vector2f this_half_size(this_rect.width / 2.0f, this_rect.height / 2.0f);
	sf::Vector2f obj_half_size(obj_rect.width / 2.0f, obj_rect.height / 2.0f);

	float dx = this_pos.x - obj_pos.x;
	float dy = this_pos.y - obj_pos.y;
	sf::Vector2f sum_of_half_sizes = this_half_size + obj_half_size;

	sf::Vector2f intersection(
		std::abs(dx) - sum_of_half_sizes.x,
		std::abs(dy) - sum_of_half_sizes.y
	);

	bool colliding = intersection.x < 0.0f && intersection.y < 0.0f;

	if (colliding)
	{
		ClampFloat(back_force, 0.0f, 1.0f);
		
		sf::Vector2f this_move_direction(0.0f, 0.0f);
		sf::Vector2f obj_move_direction(0.0f, 0.0f);

		if (intersection.x > intersection.y)
		{
			if (dx > 0.0f)
			{
				this_move_direction.x = -intersection.x * (1.0f - back_force);
				obj_move_direction.x = intersection.x * back_force;
			}
			else
			{
				this_move_direction.x = intersection.x * (1.0f - back_force);
				obj_move_direction.x = -intersection.x * back_force;
			}
		}
		else
		{
			if (dy > 0.0f)
			{
				this_move_direction.y = -intersection.y * (1.0f - back_force);
				obj_move_direction.y = intersection.y * back_force;
			}
			else
			{
				this_move_direction.y = intersection.y * (1.0f - back_force);
				obj_move_direction.y = -intersection.y * back_force;
			}
		}

		this->Move(this_move_direction);
		obj.Move(obj_move_direction);

		return true;
	}

	return false;
}