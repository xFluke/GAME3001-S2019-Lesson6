#include "Game.h"
#include <ctime>

Game* Game::s_pInstance = 0;

glm::vec2 Game::getTargetPosition()
{
	return m_pTarget->getPosition();
}

SDL_Renderer * Game::getRenderer()
{
	return m_pRenderer;
}

glm::vec2 Game::getMousePosition()
{
	return m_mousePosition;
}

Game::Game()
{
}

Game::~Game()
{
}

void Game::m_createShips()
{
	srand((unsigned)time(NULL));  // random seed
	for (size_t count = 0; count < 5; count++)
	{
		ship* newShip = new ship();
		int randomRow = rand() % m_rowSize;
		int randomCol = rand() % m_colSize;
		Tile* tile = m_pGrid[randomRow][randomCol];
		newShip->setPosition(tile->getPosition());
		m_pShips.push_back(newShip);
	}
}

void Game::m_drawShips()
{
	for (ship* ship : m_pShips)
	{
		ship->draw();
	}
}

void Game::m_updateShips()
{
	for (ship* ship : m_pShips)
	{
		ship->update();
	}
}

void Game::m_createGrid()
{
	for (size_t row = 0; row < m_rowSize; row++)
	{
		for (size_t col = 0; col < m_colSize; col++)
		{
			m_pGrid[row][col] = new Tile(glm::vec2(row * m_tileSize + 20.0f, col * m_tileSize + 20.0f ));
		}
	}
}

void Game::m_drawGrid()
{
	for (size_t row = 0; row < m_rowSize; row++)
	{
		for (size_t col = 0; col < m_colSize; col++)
		{
			m_pGrid[row][col]->draw();
		}
	}
}

void Game::m_updateGrid()
{
	for (size_t row = 0; row < m_rowSize; row++)
	{
		for (size_t col = 0; col < m_colSize; col++)
		{
			m_pGrid[row][col]->update();
		}
	}
}

void Game::createGameObjects()
{
	m_createGrid();

	m_createShips();

	m_pTarget = new Target();
}

bool Game::init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL Init success" << std::endl;

		// if succeeded create our window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

		// if window creation successful create our renderer
		if (m_pWindow != 0)
		{
			std::cout << "window creation success" << std::endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) // render init success
			{
				std::cout << "renderer creation success" << std::endl;
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init failure" << std::endl;
				return false; // render int fail
			}

			//TheTextureManager::Instance()->load("../../Assets/textures/animate-alpha.png", "animate", m_pRenderer);
			createGameObjects();
		}
		else 
		{
			std::cout << "window init failure" << std::endl;
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init failure" << std::endl;
		return false; //SDL could not intialize
	}

	std::cout << "init success" << std::endl;
	m_bRunning = true; // everything initialized successfully - start the main loop

	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw colour

	m_drawGrid();
	m_pTarget->draw();
	m_drawShips();

	

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update()
{
	m_updateGrid();

	m_updateShips();

	m_pTarget->update();

}

void Game::clean()
{
	std::cout << "cleaning game" << std::endl;

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					m_bRunning = false;
					break;
				case SDLK_w:
					m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, -1.0f));
					break;
				case SDLK_s:
					m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, 1.0f));
					break;
				
				case SDLK_a:
					m_pTarget->setVelocity(glm::vec2(-1.0f, m_pTarget->getVelocity().y));
					break;
				case SDLK_d:
					m_pTarget->setVelocity(glm::vec2(1.0f, m_pTarget->getVelocity().y));
					break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
				case SDLK_w:
					if (m_pTarget->getVelocity().y < 0.0f) {
						m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, 0.0f));
					}
					break;
				
				case SDLK_s:
					if (m_pTarget->getVelocity().y > 0.0f) {
						m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, 0.0f));
					}
					break;
				
				case SDLK_a:
					if (m_pTarget->getVelocity().x < 0.0f) {
						m_pTarget->setVelocity(glm::vec2(0.0f, m_pTarget->getVelocity().y));
					}
					break;
				case SDLK_d:
					if (m_pTarget->getVelocity().x > 0.0f) {
						m_pTarget->setVelocity(glm::vec2(0.0f, m_pTarget->getVelocity().y));
					}
					break;
				
			}
			
		default:
			break;
		}
	}
}