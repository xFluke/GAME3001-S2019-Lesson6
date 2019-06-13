#pragma once
#ifndef __Game__
#define __Game__

// Core Libraries
#include <iostream>
#include <vector>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// IMGUI Includes
#include "IMGUI/imgui.h"
#include "IMGUI_SDL/imgui_sdl.h"

// Game Managers
#include "Config.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Util.h"

// Game Objects
#include "ship.h"
#include "Target.h"
#include "Tile.h"
#include "Label.h"
#include "Planet.h"
#include "Mine.h"

class Game
{
public:
	

	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}

		return s_pInstance;
	}

	// simply set the running variable to true
	void init() { m_bRunning = true; }

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	// public functions
	void render();
	void update();
	void handleEvents();
	void clean();

	// a function to access the private running variable
	bool running() { return m_bRunning; }

	// Steering related functions
	glm::vec2 getTargetPosition();
	void setTargetPosition(glm::vec2 newPosition);

	// getters
	SDL_Renderer* getRenderer();
	glm::vec2 getMousePosition();

	// Pathfinding functions
	Tile* getTile(int row, int col);
	glm::vec2 getGoalLocation();
	void setGoalLocation(glm::vec2 newLocation);
	void findShortestPath();
	void resetClosedAndOpen();

	void setFrames(Uint32 frames);
	Uint32 getFrames();
	

private:
	Game();
	~Game();

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_currentFrame;

	bool m_bRunning;

	static Game* s_pInstance;

	// GameObjects
	std::vector<Ship*> m_pShips;
	std::vector<Mine*> m_pMines;
	Target* m_pTarget;
	Label* m_pLabel;
	Planet* m_pPlanet;

	// utility functions for ship control
	void m_createShips();
	void m_drawShips();
	void m_updateShips();
	void m_respawnShips();
	void m_moveShipsAlongPath();

	// utility functions for planet control
	void m_createPlanet();
	void m_respawnPlanet();

	// utility functions for mine control
	void m_createMines();
	void m_drawMines();
	void m_updateMines();
	void m_respawnMines();

	// Tile and Grid variables
	const int m_rowSize = Config::ROW_NUM;
	const int m_colSize = Config::COL_NUM;
	const int m_tileSize = Config::TILE_SIZE;
	Tile* m_pGrid[Config::COL_NUM][Config::ROW_NUM]; // grid of tile pointers
	glm::vec2 m_goalLocation;
	bool m_moveAlongPath = false;
	int m_pathLength = 0;

	std::vector<Tile* > m_pOpen;
	std::vector<Tile* > m_pClosed;

	// utility functions for tile and grid
	void m_createGrid();
	void m_drawGrid();
	void m_updateGrid();
	bool m_debugMode = false;
	
	void createGameObjects();

	glm::vec2 m_mousePosition;

	// ImGui utility functions
	void m_ImGuiKeyMap();
	void m_ImGuiSetStyle();
	void m_updateUI();

	// ImGui menu variables
	bool m_exitApp = false;
	bool m_displayAbout = false;
	bool m_displayUI = true;

	Uint32 m_frames;

	void m_resetAll();

	float m_newFloat = 1.5f;
};

typedef Game TheGame;

#endif /* defined (__Game__) */

