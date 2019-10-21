#ifndef SFML_AnimatedSpriteObject_H
#define SFML_AnimatedSpriteObject_H


#include "SFML_SpriteObject.h"
#include "SFML_SpriteAnimation.h"


class SFML_AnimatedSpriteObject :
	public SFML_SpriteObject
{
public:
	SFML_AnimatedSpriteObject();

	virtual ~SFML_AnimatedSpriteObject();

	// Member functions to add animation sequence
	int addAnimation(std::string spriteSheetFileName, std::string SpriteInfoFileName, float animationTime);

	// Member function that sets the current animation
	void setCurrentAnimation(int animationIndex);


	// Member function that returns the address to the current animation
	SFML_SpriteAnimation* getCurrentAnimation();

	// Member function that updates object states and variables
	virtual void update(float elapsedTime);

	// Member functions to control playback
	void play();
	void pause();
	void stop();



private:

	std::vector<sf::Texture*> m_spriteTextureList;
	int m_currentAnimationID;
	float m_CurrentTime;
	bool m_isPaused;

protected:

	std::vector<SFML_SpriteAnimation*> m_animatedSpriteList;
	SFML_SpriteAnimation* m_currentAnimation;
};

#endif // !SFML_AnimatedSpriteObject_H