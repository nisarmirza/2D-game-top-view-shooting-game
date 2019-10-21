#include "pch.h"
#include "SFML_APPLICATION.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "SFML_GameMenu.h"
#include "SFML_TitleScreen.h"


SFML_APPLICATION::SFML_APPLICATION(int WindowWidth, int WindowHeight)

	:m_window(sf::VideoMode(WindowWidth, WindowHeight), " CourseWork ", sf::Style::Fullscreen, settings)
	, m_initialised(true)
	, m_screenWidth(WindowWidth)
	, m_screenHeight(WindowHeight)
	, m_AppState(TITLESCREEN)
	, m_PreviousDownKeyPressed(false)
	, m_PreviousUpKeyPressed(false)
	, m_PreviousEscapeKeyPressed(false)
	, m_titleScreen("Media/Textures/title-screen.png", WindowWidth, WindowHeight)
	, m_MainMenu("Media/Menuinfo/main-menu.txt", WindowWidth, WindowHeight)
	, m_creditText("Media/Menuinfo/credit.txt", WindowWidth, WindowHeight)
	, m_ControlText("Media/Menuinfo/Controls.txt", WindowWidth, WindowHeight)
	//, m_StoryText("Media/Menuinfo/BackgroundStory.txt", WindowWidth, WindowHeight)
	//, m_camera(WindowWidth, WindowHeight) REMOVED not using
	, m_gameWorld(WindowWidth, WindowHeight, &m_window)
	// FPS COUNTER
	, m_desiredUpdateTime(sf::seconds(1.f / 60.f))
	, m_timeCounter(sf::seconds(0))
	, m_FPSCounter(0)
	, SoonBefore(true)

