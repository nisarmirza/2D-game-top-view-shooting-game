#include "pch.h"
#include "SFML_GameWorld.h"
#include "SFML_SpriteObject.h"


SFML_GameWorld::SFML_GameWorld(int WindowWidth, int WindowHeight, sf::RenderWindow* parentWindow)
	: m_windowWidth(WindowWidth)
	, m_windowHeight(WindowHeight)
	, m_camera(WindowWidth, WindowHeight)
	, PreviousNum1KeyPressed(false)
	, PreviousNum2KeyPressed(false)
	, PreviousNum3KeyPressed(false)
	, PreviousNum4KeyPressed(false)
	
{
	// create a gameworld layer object using dirt.png texture
	SFML_GameWorldLayer* background = new SFML_GameWorldLayer("Media/Textures/dirt.png", 1.0f, WindowWidth, WindowHeight);
	
	// Insert it to the array
	m_GameWorldLayerList.push_back(background);

	// Set the camera's inital position to (0,0)
	m_cameraPosition = sf::Vector2f(0, 0);
	
	SFML_GameWorldLayer* MiddleLayer2 = new SFML_GameWorldLayer("Media/Textures/fog.png", 0.9f, WindowWidth, WindowHeight);
	m_GameWorldLayerList.push_back(MiddleLayer2);

	/*SFML_SpriteObject* staticObject01 = new SFML_SpriteObject();
	staticObject01->setDefaultTexture("Media/Textures/soldier.png", "Media/Textures/soldier.txt");
	staticObject01->setPosition(250, 250);
	m_staticObjectList.push_back(staticObject01);*/

	// Create a gameworld layer object using the wire.png texture
	SFML_GameWorldLayer* foreGround = new SFML_GameWorldLayer("Media/Textures/wire.png", 0.3f, WindowWidth, WindowHeight);
	
	// Insert it to the array
	m_GameWorldLayerList.push_back(foreGround);

	// Sort the game world in decending order
	std::sort(m_GameWorldLayerList.begin(), m_GameWorldLayerList.end(), layerSortFunction);

	// Set default texture using soldier.png image
	// m_spriteObject.setDefaultTexture("Media/Textures/soldier.png", "Media/Textures/soldier.txt");
	
	// Set position to (0,0)
    //m_spriteObject.setPosition(0, 0);

	MiddleLayer2->setScrollSpeed(m_cameraPosition);

	// Store the address of the parent render window in m_parentWindow
	m_parentWindow = parentWindow;
	
	m_animatedObject = new SFML_AnimatedSpriteObject();

	m_idleAnimationID = m_animatedObject->addAnimation("Media/textures/hero_pistol_idle.png", "Media/Textures/hero_pistol_idle.txt", 1.0f);
	m_animatedObject->setPosition(0, 0);
	m_animatedObject->setCurrentAnimation(m_idleAnimationID);

	/*Gun1Texture.loadFromFile("Media/Textures/slot1.png");
	Gun1Sprite.setTexture(Gun1Texture);
	Gun1Sprite.setPosition(1750, 200);*/

	

	// Number of zombies on the map
	m_numberOfZombies = 30;
	for (int i = 0; i < m_numberOfZombies; i++)
	{
		SFML_NPCSpriteObject* npcSprite = new SFML_NPCSpriteObject();
		npcSprite->setIdleAnimation("Media/Textures/zombie-idle.png", "Media/Textures/zombie-idle.txt", 1.0f);
		npcSprite->setWalkingAnimation("Media/Textures/zombie-move.png", "Media/Textures/zombie-move.txt", 1.0f);
		npcSprite->setAttackingAnimation("Media/Textures/zombie-attack.png", "Media/Textures/zombie-attack.txt", 1.0f);
		npcSprite->setBloodAnimation("Media/Textures/blood.png", "Media/Textures/blood.txt", 1.0f);
		npcSprite->setPosition(rand() % 4000 - 2000, rand() % 4000 - 2000);
		npcSprite->setTargetLocation(sf::Vector2f(rand() % 4000 - 2000, rand() % 4000 - 2000));
		m_zombieCharacterList.push_back(npcSprite);
		
		
	}


	 // This for equipping the flashlight
	m_playerCharacter = new SFML_PlayableSpriteObject();
	m_playerCharacter->setFlashlightIdleAnimation("Media/Textures/hero_flashlight_idle.png", "Media/Textures/hero_flashlight_idle.txt", 1.0f);
	m_playerCharacter->setFlashlightWalkingAnimation("Media/Textures/hero_flashlight_move.png", "Media/Textures/hero_flashlight_move.txt", 1.0f);
	m_playerCharacter->setFlashlightMeleeAnimation("Media/Textures/hero_flashlight_melee.png", "Media/Textures/hero_flashlight_melee.txt", 1.0f);
	   
	// Setting up sprite animation to work in the game if certain key will be pressed in the update
	m_playerCharacter->setRifleIdleAnimation("Media/Textures/hero_rifle_idle.png", "Media/Textures/hero_rifle_idle.txt", 1.0f);
	m_playerCharacter->setRifleWalkingAnimation("Media/Textures/hero_rifle_move.png", "Media/Textures/hero_rifle_move.txt", 1.0f);
	m_playerCharacter->setRifleMeleeAnimation("Media/Textures/hero_rifle_melee.png", "Media/Textures/hero_rifle_melee.txt", 1.0f);
	m_playerCharacter->setRifleShootAnimation("Media/Textures/hero_rifle_shoot.png", "Media/Textures/hero_rifle_shoot.txt", 1.0f);
	m_playerCharacter->setRifleReloadAnimation("Media/Textures/hero_rifle_reload.png", "Media/Textures/hero_rifle_reload.txt", 1.0f);

	// Setting up sprite animation to work in the game if certain key will be pressed in the update
	m_playerCharacter->setKnifeIdleAnimation("Media/Textures/hero_knife_idle.png", "Media/Textures/hero_knife_idle.txt", 1.0f);
	m_playerCharacter->setKnifeWalkingAnimation("Media/Textures/hero_knife_move.png", "Media/Textures/hero_knife_move.txt", 1.0f);
	m_playerCharacter->setKnifeMeleeAnimation("Media/Textures/hero_knife_melee.png", "Media/Textures/hero_knife_melee.txt", 1.0f);
	
	// Setting up sprite animation to work in the game if certain key will be pressed in the update
	m_playerCharacter->setPistolIdleAnimation("Media/Textures/hero_pistol_idle.png", "Media/Textures/hero_pistol_idle.txt", 1.0f);
	m_playerCharacter->setPistolWalkingAnimation("Media/Textures/hero_pistol_move.png", "Media/Textures/hero_pistol_move.txt", 1.0f);
	m_playerCharacter->setPistolMeleeAnimation("Media/Textures/hero_pistol_melee.png", "Media/Textures/hero_pistol_melee.txt", 1.0f);
	m_playerCharacter->setPistolShootAnimation("Media/Textures/hero_pistol_shoot.png", "Media/Textures/hero_pistol_shoot.txt", 1.0f);
	m_playerCharacter->setPistolReloadAnimation("Media/Textures/hero_pistol_reload.png", "Media/Textures/hero_pistol_reload.txt", 1.0f);

	// When you start the game, player will be starting with the knife equipped.
	m_playerCharacter->equipKnife();
	m_playerCharacter->toIdleState();


	Gun1Texture.loadFromFile("Media/Textures/Knife.png");
	Gun1Sprite.setTexture(Gun1Texture);
	Gun1Sprite.setPosition(1750, 200);

	TextTexture.loadFromFile("Media/Textures/PlayerHealthText.png");
	TextSprite.setTexture(TextTexture);
	TextSprite.getTexture();
	TextSprite.setPosition(1490, 40);

	Text2Texture.loadFromFile("Media/Textures/Equipped.png");
	Text2Sprite.setTexture(Text2Texture);
	Text2Sprite.getTexture();
	Text2Sprite.setPosition(1490, 200);


}

