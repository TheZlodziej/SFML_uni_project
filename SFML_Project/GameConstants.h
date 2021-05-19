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

	const float ENEMY_RANGE[] = { 150.0f, 200.0f, 250.0f };
	const float ENEMY_STRENGTH[] = { 10.0f, 20.0f, 30.0f };
	const float ENEMY_HP[] = { 1.0f, 1.5f, 3.0f };
};