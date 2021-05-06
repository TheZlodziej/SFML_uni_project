#pragma once

namespace GAME_CONST
{
	const float T = 1.0f;

	const unsigned int WINDOW_WIDTH = 1200;
	const unsigned int WINDOW_HEIGHT = 800;
	
	const float PI = 3.1415f;

	const float CAMERA_HEIGHT = static_cast<float>(WINDOW_HEIGHT);
	const float CAMERA_WIDTH = static_cast<float>(WINDOW_HEIGHT);

	const float ENTITY_DRAG = 0.98f;					// drag is negative force (like friction) // this value shows how much of the previous force is gonna stay
	const float FLOAT_PRECISION = 0.001f;
	const float ENTITY_MOVE_ACCELERATION = 10.0f * T;	// acceleration on keyboard input
	const float MAX_ENTITY_VELOCITY = 50.0f * T;
	const float MAX_ENTITY_ACCELERATION = 10.0f * T;
};