{
	settings.antialiasingLevel = 8;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	m_initialised = m_textFont.loadFromFile("Media/Fonts/youmurdererbb_reg.otf");
	m_messageText.setFont(m_textFont);
	m_MainMenu.setScale(0.85f, 0.85f);
	m_MainMenu.setPosition(m_screenWidth / 2, m_screenHeight / 2);
	m_creditText.setScale(0.85f, 0.85f);
	m_creditText.setPosition(m_screenWidth / 2, m_screenHeight / 2);
	m_ControlText.setScale(0.85f, 0.85f);
	m_ControlText.setPosition(m_screenWidth / 2, m_screenHeight / 2);

	//BACKGROUND TEXT IMPLEMENTATION
	//------------------------------------------------------------------------------------------

	StoryTextAlphabettically.setFont(m_textFont);
	StoryTextAlphabettically.setCharacterSize(30);
	StoryTextAlphabettically.setPosition(0, 0);

	m_backgroundStoryTexture.loadFromFile("Media/Textures/667302.jpg");
	

	m_backgroundStorySprite.setTexture(m_backgroundStoryTexture);
	m_backgroundStorySprite.setPosition(0, 0);

	m_backgroundStorySprite.setColor(sf::Color::White);

	TextForBackgroundStory = "So it all started by a scientist, a guy named exorcist, \nnwho is working in a company called Trey-Yark, exorcist is known for his extreme experiments in the labs, daily hoping for his idea to succeed,\n also, he created something which caused mayhem everywhere throughout the world.\nIt was a mistake which turned out to be his invention and it was a portal which he invented while trying to make time machine,\nwhich could unlock different dimension in the world. He was so eager to test it,\n for testing the portals they needed someone who knows how to deal with situations which are out of control.\n A military commander was appointed for experiments who could visit the dimensions and check what is on other dimensions.\n Several dimensions were visited by the commander.But all of those were safe except one.\nHowever, there was one portal which exorcist was studying about and did not want to experiment because,\nit was the opposite of the planet normal human being live in.Where everything is opposite and people over there are known as zombies.\nHe warned the military to not go there.But they were so eager to know that what lies behind that opposite world,\nthey got curios and made an forceful attempt to go there. Exorcist warned them about the portal damaging. \nIf the portal gets damaged there is no way of closing it and those zombies eat humans.\nMilitary refused to listen to exorcist and they made him open the portal.Eventually, exorcist was right.\nThe power got overpowered which pushed the bounds of that portal and the power of the whole city was doomed,\nwhich make the portal do infinite loops(which will never close).\nThe portal over charged and started opening at various places in the planet earth,\nby which zombies could enter the planet earth.To stop this, the general gave a command for a war,\ntanks were called in, all military were on high alert.Moreover, the zombies came in the lab itself.\nThe general gave order to exorcist to work on portal to fix it, till then we will handle the zombies.\nHowever, exorcist got bitten by the zombie and it was chaos all over the world.\nNonetheless exorcist still had 24 hours before he was fully transformed into a zombie.\nHe tried to fix the portal.But to fix it, electricity was required due to the portal defect.\nAll the electricity in the city was washed out.The only way of gaining back electricity was to go electric station which was located out of city\nand get a charge and put it in to the machine to make it work again.So, military was sent to grab that charge.On their way,\nthe whole city was filled with zombies, they had to fight their way to grab the charge.\nBy the time a group military was sent for charge, another military group was assigned to go in portal and get some information about that portal.\nThe military after several hours came back with the charge.\nThe exorcist worked out to make the portal close but sacrificing the soldiers which were already in the portal,\nbut the soldiers which were in the portal were locked and had no chance of coming back.\nThe soldiers fought bravely against the zombies and they killed hundreds of them.One of soldiers is still alive and he is still fighting…….";

	//Gun1Texture.loadFromFile("Media/Textures/slot1.png");
	//Gun1Sprite.setTexture(Gun1Texture);
	//Gun1Sprite.setPosition(0, 0);


	//-----------------------------------------------------------------------------------------------


	// ------------------------------------------------- ROUGH WORK -------------------------------------------------------------
	// Create a gameworld layer object using a wall.png texture
	/*SFML_GameWorldLayer* background = new SFML_GameWorldLayer("Media/Textures/wall.png", 1.0f,  WindowWidth, WindowHeight);
	
	// Insert it to push the array
	m_GameWorldLayerList.push_back(background);

	// Set the camera's intial position (0,0)
	m_cameraPosition = sf::Vector2f(0, 0);

	SFML_GameWorldLayer* foreGround = new SFML_GameWorldLayer("Media/Textures/wire.png", 0.3f, WindowWidth, WindowHeight);
	m_GameWorldLayerList.push_back(foreGround);*/ // REMOVED
	// ---------------------------------------------------------------------------------------------------------------------------
}

SFML_APPLICATION::~SFML_APPLICATION()
{
	// Clear the gameworldLayer list ------------------------------------------------------
	/*for (std::vector<SFML_GameWorldLayer*>::iterator it = m_GameWorldLayerList.begin();
		it != m_GameWorldLayerList.end();
		it++)
	{
		delete (*it);
	}
	m_GameWorldLayerList.clear();*/ // REMOVED

}

void SFML_APPLICATION::run()
{
	// ------------------------------------------- ROUGH WORK -------------------------------------------
	/*if (!m_initialised)
		return;

	sf::Clock clock;
	while (m_window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > m_desiredUpdateTime)
		{
			update(m_desiredUpdateTime);
		}
		updateFPS(elapsedTime);
		
		m_window.pollEvent(m_event);
		if (m_event.type == sf::Event::Closed)
			m_window.close();
		update(elapsedTime);
		render();
	}*/ // REMOVED
	// ----------------------------------------------------------------------------------------------------


	if (!m_initialised)
		return;
	sf::Clock clock;

	while (m_window.isOpen())
	{
		// Get the elapsed time since the last loop
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > m_desiredUpdateTime)
		{
			// Update application states
			update(m_desiredUpdateTime);

			// Subtract m_desiredUpdateTime from timeSinceLastUpdate
			timeSinceLastUpdate -= m_desiredUpdateTime;
		}

		// Claculate FPS
		updateFPS(elapsedTime);
		// --------------------------------------------
		/*m_window.pollEvent(m_event);
		if (m_event.type == sf::Event::Closed)
			m_window.close();*/
		//----------------------------------------------
		update(elapsedTime);

		// Render reslt to the screen
		render();
	}
	
}

