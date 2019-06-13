#pragma once
#ifndef __Tile__
#define __Tile__

#include "GameObject.h"
#include "TextureManager.h"
#include "Config.h"
#include "Label.h"

enum TileState {
	OPEN,
	CLOSED,
	START,
	GOAL,
	NUM_OF_TILE_STATES
};

class Tile : public GameObject
{
public:
	Tile(glm::vec2 position = glm::vec2(), glm::vec2 gridPosition = glm::vec2());
	~Tile();

	// Inherited via GameObject
	virtual void draw() override;

	virtual void update() override;

	virtual void clean() override;

	Tile* up();
	Tile* down();
	Tile* right();
	Tile* left();

	void setTileState(TileState state);
	TileState getTileState();

	void setTargetDistance(glm::vec2 goalLocation);

	glm::vec2 getGridPosition();

	float getTileValue();

	void setTileStateLabel(std::string closedOpen);

	float* getManhanttanFactor();
	void setManhanttanFactor(float newFactor);

	float* getEuclideanFactor();
	void setEuclideanFactor(float newFactor);

private:
	float m_cost = Config::TILE_COST;
	float m_targetDist = 0.0f;
	float m_tileValue = 0.0f;
	TileState m_tileState;
	glm::vec2 m_gridPosition;
	Label* m_pValueLabel;
	Label* m_pClosedOpenLabel;

	glm::vec2 m_goalLocation;
	
	static float m_manhanttanFactor;
	static float m_euclideanFactor;

};


#endif /* defined (__Tile__) */