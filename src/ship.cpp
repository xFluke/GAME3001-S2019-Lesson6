#include "ship.h"
#include "Game.h"
#include "Util.h"


ship::ship()
{
	TheTextureManager::Instance()->load("../Assets/textures/ship3.png",
		"ship", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("ship");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(500.0f, 500.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	//m_reset();
	setIsColliding(false);
	setType(GameObjectType::SHIP);
	setState(State::IDLE);
	m_maxSpeed = 5.0f;
	m_currentDirection = 0.0;
	m_turnSpeed = 2.0f;
	
	//TheTextureManager::Instance()->setColour("ship", 255, 255, 0);

	/*
	SoundManager::Instance()->load("../Assets/audio/yay.ogg",
		"yay", sound_type::SOUND_SFX);
	*/
}


ship::~ship()
{
}

void ship::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("ship", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), m_currentDirection, 255, true);
}

void ship::m_checkState()
{
	switch (getState())
	{
	case State::IDLE:
		break;
	case State::SEEK:
		m_seek();
		break;
	case State::ARRIVE:
		break;
	case State::AVOID:
		break;
	case State::FLEE:
		break;
	}
}

void ship::update()
{
	m_checkState();
	
	m_checkBounds();

	//std::cout << "current Direction:" << m_currentDirection << std::endl;
}

void ship::clean()
{
}

void ship::turnRight()
{
	m_currentDirection += m_turnSpeed;
}

void ship::turnLeft()
{
	m_currentDirection -= m_turnSpeed;
}

void ship::move()
{
	//glm::vec2 newPosition = getPosition() + getVelocity();

	glm::vec2 newPosition;
	newPosition.x = getPosition().x + (m_maxSpeed * cos(m_currentDirection * Util::Deg2Rad));
	newPosition.y = getPosition().y + (m_maxSpeed * sin(m_currentDirection * Util::Deg2Rad));
	setPosition(newPosition);
}

void ship::m_checkBounds()
{
	float distance = Util::distance(getPosition(), TheGame::Instance()->getTargetPosition());
	//std::cout << "distance: " << distance << std::endl;
	if(distance <= 5.0f)
	{
		setState(State::IDLE);
		
	}
}

void ship::m_reset()
{
	setIsColliding(false);
	int halfWidth = getWidth() * 0.5;
	int xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	int yComponent = -getHeight();
	setPosition(glm::vec2(xComponent, yComponent));
}

void ship::m_seek()
{
	m_target = TheGame::Instance()->getTargetPosition();
	glm::vec2 targetDirection = m_target;
	targetDirection.x -= getPosition().x;
	targetDirection.y -= getPosition().y;
	
	if (Util::squaredMagnitude(targetDirection) > 2.0f) {
		targetDirection = Util::normalize(targetDirection);
		//setVelocity(targetDirection * m_maxSpeed);
	}

	//glm::vec2 offset = m_target;
	double desiredDirection;
	if (targetDirection.x * targetDirection.x + targetDirection.y * targetDirection.y > 0) {
		desiredDirection = atan2(targetDirection.x, -targetDirection.y);
		
		desiredDirection *= Util::Rad2Deg; // convert to degrees

		desiredDirection -= 90.0;

		//m_currentDirection = (desiredDirection - m_currentDirection > 0) ? m_currentDirection + m_turnSpeed : m_currentDirection - m_turnSpeed;

		std::cout << "=============================" << std::endl;
		std::cout << "Current Direction : " << m_currentDirection << std::endl;
		std::cout << "Desired Direction : " << desiredDirection << std::endl;
		std::cout << "Desired Direction - current: " << desiredDirection - m_currentDirection << std::endl;
		std::cout << "=============================" << std::endl;

		if (desiredDirection - m_currentDirection > 0)
		{
			turnRight();
		}
		else if (desiredDirection - m_currentDirection < 0)
		{
			turnLeft();
		}

		move();
	}
	else {
		desiredDirection = 0.0;
		m_currentDirection = desiredDirection;
	}
}