SFML_GameWorld::~SFML_GameWorld()
{
	// Clear the GameWorldLayer list ----------------------------------------------------------
	for (std::vector<SFML_GameWorldLayer*>::iterator it = m_GameWorldLayerList.begin();
		it != m_GameWorldLayerList.end();
		it++)
	{
		delete (*it);
	}
	m_GameWorldLayerList.clear();

	// Clear the static object
	for (std::vector<SFML_SpriteObject*>::iterator it = m_staticObjectList.begin();
		it != m_staticObjectList.end();
		it++)
	{
		delete (*it);
	}
	m_staticObjectList.clear();
	// Clear the memory space used for animated object
	//delete m_animatedObject;
}

void SFML_GameWorld::update(float elapsedTime)
{
	processEvents(elapsedTime);
	//m_camera.setPosition(m_cameraPosition);

	for (int counter = 0; counter < m_GameWorldLayerList.size(); counter++)
	{
		m_GameWorldLayerList[counter]->followCamera(&m_camera);
	}

	for (std::size_t counter = 0; counter < m_GameWorldLayerList.size(); counter++)
	{
		m_GameWorldLayerList[counter]->followCamera(&m_camera);
		m_GameWorldLayerList[counter]->Update(elapsedTime);
	}

	// Update each sprite in the list
	for (unsigned int counter = 0; counter < m_staticObjectList.size(); counter++)
	{
		m_staticObjectList[counter]->update(elapsedTime);
	}

	// Update the sprite object
	//m_spriteObject.update(elapsedTime);
	//m_animatedObject->update(elapsedTime);

	// Update each zombie object in the list
	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
	{
		m_zombieCharacterList[counter]->update(elapsedTime);
	}
	m_playerCharacter->update(elapsedTime);
	m_camera.setPosition(m_playerCharacter->getWorldPosition());

	// updating all bullets -----------------
	for (unsigned int counter = 0; counter < m_bulletList.size(); counter++)
	{
		m_bulletList[counter]->update(elapsedTime);
	}

	//playerfont.loadFromFile("Media/Fonts/youmurdererbb_reg.otf");
	//PlayerHealthText.setString("hello");
	//PlayerHealthText.setCharacterSize(30);
	//PlayerHealthText.setStyle(sf::Text::Bold);
	//PlayerHealthText.setFillColor(sf::Color::Red);

	
	

	SettingTimeUP = static_cast<unsigned int>(ClockElapsed.getElapsedTime().asSeconds());
	ClockElapsed.getElapsedTime();

	TimeGone += ClockGone.restart();
	TimeIsGone = static_cast<unsigned int>(TimeGone.asSeconds());
	if ((TimeIsGone > 20) &&  (SettingTimeUP >= 20))
	{
			Timeupdate += clockupdate.restart();

			if (Timeupdate >= sf::seconds(.2f))
			{
					Timeupdate -= sf::seconds(.01f);
					rect.setSize(sf::Vector2f(1980, 1080));
					rect.setFillColor(sf::Color(255, 200, 140));

			}
	}
	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
	{
		if (m_zombieCharacterList[counter]->isInVision(m_playerCharacter->getWorldPosition()))
		{
			m_zombieCharacterList[counter]->setTargetLocation(m_playerCharacter->getWorldPosition());

			// Getting the bouding boxes for the player and the zombies so when they get closer to each other theu die
			sf::FloatRect PLayerBox = m_playerCharacter->getGlobalBounds();
			sf::FloatRect EnemyBox = m_zombieCharacterList[counter]->getGlobalBounds();
			//sf::FloatRect BulletBox = m_bulletList[counter]->getGlobalBounds();

			// IF statment, if the bounding box of the player intersect with the bounding box of the enemy then the enemy will die. basically i used bool for zombies so if they intersect zombies diables.
			if (PLayerBox.intersects(EnemyBox) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				m_zombieCharacterList[counter]->m_alive = false;
				
				//m_zombieCharacterList[counter]->setBloodAnimation("Media/Textures/blood.png", "Media/Textures/blood.txt", 1.0f);
				//m_zombieCharacterList[counter]->setPosition(0, 0);
				//if (m_zombieCharacterList[counter]->m_alive = false)
			//	playerhealth.getSize();
				
				
			}
			else if (EnemyBox.intersects(PLayerBox))
			{
				m_zombieCharacterList[counter]->toAttackingState();
				//for (int i = 0; i < playerhealth; i++)
				//{
				/*float h;
				playerhealth = (h / 300) * 100;*/

					playerhealth.setSize(sf::Vector2f(150, 50));
					playerhealth.setOutlineColor(sf::Color::Black);
					playerhealth.setFillColor(sf::Color::Red);
					playerhealth.setOutlineThickness(5);
					playerhealth.setPosition(1750, 50);
					playerhealth.setTextureRect(sf::IntRect(0, 0, 50, 0));
				//}
			}
			
		}
	}
	
	// IF function used for selecting the playerstate in the game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_playerCharacter->equipFlashlight();
		m_playerCharacter->toIdleState();
		/*Gun1Texture.loadFromFile("Media/Textures/slot1.png");
		Gun1Sprite.setTexture(Gun1Texture);
		Gun1Sprite.setPosition(1750, 200);*/
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_playerCharacter->equipKnife();
		m_playerCharacter->toIdleState();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		m_playerCharacter->equipPistol();
		m_playerCharacter->toIdleState();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		m_playerCharacter->equipRifle();
		m_playerCharacter->toIdleState();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_playerCharacter->equipRifle();
		m_playerCharacter->toReloadState();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	{
		m_playerCharacter->equipPistol();
		m_playerCharacter->toReloadState();
	}

	bool CurrentNum1KeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);
	bool CurrentNum2KeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num2);
	bool CurrentNum3KeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num3);
	bool CurrentNum4KeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num4);

	if (CurrentNum1KeyPressed && !PreviousNum1KeyPressed)
	{
		Gun1Texture.loadFromFile("Media/Textures/FlashLight.png");
		Gun1Sprite.setTexture(Gun1Texture);
		//Gun1Sprite.setTextureRect(sf::IntRect(sf::Vector2i(1700, 200), sf::Vector2i(200, 150)));
		Gun1Sprite.setPosition(1750, 200);
	}
	if (CurrentNum2KeyPressed && !PreviousNum2KeyPressed)
	{
		Gun1Texture.loadFromFile("Media/Textures/Knife.png");
		Gun1Sprite.setTexture(Gun1Texture);
		Gun1Sprite.setPosition(1750, 200);
	}
	if (CurrentNum3KeyPressed && !PreviousNum3KeyPressed)
	{
		Gun1Texture.loadFromFile("Media/Textures/slot1.png");
		Gun1Sprite.setTexture(Gun1Texture);
		Gun1Sprite.setPosition(1750, 200);
	}
	if (CurrentNum4KeyPressed && !PreviousNum4KeyPressed)
	{
		Gun1Texture.loadFromFile("Media/Textures/slot 2.png");
		Gun1Sprite.setTexture(Gun1Texture);
		Gun1Sprite.setPosition(1750, 200);
	}




}

