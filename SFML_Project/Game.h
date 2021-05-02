#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "GameObject.h"

//test
#include "Entity.h"

class Game
{
private:
	sf::RenderWindow window_;
	std::vector<GameObject*> game_objects_;
	sf::Clock clock_;

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
	float DeltaTime();			// returns time elapsed from last call of this function
};