#pragma once

namespace GAME_CONST
{
	const unsigned int WINDOW_WIDTH = 1200;
	const unsigned int WINDOW_HEIGHT = 800;

	const float ENTITY_MOVE_FORCE = 1000.0f;
	const float ENTITY_DRAG = 0.98f;	// drag is negative force (like friction) // this value shows how much of the previous force is gonna stay
	const float FLOAT_PRECISION = 0.001f;

	const float MAX_ENTITY_VELOCITY = 100.0f;
	const float MAX_ENTITY_ACCELERATION = 100.0f;
};