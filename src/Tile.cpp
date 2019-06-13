#include "Tile.h"
#include "Game.h"
#include "Util.h"
#include <iomanip>
#include <sstream>

float Tile::m_manhanttanFactor = 1.5f;
float Tile::m_euclideanFactor = 1.5f;

Tile::Tile(glm::vec2 position, glm::vec2 gridPosition)
{
	m_gridPosition = gridPosition;
	TheTextureManager::Instance()->load("../Assets/textures/tile.png",
		"tile", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("tile");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(position);
	setTileState(TileState::OPEN);

	

	std::ostringstream tempLabel;
	tempLabel << std::fixed << std::setprecision(1) <<  m_tileValue;
	std::string labelstring = tempLabel.str();

	SDL_Color black{ 0, 0, 0, 255 };
	glm::vec2 closedOpenLabelPosition = glm::vec2(getPosition().x, getPosition().y - 5);
	m_pClosedOpenLabel = new Label("-", "Consolas", 12, black, closedOpenLabelPosition);

	glm::vec2 valueLabelPosition = glm::vec2(getPosition().x, getPosition().y + 10);
	m_pValueLabel = new Label(labelstring, "Consolas", 14, black, valueLabelPosition, true);
}

Tile::~Tile()
{
}

void Tile::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("tile", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, true);

	m_pClosedOpenLabel->draw();
	m_pValueLabel->draw();
}

void Tile::update()
{
}

void Tile::clean()
{
}

Tile * Tile::up()
{
	return TheGame::Instance()->getTile(m_gridPosition.x, m_gridPosition.y - 1);
}

Tile * Tile::down()
{
	return TheGame::Instance()->getTile(m_gridPosition.x, m_gridPosition.y + 1);
}

Tile * Tile::right()
{
	return TheGame::Instance()->getTile(m_gridPosition.x + 1, m_gridPosition.y);
}

Tile * Tile::left()
{
	return TheGame::Instance()->getTile(m_gridPosition.x - 1, m_gridPosition.y);
}

void Tile::setTileState(TileState state)
{
	m_tileState = state;
	if (state == TileState::GOAL)
	{
		m_tileValue = 0;
	}
}

TileState Tile::getTileState()
{
	return m_tileState;
}

void Tile::setTargetDistance(glm::vec2 goalLocation)
{
	m_goalLocation = goalLocation;

	if(m_gridPosition != goalLocation)
	{ 
	float x1 = m_gridPosition.x;
	float x2 = goalLocation.x;
	float y1 = m_gridPosition.y;
	float y2 = goalLocation.y;

	float dx = abs(x1 - x2);
	float dy = abs(y1 - y2);

	int count = 1;
	// check adjacent tiles **************************************
	if (m_gridPosition.y != 0) 
	{
		if (up()->getTileState() == TileState::CLOSED) {
			dy += 1;
			count++;
		}
	}

	if (m_gridPosition.y != Config::ROW_NUM - 1) 
	{
		if (down()->getTileState() == TileState::CLOSED)
		{
			dy += 1;
			count++;
		}
	}
	
	if (m_gridPosition.x != Config::COL_NUM - 1)
	{
		if (right()->getTileState() == TileState::CLOSED)
		{
			dx += 1;
			count++;
		}
	}
	
	if (m_gridPosition.x != 0)
	{
		if (left()->getTileState() == TileState::CLOSED)
		{
			dx += 1;
			count++;
		}
	}

	if (count > 3)
	{
		count = 50;
	}

	// heuristic combines manhattan distance with euclidean distance

	m_targetDist = m_manhanttanFactor * (dx + dy) + m_euclideanFactor * sqrt((dx *dx) + (dy * dy)) + count;
	//m_targetDist = 1.5 * (dx + dy) + 1.5 * sqrt((dx *dx) + (dy * dy)) + count;
	}
	else
	{
		// assigning the goal a cost of zero
		m_cost = 0;
		m_targetDist = 0;
	}

	m_tileValue = m_cost + m_targetDist;
	
	std::ostringstream tempLabel;
	tempLabel << std::fixed << std::setprecision(1) << m_tileValue;
	std::string labelstring = tempLabel.str();
	m_pValueLabel->setText(labelstring);
}

glm::vec2 Tile::getGridPosition()
{
	return m_gridPosition;
}

float Tile::getTileValue()
{
	return m_tileValue;
}

void Tile::setTileStateLabel(std::string closedOpen)
{
	m_pClosedOpenLabel->setText(closedOpen);

	SDL_Color blue = { 0, 0, 255, 255 };
	m_pClosedOpenLabel->setColour(blue);
}

float* Tile::getManhanttanFactor()
{
	return &m_manhanttanFactor;
}

void Tile::setManhanttanFactor(float newFactor)
{
	m_manhanttanFactor = newFactor;
	setTargetDistance(m_goalLocation);
}

float* Tile::getEuclideanFactor()
{
	return &m_euclideanFactor;
}

void Tile::setEuclideanFactor(float newFactor)
{
	m_euclideanFactor = newFactor;
	setTargetDistance(m_goalLocation);
}
