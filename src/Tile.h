#pragma once
#ifndef __Tile__
#define __Tile__

#include "GameObject.h"
#include "TextureManager.h"

class Tile : public GameObject
{
public:
	Tile(glm::vec2 position = glm::vec2());
	~Tile();

	// Inherited via GameObject
	virtual void draw() override;

	virtual void update() override;

	virtual void clean() override;
private:

};


#endif /* defined (__Tile__) */