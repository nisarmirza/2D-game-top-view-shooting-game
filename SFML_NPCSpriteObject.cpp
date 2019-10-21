#include "pch.h"
#include "SFML_NPCSpriteObject.h"


SFML_NPCSpriteObject::SFML_NPCSpriteObject()
	: m_targetLocation(0, 0)
	, m_moveSpeed(100.0f)
	, m_state(IDLE)
	, m_idleAnimationID(-1)
	, m_walkingAnimationID(-1)
	, m_attackingAnimationID(-1)
	, m_bloodanimationid(-1)
	, m_visionConeAngle(90.0f)
	, m_visionRange(1200.0f)
	, m_alive(true)
{
}

SFML_NPCSpriteObject::~SFML_NPCSpriteObject()
{
}

int SFML_NPCSpriteObject::setIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_idleAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_idleAnimationID;
}

int	SFML_NPCSpriteObject::setWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_walkingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_walkingAnimationID;
}

int SFML_NPCSpriteObject::setAttackingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_attackingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_attackingAnimationID;
}

int SFML_NPCSpriteObject::setBloodAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_bloodanimationid = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_bloodanimationid;
}


void SFML_NPCSpriteObject::toIdleState()
{
	m_state = IDLE;
	setCurrentAnimation(m_idleAnimationID);
}

void SFML_NPCSpriteObject::toWalkingState()
{
	m_state = WALKING;
	setCurrentAnimation(m_walkingAnimationID);
}

void SFML_NPCSpriteObject::toAttackingState()
{
	m_state = ATTACKING;
	setCurrentAnimation(m_attackingAnimationID);
}

bool SFML_NPCSpriteObject::isInVision(sf::Vector2f targetpoint)
{
	const float pi = 3.1415f;

	// Get the NPC's current location
	sf::Vector2f currentPosition = getPosition();

	// Claculate the vector from NPC's current position to the target position
	sf::Vector2f vector = targetpoint - currentPosition;

	// Calculate the distance (L2-norm) between the current location and target position
	float distance = sqrt(vector.x * vector.x + vector.y * vector.y);

	// Check if distance is outside vision range
	if(distance > m_visionRange)
	return false;
	
	// Get the NPC's orientation . Note the getRotation() always produce angle in degree and 
	// in 0 -360 range
	float faceAngle = getRotation();

	// calculate the angle of the vector
	float targetAngle = atan2(vector.y, vector.x);

	// Convert to degree
	targetAngle = targetAngle * 180 / pi;
	
	// The angle could be outside 0 -360 range, so we need to conver it to 
	// 0 - 360 range

	while (targetAngle > 360)
		targetAngle = targetAngle - 360;
	while (targetAngle < 0)
		targetAngle = targetAngle + 360;

	// Claculate the absolute difference between targetAngle and faceAngle
	float angleDifference = fabs(targetAngle - faceAngle);

	// If within half of the vision cone angle then it is within the vision cone
	if (angleDifference <= m_visionConeAngle / 2)
		return true;
	else
		return false;


	
}


void SFML_NPCSpriteObject::setTargetLocation(sf::Vector2f targetLocation)
{
	m_targetLocation = targetLocation;
}

void SFML_NPCSpriteObject::setMovementSpeed(float speed)
{
	m_moveSpeed = speed;
}

void SFML_NPCSpriteObject::update(float elapsedTime)
{

	if (!m_alive)
		return;

	const float pi = 3.1415f;
	// Get the NPC's current location
	sf::Vector2f currentPosition = getPosition();

	// calculate the vector from the NPC's current position to the target point
	sf::Vector2f faceDirection = m_targetLocation - currentPosition;

	// Claculate the distance (L2-norm) between the current location and the target position
	float distance = sqrt(faceDirection.x * faceDirection.x + faceDirection.y * faceDirection.y);

	// If the distance is less than the displacement to cover in this frame
	if (distance < elapsedTime * m_moveSpeed)
	{
		// That means this NPC has reached its destination point
		setPosition(m_targetLocation);

		// Set the animation to idle
		if (m_state != ATTACKING )
		{
			toIdleState();
		}
		
	}
	else
	{
		// Otherwise it needs to keep moving
		float angle = atan2(faceDirection.y, faceDirection.x);
		setRotation(angle / pi * 180);

		// Calculate the movement vector
		sf::Vector2f unitMoveVector = sf::Vector2f(cos(angle), sin(angle));
		sf::Vector2f totalMoveVector = unitMoveVector * elapsedTime * m_moveSpeed;
		move(totalMoveVector);

		// Set the animation to walking
		if (m_state != ATTACKING)
		{
			toWalkingState();
		}
		
	}
	SFML_AnimatedSpriteObject::update(elapsedTime);
}
