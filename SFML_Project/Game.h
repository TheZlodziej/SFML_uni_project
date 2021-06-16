#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "HelperFunctions.h"
#include "GameConstants.h"
#include "Camera.h"
#include "TextureManager.h"
#include "Cursor.h"
#include "Screen.h"

//test
#include "Hand.h"
#include "Entity.h"
#include "Player.h"
#include "Gun.h"
#include "Sword.h"
#include "Enemy.h"
#include "Terrain.h"
#include <iostream>

class Game
{
private:
	sf::RenderWindow window_;
	sf::Clock clock_;
	float delta_time_;
	Camera camera_;
	TextureManager textures_;
	Cursor cursor_;
	sf::Font* font_;
	std::unordered_map<SCREEN_TYPE, Screen> screens_;
	bool paused_;
	float enemies_spawn_timer_;
	float items_spawn_timer_;

	Player* player_;
	std::vector<Enemy*> enemies_;
	std::vector<Terrain*> terrain_;
	std::vector<Item*> items_;

public:
	Game();
	virtual ~Game();
	bool IsRunning();									// returns the state of the game window
	void LoadFont();									// load font for the game
	void Pause();										// pauses the game
	void SpawnItems();									// spawns a new item on the map when needed
	bool AnyScreenActive();								// returns true if any of the screen is set to active
	void PauseIfScreenOpened();							// pauses the screen if AnyScreenActive() returns true
	void LoadTextures();								// loads textures; call in constructor
	void HandleWindowEvents();							// function for handling window events (close, resize, etc.)
	void SetupCamera();									// sets default camera values
	void SpawnEnemies();								// spawns enemies when needed
	void SetupCursor();									// initializes cursor
	void RemoveOutOfMapObjects();						// removes objects that are out of map range
	void SetupScreens();								// adds default screens to the screens_ vector
	void ScreenInput();									// checks for input even if the game is in pause state
	void UpdateCursor();								// updates cursor position
	void SetupPlayer();									// sets default player values
	void SetupTerrain();								// spawns default terrain on the map
	void SetupEnemies();								// spawns deafult enemies on the map
	void SetupItems();									// spawns default items on the map
	void SpawnRandomItem();								// spawns random item around player
	void MouseInput();									// handles mouse inputs (click, movement, etc.)
	void Update();										// main update function
	void Draw();										// main draw function
	void CheckObjectsCollision();						// checks if objects are colliding and applying suitable behavior
	void DrawCursor();									// draws cursor
	void DrawScreens();									// calls draw for each screen that is active
	void UpdateScreens();								// calls update for each screen that is active
	void ClearWindow();									// clears window & sets its bg to certain color
	void DisplayWindow();								// displays updated window
	void UpdateGameObjects();							// calling update function for each game object
	void DrawGameObjects();								// calling draw function for each game object
	void HandleInputEvents();							// keybaords input for now
	void KeyboardInput();								// handles keyboard input && gets called in HandleInputEvents()
	void HandlePlayerMovement();						// handles player movements && gets called in KeyboardInput()
	void HandlePlayerInventory();						// handles player inventory && gets called in KeybaordInput()
	void SetDeltaTime();								// returns time elapsed from last call of this function
	void UpdateCamera();								// sets camera position at certain game object
};