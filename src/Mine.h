#pragma once
#ifndef __Mine__
#define __Mine__

#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Tile.h"

class Mine : public GameObject
{
public:
	Mine();
	~Mine();

	// Inherited via GameObject
	virtual void draw() override;

	virtual void update() override;

	virtual void clean() override;

	// pathfinding behaviours
	Tile* getTile();
	void setTile(Tile* newTile);
private:
	Tile* m_currentTile;
};


#endif /* defined (__Mine__) */