void SFML_APPLICATION::updateFPS(sf::Time elaspedTime)
{
	// Increment the time counter by the time since the last update
	m_timeCounter += elaspedTime;

	// Increment FPS counter by one
	m_FPSCounter += 1;

	// If onse second has passed
	if (m_timeCounter >= sf::seconds(1.0f))
	{
		// Set the message text
		m_messageText.setString(
			"Refresh rate = " + std::to_string(m_FPSCounter) + "fps \n" + "Time between screen refreshes =" + std::to_string(m_timeCounter.asMicroseconds() / m_FPSCounter) + "microseconds \n");
		
		// Take away one second from the time counter
		m_timeCounter -= sf::seconds(1.0f);

		// Reset the FPS counter
		m_FPSCounter = 0;

	}
}


void SFML_APPLICATION::update(sf::Time elaspedTime)
{
	// Check if the player has tries to close the window, if so close the applicaiotn 
	// This event triggers when 1) The x window is pressed or 2) Alt-F4 keys are pressed
	bool validEventPoll = m_window.pollEvent(m_event);

	if ((m_event.type == sf::Event::Closed) && validEventPoll)
		m_window.close();

	int selection;

	m_titleScreen.update(elaspedTime);
	m_messageText.setPosition(m_screenWidth / 6, m_screenHeight / 10);
	m_messageText.setCharacterSize(20);
	sf::FloatRect textbox = m_messageText.getLocalBounds();
	m_messageText.setOrigin(textbox.width / 2, textbox.height / 2);

	bool CurrentDownKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool CurrentUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool CurrentEscapeKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
	
	switch (m_AppState)
	{
	case TITLESCREEN:
		
		if ((m_event.type == sf::Event::KeyPressed))
		{
			m_AppState = MAINMENU;
		}
		//m_messageText.setString(" LAST MERCENARY ");
		break;

	case MAINMENU:
		selection = m_MainMenu.update(elaspedTime);
		if (selection >= 0)
		{
			if (selection == 0)
			{
				//m_AppState = BACKGROUNDSTORY;
				m_AppState = GAMEPLAYING;
			}
			else if (selection == 1)
				m_AppState = CONTROLS;
			else if (selection == 2)
				m_AppState = CREDITS;
			else if (selection == 3)
				m_AppState = EXITING;
		}
		break;

	case CONTROLS:
		
		if (CurrentEscapeKeyPressed & !m_PreviousEscapeKeyPressed)
		{
			m_AppState = MAINMENU;
		}
		//m_messageText.setString(" Options");
		m_ControlText.update(elaspedTime);
		break;

	case CREDITS:

		if (CurrentEscapeKeyPressed & !m_PreviousEscapeKeyPressed)
		{
			m_AppState = MAINMENU;
		}
		m_creditText.update(elaspedTime);
		//m_StoryText.update(elaspedTime);
		

	case GAMEPLAYING:
		// --------------------------------------------------- ROUGH WORK -----------------------------------------------------------
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_cameraPosition.x = m_cameraPosition.x - 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_cameraPosition.x = m_cameraPosition.x + 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_cameraPosition.y = m_cameraPosition.y - 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_cameraPosition.y = m_cameraPosition.y + 1;
		}*/

	/*{
		float cameraPanSpeed = 60.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_cameraPosition.x = m_cameraPosition.x - cameraPanSpeed * elaspedTime.asSeconds();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_cameraPosition.x = m_cameraPosition.x + cameraPanSpeed * elaspedTime.asSeconds();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_cameraPosition.y = m_cameraPosition.y - cameraPanSpeed * elaspedTime.asSeconds();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_cameraPosition.y = m_cameraPosition.y + cameraPanSpeed * elaspedTime.asSeconds();
		}
	}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			m_camera.zoomUp(elaspedTime.asSeconds());
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		{
			m_camera.zoomDown(elaspedTime.asSeconds());
		}*/


		//m_camera.setPosition(m_cameraPosition);
		///*m_GameWorldLayerList[0]->followCamera(&m_camera);*/
		//for (std::size_t counter = 0; counter < m_GameWorldLayerList.size(); counter++)
		//{
		//	m_GameWorldLayerList[counter]->followCamera(&m_camera);

		//}
		 
		//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		
		if (CurrentEscapeKeyPressed & !m_PreviousEscapeKeyPressed)
		{
			m_AppState = MAINMENU; 
		}
		

		StoryTextAlphabettically.setPosition(200, 150);

		Timeupdate += clockupdate.restart();

		if (Timeupdate >= sf::seconds(.6f))
		{
			Timeupdate -= sf::seconds(.02f);
			if (TextForBackgroundStory.getSize() > 0)
			{
				StoryTextAlphabettically.setString(StoryTextAlphabettically.getString()+ TextForBackgroundStory[0]);
				TextForBackgroundStory = TextForBackgroundStory.toAnsiString().substr(1);
			}
		}

		SettingTimeUP = static_cast<unsigned int>(ClockElapsed.getElapsedTime().asSeconds());
		ClockElapsed.getElapsedTime();


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			SoonBefore = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			SoonBefore = false;
		}

		TimeGone += ClockGone.restart();
		TimeIsGone = static_cast<unsigned int>(TimeGone.asSeconds());

		if ((TimeIsGone > 10) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (SettingTimeUP >= 10)))
		{
			m_gameWorld.update(elaspedTime.asSeconds());
		}
		else if ((SoonBefore == false) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
		{
			m_gameWorld.update(elaspedTime.asSeconds());
		}


		/*if (CurrentNum4KeyPressed && !PreviousNum4KeyPressed)
		{
			Gun1Sprite.setPosition(0, 0);
		}
*/
		
		//m_gameWorld.update(elaspedTime.asSeconds());
		//m_StoryText.update(elaspedTime);
		break;

	case BACKGROUNDSTORY:
		if (CurrentEscapeKeyPressed & !m_PreviousEscapeKeyPressed)
		{
			m_AppState = MAINMENU;
		}
		//m_StoryText.update(elaspedTime);
		break;
	case EXITING:

		m_window.close();
		break;
	}
	m_PreviousDownKeyPressed = CurrentDownKeyPressed;
	m_PreviousEscapeKeyPressed = CurrentEscapeKeyPressed;
	m_PreviousUpKeyPressed = CurrentUpKeyPressed;
}

