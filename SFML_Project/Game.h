#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "HelperFunctions.h"
#include "GameConstants.h"
#include "Camera.h"

//test
#include "Entity.h"
#include "Player.h"
#include <iostream>

class Game
{
private:
	sf::RenderWindow window_;
	std::vector<GameObject*> game_objects_;
	sf::Clock clock_;
	float delta_time_;
	Camera camera_;

	//test vars
	sf::Texture player_texture_;
	sf::Texture enemy_texture_;

public:
	Game();
	virtual ~Game();
	bool IsRunning();			// returns the state of the game window
	void HandleWindowEvents();  // function for handling window events
	void Update();				// main update function
	void Draw();				// main draw function
	void ClearWindow();			// clears window & sets its bg to certain color
	void DisplayWindow();		// displays updated window
	void UpdateGameObjects();	// calling update function for each game object
	void DrawGameObjects();		// calling draw function for each game object
	void HandleInputEvents();	// keybaords input for now
	void KeyboardInput();		// handles keyboard input && gets called in HandleInputEvents()
	void SetDeltaTime();		// returns time elapsed from last call of this function
	void UpdateCamera();		// sets camera position at certain game object
};