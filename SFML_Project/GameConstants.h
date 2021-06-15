#pragma once
#include <SFML/Graphics.hpp>
namespace GAME_CONST
{
	const unsigned int WINDOW_WIDTH = 1200;
	const unsigned int WINDOW_HEIGHT = 800;
	
	const float PI = 3.1415f;

	const float CAMERA_HEIGHT = static_cast<float>(WINDOW_HEIGHT);
	const float CAMERA_WIDTH = static_cast<float>(WINDOW_WIDTH);
	const float CAMERA_ZOOM = 1.25f;

	const float PLAYER_HP = 200.0f;
	const float ENTITY_DRAG = 0.98f;					// drag is negative force (like friction) // this value shows how much of the previous force is gonna stay
	const float FLOAT_PRECISION = 0.001f;
	const float ENTITY_MOVE_ACCELERATION = 10.0f;		// acceleration on keyboard input
	const float MAX_ENTITY_VELOCITY = 50.0f;
	const float MAX_ENTITY_ACCELERATION = 10.0f;

	const float ENEMY_RANGE[] = { 500.0f, 1000.0f, 1500.0f };
	const float ENEMY_FOLLOW_ACCELERATION[] = {ENTITY_MOVE_ACCELERATION/3.0f, ENTITY_MOVE_ACCELERATION/2.0f, ENTITY_MOVE_ACCELERATION/1.5f};
	const float ENEMY_HP[] = { 50.0f, 150.0f, 300.0f };
	const float ENEMY_PUSH_BACK_FORCE[] = { 0.5f, 0.6f, 0.7f };
	const float ENEMY_SPAWN_TIME = 3.0f;
	const int ENEMY_SPAWN_RANGE = 500;

	const float HP_BAR_HEIGHT = 10.0f;
	const float HP_BAR_WIDTH = 120.0f;
	const float HP_BAR_OFFSET = 30.0f;
	const sf::Color HP_BAR_COLOR{ 220u, 0u, 44u };
	const sf::Color HP_BAR_BG_COLOR{ 26u, 26u, 26u };

	const float INVENTORY_OFFSET_X = -CAMERA_WIDTH * 0.5f; // % of the screen
	const float INVENTORY_OFFSET_Y = CAMERA_HEIGHT * 0.5f;
	const float INVENTORY_ITEM_SIZE = 50.0f;			   // it is a square so no need for 2 variables

	const sf::Color ITEMS_BG_COLOR{ 74u, 169u, 108u };
	const sf::Color SELECTED_ITEM_COLOR{ 159u, 230u, 160u };

	const sf::Color BG_COLOR{ 19u, 58u, 43u };

	const float BULLET_SPEED = 1000.0f;

	const float SWORD_SPEED = 270.0f;	// angular speed (degrees)
	const float SWORD_MAX_ROTATION = 45.0f;
	const float SWORD_POWER = 120.0f;
	
	const float MAP_WIDTH = 5000.0f;
	const float MAP_HEIGHT = MAP_WIDTH;

	const sf::Color SCREEN_BG_COLOR{ 46u, 46u, 46u, 200u };
	
	const float BUTTON_TOP_MARGIN = 25.0f;
	const float BUTTON_LEFT_MARGIN = 20.0f;
	const sf::Color BUTTON_COLOR{ 32u, 32u, 32u };
	const sf::Color BUTTON_HOVER_COLOR{ 16u, 16u, 16u };
};