void SFML_APPLICATION::render()
{
	m_window.clear();
	switch (m_AppState)
	{
	case TITLESCREEN:
		m_window.draw(m_titleScreen);
		break;
	case MAINMENU:
		m_window.draw(m_MainMenu);
		m_window.draw(m_messageText);
		break;
	case CONTROLS:
		m_window.draw(m_ControlText);
		break;

	case CREDITS:
		m_window.draw(m_creditText);
		//m_window.draw(m_StoryText);
		break;

	case GAMEPLAYING:
		// Render the first layer
	/*	m_window.draw(*m_GameWorldLayerList[0]);*/
		/*for (std::size_t counter = 0; counter < m_GameWorldLayerList.size(); counter++)
		{
			m_window.draw(*m_GameWorldLayerList[counter]);

		}*/
		
		m_window.draw(m_gameWorld);
		//m_window.draw(m_StoryText);
		m_window.draw(m_messageText);
	/*	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			Gun1Sprite.setPosition(10, 20);
			
		}
		else
		{
			m_window.draw(Gun1Sprite);
		}
*/
		SettingTimeUP = static_cast<unsigned int>(ClockElapsed.getElapsedTime().asSeconds());
		ClockElapsed.getElapsedTime();

		if ((SettingTimeUP < 10) && (SoonBefore == true))
		{
			
			m_window.draw(m_backgroundStorySprite);
			m_window.draw(StoryTextAlphabettically);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			
			m_window.draw(m_backgroundStorySprite);
			m_window.draw(StoryTextAlphabettically);
		}

	
		
		
		
		break;
	case BACKGROUNDSTORY:
		//m_window.draw(m_StoryText);
		break;
	case EXITING:
		break;
	}
	m_window.display();
}

