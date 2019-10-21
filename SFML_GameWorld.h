#ifndef SFML_GameWorld_H
#define SFML_GameWorld_H
#include <SFML/Graphics.hpp>
#include "SFML_SpriteObject.h"
#include "SFML_GameWorldLayer.h"
#include "SFML_AnimatedSpriteObject.h"
#include "SFML_NPCSpriteObject.h"
#include "SFML_PlayableSpriteObject.h"
#include "SFML_BulletSpriteObject.h"


class SFML_GameWorld :
	public sf::Drawable
{
public:
	SFML_GameWorld(int WindowWidth, int WindowHeight, sf::RenderWindow* parentWindow);
	~SFML_GameWorld();

	void update(float elapsedTime);

private:

	void processEvents(float elapsedTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Member attributes to store render window dimension 
	int m_windowWidth;
	int m_windowHeight;

	// The array to store the game world layers
	std::vector<SFML_GameWorldLayer*> m_GameWorldLayerList;

	// The member attribute to store the camera object
	SFML_2DCamera m_camera;

	// The member attribute to store camera position
	sf::Vector2f m_cameraPosition;

	SFML_SpriteObject m_spriteObject;

	// Member attribute to store pointer to the parent render window
	sf::RenderWindow* m_parentWindow;

	// Static function to be used to sort SFML_GameWorldLayer array
	static bool layerSortFunction(SFML_GameWorldLayer* a, SFML_GameWorldLayer* b);
	
	std::vector<SFML_SpriteObject*> m_staticObjectList;

	int m_selectedSpriteObjectID;
	bool m_prevLeftButtonPressed;

	sf::Texture m_zombieblood;
	sf::Sprite m_zombiebloodsprite;

	SFML_AnimatedSpriteObject* m_animatedObject;
	int m_idleAnimationID;

	std::vector<SFML_NPCSpriteObject*> m_zombieCharacterList;
	int m_numberOfZombies;

	SFML_PlayableSpriteObject* m_playerCharacter;

	std::vector<SFML_BulletSpriteObject*> m_bulletList;

	sf::Time DelayNight;
	sf::Time Night;
	//player health HUD
	sf::RectangleShape playerhealth;
	// player health HUD FONT
	sf::Font playerfont;
	sf::Text PlayerHealthText;
	sf::RectangleShape rect;

	// Time and clock for changing the color on the screen
	sf::Clock clockupdate; 
	sf::Time Timeupdate; 

	sf::Clock ClockElapsed; 
	sf::Time TimeElapsed; 

	sf::Clock ClockGone; 
	sf::Time TimeGone; 


	int SettingTimeUP;
	int TimeIsGone;

	// Guns sprite for HUD
	sf::Sprite Gun1Sprite;
	sf::Texture Gun1Texture;

	sf::Sprite TextSprite;
	sf::Texture TextTexture;

	sf::Sprite Text2Sprite;
	sf::Texture Text2Texture;

	sf::Sprite Gun2Sprite;
	sf::Texture Gun2Texture;

	sf::Sprite knifeSprite;
	sf::Texture knifeTexture;

	sf::Sprite flashSprite;
	sf::Texture flashTexture;

	bool PreviousNum1KeyPressed;
	bool PreviousNum2KeyPressed;
	bool PreviousNum3KeyPressed;
	bool PreviousNum4KeyPressed;

};


#endif // !SFML_GameWorld_H