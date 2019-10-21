#pragma once
#ifndef SFML_APPLICATION_H
#define SFML_APPLICATION_H


#include <SFML/Graphics.hpp>
#include "SFML_TitleScreen.h"
#include "SFML_CreditScreen.h"
#include "SFML_GameMenu.h"
#include "SFML_GameWorldLayer.h"
#include "SFML_GameWorld.h"
#include "BackgroundStory.h"
#include "SFML_Controls.h"


using namespace std;
// TODO: add headers that you want to pre-compile here

enum AppState {
	TITLESCREEN,
	MAINMENU,
	GAMEPLAYING,
	EXITING,
	CONTROLS,
	CREDITS,
	BACKGROUNDSTORY
	
	

};


class SFML_APPLICATION :
	public sf::NonCopyable
{
public:
	SFML_APPLICATION(int WindowWidth, int WindowHeight);
	~SFML_APPLICATION();
	void run();


private:
	
	void update(sf::Time elaspedTime);
	void render();

	bool m_initialised;

	sf::RenderWindow m_window;

	std::size_t m_screenWidth;
	std::size_t m_screenHeight;

	sf::Event m_event;

	sf::Font m_textFont;

	sf::Text m_messageText;

	AppState m_AppState;

	sf::Sprite entity;

	bool m_PreviousDownKeyPressed;
	bool m_PreviousUpKeyPressed;
	bool m_PreviousEscapeKeyPressed;
	

	SFML_TitleScreen m_titleScreen;

	SFML_GameMenu m_MainMenu;

	SFML_CreditScreen m_creditText;

	SFML_Controls m_ControlText;

	//BackgroundStory m_StoryText;

	// The array to store the game world layers
	/*std::vector<SFML_GameWorldLayer*> m_GameWorldLayerList;

	// The member attribute to store the camera object
	SFML_2DCamera m_camera;

	// The member attribute to store the camera position
	sf::Vector2f m_cameraPosition;*/ // REMOVED

	// Game world object that contains m_gameWorld LAyerList and m_camera
	SFML_GameWorld m_gameWorld;

	// Member attributes for FPS data
	sf::Time m_timeCounter;
	sf::Time m_desiredUpdateTime;
	std::size_t m_FPSCounter;

	// Function to update FPS data
	void updateFPS(sf::Time elaspedTime);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	int m_MainMenuCounter;


	bool SoonBefore;
	sf::Text StoryTextAlphabettically;

	sf::Sprite m_backgroundStorySprite;
	sf::Texture m_backgroundStoryTexture;

	sf::String TextForBackgroundStory;

	sf::Clock clockupdate; // (10)
	sf::Time Timeupdate; // (10)

	sf::Clock ClockElapsed; // (4)
	sf::Time TimeElapsed; // (4)

	sf::Clock ClockGone; // (3)
	sf::Time TimeGone; // (3)

	int SettingTimeUP;
	int TimeIsGone;

	sf::ContextSettings settings;
	

	// Guns sprite for HUD
	sf::Sprite Gun1Sprite;
	sf::Texture Gun1Texture;

};


#endif // SFML_APPLICATION_H