void SFML_GameWorld::processEvents(float elapsedTime)
{
	// ------------------------------------------------- ROUGH WORK ------------------------------------------------------
	/*float cameraPanSpeed = 60.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_cameraPosition.x = m_cameraPosition.x - cameraPanSpeed * elapsedTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_cameraPosition.x = m_cameraPosition.x + cameraPanSpeed * elapsedTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_cameraPosition.y = m_cameraPosition.y - cameraPanSpeed * elapsedTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_cameraPosition.y = m_cameraPosition.y + cameraPanSpeed * elapsedTime;
	}*/
	// -----------------------------------------------------------------------------------------------------------------

	// Zoom in function for the game if you press + sign on the keyboard the game will zoom in and - to zoom out
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	{
		m_camera.zoomUp(elapsedTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		m_camera.zoomDown(elapsedTime);
	}

	// Get camera transform ( World -> screen)
	sf::Transform transform;
	transform = m_camera.getprojTransform() * m_camera.getViewTransform();

	// Take inverse (screen -> world)
	sf::Transform inv = transform.getInverse();

	// get mouse position ( in screen space)
	sf::Vector2f mouseScreenPosition = sf::Vector2f(sf::Mouse::getPosition(*m_parentWindow));

	// convert to world space coordinate
	sf::Vector2f mouseinworldpos = inv.transformPoint(mouseScreenPosition);

	sf::FloatRect rect;

	//rect = m_spriteObject.getGlobalBounds();

	//if (rect.contains(mouseinworldpos))
	//{
	//	m_spriteObject.setColor(sf::Color::Red);
	//}
	//else
	//	m_spriteObject.setColor(sf::Color::White);

	
	// Solution to additional challenges --------------------------------------------------
	
	
	
	bool leftButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	bool selected = false;

	for (unsigned int counter = 0; counter < m_staticObjectList.size(); counter++)
	{
		rect = m_staticObjectList[counter]->getGlobalBounds();

		if (rect.contains(mouseinworldpos))
		{
			// if mouse pointer insite the bounding rectangle, tint the sprite red
			m_staticObjectList[counter]->setColor(sf::Color::Red);

		/*	if (rect.intersects)
			{
				
			}*/

			if (!leftButtonPressed && m_prevLeftButtonPressed)
			{

				selected = true;
				m_selectedSpriteObjectID = counter;
			}
			else
			{
				// otherwise revert back to normal color (white)
				m_staticObjectList[counter]->setColor(sf::Color(255, 255, 255));
			}
		}
	}

	// ----------------------------------------------------------------------------------------

	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
	{
		if (m_zombieCharacterList[counter]->isInVision(mouseinworldpos))
		{
			// The mouse pointer is within npc's vision cone
			m_zombieCharacterList[counter]->setColor(sf::Color(128, 0, 0));
		}
		else 
		{
			// The mouse pointer is outside the npc's vision ccone
			m_zombieCharacterList[counter]->setColor(sf::Color(255, 255, 255));
		}
	}
	if (!selected && !leftButtonPressed && m_prevLeftButtonPressed)
		m_selectedSpriteObjectID = -1;

	m_prevLeftButtonPressed = leftButtonPressed;

	

	//m_spriteObject.update(elapsedTime);
	//m_animatedObject->update(elapsedTime);

	SFML_BulletSpriteObject* bullet = m_playerCharacter->processEvents(elapsedTime, transform, mouseScreenPosition);
	if (bullet)
	{
		m_bulletList.push_back(bullet);
	}
}

void SFML_GameWorld::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Render each game world layer
	// Render each game world with parallax factor >=1.0f
	for (unsigned int counter = 0; counter < m_GameWorldLayerList.size(); counter++)
	{
		if (m_GameWorldLayerList[counter]->getParallaxFactor() >= 1.0f)
		target.draw(*m_GameWorldLayerList[counter]);
	}
	
	// Get the camera view-projection tranform and set it to the renderstate
	sf::RenderStates renderState;
	renderState.transform = m_camera.getprojTransform() * m_camera.getViewTransform();

	// Draw the sprite object with the renderstate
	//target.draw(*m_animatedObject, renderState);

	// Draw each zombie object in the list
	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
	{
		if (m_zombieCharacterList[counter]->m_alive)
			target.draw(*m_zombieCharacterList[counter], renderState);
	}

	target.draw(*m_playerCharacter, renderState);

	// Draw each bullet object in the list
	for (unsigned int counter = 0; counter < m_bulletList.size(); counter++)
	{
		target.draw(*m_bulletList[counter], renderState);
	}

	// Draw each sprite object in the list 
	for (unsigned int counter = 0; counter < m_staticObjectList.size(); counter++)
	{
		target.draw(*m_staticObjectList[counter], renderState);
	}

	// Render each game world layer with parallax factor < 1.0
	for (unsigned int counter = 0; counter < m_GameWorldLayerList.size(); counter++)
	{
		if (m_GameWorldLayerList[counter]->getParallaxFactor() < 1.0f)
			target.draw(*m_GameWorldLayerList[counter]);
	}

	target.draw(playerhealth);
	target.draw(PlayerHealthText);
	target.draw(rect, sf::BlendMultiply);

	target.draw(Gun1Sprite);
	target.draw(TextSprite);
	target.draw(Text2Sprite);
		
	
}

bool SFML_GameWorld::layerSortFunction(SFML_GameWorldLayer * a, SFML_GameWorldLayer * b)
{
	return (a->getParallaxFactor() > b->getParallaxFactor());
}
