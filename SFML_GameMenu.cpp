#include "pch.h"
#include <SFML/Graphics.hpp>
#include "SFML_GameMenu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "SFML_GameMenu.h"

SFML_GameMenu::SFML_GameMenu(std::string menuFileName, int WindowWidth, int WindowHeight)
{
	//line 1 - background texture
	std::ifstream inputfile(menuFileName);
	if (inputfile.is_open())
	{
		std::string stringLine;
		std::getline(inputfile, stringLine);
		if (inputfile.good())
		{
			// Load the testure file and set it to the sprite
			m_BackgroundTexture.loadFromFile(stringLine);
			m_BackgroundSprite.setTexture(m_BackgroundTexture);

			// set the origin, texture rectangle, and position of the sprite
			sf::Vector2u textureSize = m_BackgroundTexture.getSize();
			m_BackgroundSprite.setOrigin(textureSize.x /2 , textureSize.y /2);
			m_BackgroundSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x , textureSize.y));
			//m_BackgroundSprite.setPosition(0, 0);
			// Note here that we set the origin to the texture centre but placed it
			// to the top left corner of the screen. We are going to use the sf::transformable
			// class property later on to shift this to the centre of the screen.

			// Set the rectangle texture which is cenred to 0,0
			m_BackgroundRect.left = -static_cast<float> (textureSize.x / 2);
			m_BackgroundRect.top = -static_cast<float> (textureSize.y / 2);
			m_BackgroundRect.width = textureSize.x ;
			m_BackgroundRect.height = textureSize.y;
			
		}

		//line 2 - game logo texture
		std::getline(inputfile, stringLine);
		if (inputfile.good())
		{
			// Load the testure file and set it to the sprite
			m_logo.loadFromFile(stringLine);
			m_logoSprite.setTexture(m_logo);


			// set the origin, texture rectangle, and position of the sprite
			sf::Vector2u textureSizeLogo = m_logo.getSize();
			m_logoSprite.setOrigin(textureSizeLogo.x / 2, textureSizeLogo.y / 2);
			m_logoSprite.setTextureRect(sf::IntRect(0, 0, textureSizeLogo.x, textureSizeLogo.y));
			m_logoSprite.setPosition(0, m_BackgroundTexture.getSize().y / 2 * 0.9f);
			// We set the position of the logo 90% down the screen height
		}

		//line 3 - font
		std::getline(inputfile, stringLine);
		if (inputfile.good())
		{
			m_gameFont.loadFromFile(stringLine);
		}

		//line 4 - normal text colour fill (R , G , B)
		std::getline(inputfile, stringLine);
		if (inputfile.good())
		{
			// Seperate them into three strings (assuming they are separated by a whitespace)
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			// Conver them to integers
			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			// Set the values to a m_normalTextColor
			m_normalTextColour = sf::Color(redInt, greenInt, blueInt);
		}

		//line 5 - normal text outline colour (R,G,B)
		std::getline(inputfile, stringLine);
		if (inputfile.good())
		{
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueString = std::stoi(blueString);

			m_normalOutlineColour = sf::Color(redInt, greenInt, blueInt);
			
		}

		//line 6 - highlight text fill colour ( R , G , B)
		std::getline(inputfile, stringLine);
		if (inputfile.good())
		{
			// Seperate them into three strings (assuming they are separated by a whitespace)
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			// Conver them to integers
			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueString = std::stoi(blueString);

			// Set the values to a m_HighlightTextColour
			m_HighlightTextColour = sf::Color(redInt, greenInt, blueInt);
		}

		//line 7 - highligh text outline colour (R, G ,B)
		std::getline(inputfile, stringLine);
		if (inputfile.good())
		{
			// Seperate them into three strings (assuming they are separated by a whitespace)
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			// Conver them to integers
			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueString = std::stoi(blueString);

			// Set the values to a m_highlightOutlineColour
			m_highlightOutlineColour = sf::Color(redInt, greenInt, blueInt);
		}

		//line 8 - border size in pixels
		std::getline(inputfile, stringLine);
		if (inputfile.good())
		{
			// Seperate them into two strings
			std::istringstream stringStream(stringLine);
			stringStream >> xBorderString;
			stringStream >> yBorderString;

			// Convert them to integers
			xBorderInt = std::stoi(xBorderString);
			yBorderInt = std::stoi(yBorderString);

			// Set the values to a m_menuItemBorder
			m_menuItemBorder.x = xBorderInt;
			m_menuItemBorder.y = yBorderInt;
		}
		
		//line 9 - Menu Text Position
		std::getline(inputfile, stringLine);
		if (inputfile.good())
		{
			m_menuAlignment = LEFT_JUSTIFIED;
			if (inputfile.good())
			{
				if (!std::strcmp(stringLine.c_str(), "LEFT_JUSTIFIED"))
					m_menuAlignment = LEFT_JUSTIFIED;
				else if (!std::strcmp(stringLine.c_str(), "CENTRE_JUSTIFIED"))
					m_menuAlignment = CENTRE_JUSTIFIED;
				else if (!std::strcmp(stringLine.c_str(), "RIGHT_JUSTIFIED"))
					m_menuAlignment = RIGHT_JUSTIFIED;

				if (m_menuAlignment == CENTRE_JUSTIFIED)
				{
					textPos.x = m_BackgroundRect.left + m_BackgroundRect.width / 2;
					textPos.y = m_BackgroundRect.top + m_menuItemBorder.y;
				}
				else if (m_menuAlignment == LEFT_JUSTIFIED)
				{
					textPos.x = m_BackgroundRect.left + m_menuItemBorder.x;
					textPos.y = m_BackgroundRect.top + m_menuItemBorder.y;
				}
				else if (m_menuAlignment == RIGHT_JUSTIFIED)
				{
					textPos.x = m_BackgroundRect.left + m_BackgroundRect.width - m_menuItemBorder.x;
					textPos.y = m_BackgroundRect.top + m_menuItemBorder.y;
				}
			}
			start.setFont(m_gameFont);
			start.setCharacterSize(60);
			start.setPosition(0, 5);
			start.setStyle(sf::Text::Bold);
			start.setFillColor(sf::Color::Red);
			start.setOutlineColor(m_normalOutlineColour);
			start.setOutlineThickness(2.0f);
		}

		//line 10
		do
		{
			// Read the every line for each menu item
			std::getline(inputfile, stringLine);
			if (inputfile.good())
			{
				// Set the Text's position to textpos
				start.setPosition(textPos.x, textPos.y);

				// Set the text's string to stringline (the oen we just read)
				start.setString(stringLine);

				// Set th Text's origin to Mid-left coordinate
				sf::FloatRect textbox = start.getLocalBounds();
				if (m_menuAlignment == CENTRE_JUSTIFIED)
				{
					start.setOrigin(textbox.width / 2, textbox.height / 2);
				}
				else if (m_menuAlignment == LEFT_JUSTIFIED)
				{
					start.setOrigin(0, textbox.height / 2);
				}
				else if (m_menuAlignment == RIGHT_JUSTIFIED)
				{
					start.setOrigin(textbox.width, textbox.height / 2);
				}

				// Store the Text to m_menuText array
				m_menuText.push_back(start);

				// Calculate the next text position by incrementing its y-position
				textPos.y += start.getLocalBounds().height * 2.2f;
			}
			else
				break;
		} while (true);
		m_highlightIndex = 0;
		m_menuText[m_highlightIndex].setFillColor(sf::Color::White);
		m_menuText[m_highlightIndex].setOutlineColor(m_normalOutlineColour);
		
		m_prevDownKeyPressed = true;
		m_prevUpKeyPressed = true;
		m_PrevReturnKeyPressed = true;		
	}
	inputfile.close();
}

