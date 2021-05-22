#pragma once

namespace GAME_CONST
{
	const unsigned int WINDOW_WIDTH = 1200;
	const unsigned int WINDOW_HEIGHT = 800;
	
	const float PI = 3.1415f;

	const float CAMERA_HEIGHT = static_cast<float>(WINDOW_HEIGHT);
	const float CAMERA_WIDTH = static_cast<float>(WINDOW_HEIGHT);
	const float CAMERA_ZOOM = 1.25f;

	const float ENTITY_DRAG = 0.98f;					// drag is negative force (like friction) // this value shows how much of the previous force is gonna stay
	const float FLOAT_PRECISION = 0.001f;
	const float ENTITY_MOVE_ACCELERATION = 10.0f;		// acceleration on keyboard input
	const float MAX_ENTITY_VELOCITY = 50.0f;
	const float MAX_ENTITY_ACCELERATION = 10.0f;

	const float ENEMY_RANGE[] = { 500.0f, 1000.0f, 1500.0f };
	const float ENEMY_FOLLOW_ACCELERATION[] = {ENTITY_MOVE_ACCELERATION/3.0f, ENTITY_MOVE_ACCELERATION/2.0f, ENTITY_MOVE_ACCELERATION/1.5f};
	const float ENEMY_STRENGTH[] = { 10.0f, 20.0f, 30.0f };
	const float ENEMY_HP[] = { 1.0f, 1.5f, 3.0f };
	
	const float HP_BAR_HEIGHT = 10.0f;
	const float HP_BAR_WIDTH = 120.0f;
	const unsigned int HP_BAR_R = 220;
	const unsigned int HP_BAR_G = 0;
	const unsigned int HP_BAR_B = 44;
};