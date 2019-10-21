#ifndef SFML_SpriteAnimation_H
#define SFML_SpriteAnimation_H

#include <SFML/Graphics.hpp>


class SFML_SpriteAnimation
{
public:
	SFML_SpriteAnimation();
	~SFML_SpriteAnimation();

	// Member function to store memory address of the texture to use
	void setSpriteSheet(sf::Texture* spriteTexture);

	// Member function to add a frame (Rectangle and Centre)
	void addFrame(sf::IntRect textureRect, sf::Vector2f centre);

	// Member function that return current frame information (rectangle and Centre)
	bool getCurrentFrame(sf::IntRect* rect, sf::Vector2f* centre);

	// Member function to set the delay between showing consecutive frames
	void setFrameTime(float timeperFrame);

	// Member function that returns the delat between showing consecutive frames
	float getTimePerFrame();

	// Member function that returns the address of the texture used
	sf::Texture* getSpriteSheet();

	// Member function that returns the number of frames in this animation
	int getNumberOfFrames();
	void getTextureInfo(int newFrame, sf::IntRect* rect, sf::Vector2f* centre);

	// Member functions to set and get interruptible flag
	void setCanBeInterrupted(bool trueorflase);
	bool canBeInterrupted() const;

	// Member functions to set and get loop flag 
	bool isLooped() const;
	void setLoop(bool loop);


	float getFrameTime();

	// Member functions to increment and get frame number, and reset animation
	void incrementFrameNumber();
	int getCurrentFrameNumber();
	void resetCurrentAnimation();
	
	
	// Member function to check if the animation is completed
	// This will never be true if the animation is looping
	bool isCompleted();



private:

	// Frames information (Rectangles and Centres)
	std::vector<sf::IntRect> m_frameRectangleList;
	std::vector<sf::Vector2f> m_frameCentreList;

	// Pointer to the texture object
	sf::Texture* m_spriteSheet;

	// Current frame numbers and time delay
	int m_currentFrameNumber;
	float m_timePerFrame;

	// Animaiton controls
	bool m_isLoop;
	bool m_canBeInterrupted;


};


#endif // !SFML_SpriteAnimation