SFML_GameMenu::~SFML_GameMenu()
{
	// Clear the menu item list
	m_menuText.clear();
}

int SFML_GameMenu::update(sf::Time elaspedTime)
{
	// This is for making the text on the menu screen rotate circular but it does not work properly
	for (int moveText = 0; m_highlightIndex < 4; moveText-- )
	{

		m_menuText[m_highlightIndex].rotate(0.003f);
		
		

			bool m_currentDownKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
			bool m_currentUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
			bool m_currentReturnKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);

			if (m_currentDownKeyPressed && !m_prevDownKeyPressed)
			{
				// set the colour of the CURRENT highlighed menu item to normal colour
				m_menuText[m_highlightIndex].setFillColor(sf::Color::Red);
				m_menuText[m_highlightIndex].setOutlineColor(m_normalOutlineColour);

				// Increment the highlighted index by one, modulated by the number of menu items
				m_highlightIndex++;
				m_highlightIndex = m_highlightIndex % m_menuText.size();

				// Set the colour of the NEW highlighted menu item to highlight colour
				m_menuText[m_highlightIndex].setFillColor(sf::Color::White);
				m_menuText[m_highlightIndex].setOutlineColor(m_highlightOutlineColour);
			}
			else if (m_currentUpKeyPressed && !m_prevUpKeyPressed)
			{
				// set the colour of the CURRENT highlighed menu item to normal colour
				m_menuText[m_highlightIndex].setFillColor(sf::Color::Red);
				m_menuText[m_highlightIndex].setOutlineColor(m_normalOutlineColour);

				// Increment the highlighted index by one, modulated by the number of menu items
				// The number of menu item to it
				m_highlightIndex--;
				if (m_highlightIndex < 0)
					m_highlightIndex = m_highlightIndex + m_menuText.size();

				// Set the colour of the NEW highlighted menu item to highlight colour
				m_menuText[m_highlightIndex].setFillColor(sf::Color::White);
				m_menuText[m_highlightIndex].setOutlineColor(m_highlightOutlineColour);
			}

			m_prevDownKeyPressed = m_currentDownKeyPressed;
			m_prevUpKeyPressed = m_currentUpKeyPressed;

			bool hasSelected = false;

			if (m_currentReturnKeyPressed && !m_PrevReturnKeyPressed)
				hasSelected = true;

			m_PrevReturnKeyPressed = m_currentReturnKeyPressed;

			if (hasSelected)
				return m_highlightIndex;
			else
				return -1;
		
	}
}


void SFML_GameMenu::move(float offsetX,float offsetY)
{
}

void SFML_GameMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_BackgroundSprite, states);
	target.draw(m_logoSprite, states);

	for (std::size_t count = 0; count < m_menuText.size(); count++)
		target.draw(m_menuText[count], states);
}


