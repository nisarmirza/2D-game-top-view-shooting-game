#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "SFML_CreditScreen.h"
#include "SFML_GameMenu.h"




SFML_CreditScreen::SFML_CreditScreen(std::string TextureFileName, int WindowWidth, int WindowHeight)
{
	m_CreditScreenTexture.loadFromFile(TextureFileName);
	m_CreditScreenSprite.setTexture(m_CreditScreenTexture);
	sf::Vector2u bkTextureSize = m_CreditScreenTexture.getSize();
	m_CreditScreenSprite.setTextureRect(sf::IntRect(0,0, bkTextureSize.x, bkTextureSize.y));
	m_CreditScreenSprite.setPosition(0, 0);
	m_messageTexture.loadFromFile("Media/Menuinfo/credit.txt");
	m_messageSprite.setTexture(m_messageTexture);
	m_messageSprite.setPosition(WindowWidth * 0.5f, WindowHeight * 0.9f);
	sf::Vector2u msgTextureSize = m_messageTexture.getSize();
	m_messageSprite.setOrigin(msgTextureSize.x / 2, msgTextureSize.y / 2);
	m_messageSprite.setTextureRect(sf::IntRect(0, 0, msgTextureSize.x, msgTextureSize.y));
	m_messageSprite.setColor(sf::Color(255, 0, 0));


	//line 1 - background texture
	std::ifstream inputfile(TextureFileName);
	if (inputfile.is_open())
	{
		std::string stringLine;
		std::getline(inputfile, stringLine);

		if (inputfile.good())
		{
			// Load the testure file and set it to the sprite
			m_CreditScreenTexture.loadFromFile(stringLine);
			m_CreditScreenSprite.setTexture(m_CreditScreenTexture);

			// set the origin, texture rectangle, and position of the sprite
			sf::Vector2u textureSize = m_CreditScreenTexture.getSize();
			m_CreditScreenSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_CreditScreenSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x  , textureSize.y ));
			m_CreditScreenSprite.setPosition(0, 0);
			// Note here that we set the origin to the texture centre but placed it
			// to the top left corner of the screen. We are going to use the sf::transformable
			// class property later on to shift this to the centre of the screen.

			// Set the rectangle texture which is cenred to 0,0
			m_BackgroundRect.left = -static_cast<float> (textureSize.x /2);
			m_BackgroundRect.top = -static_cast<float> (textureSize.y /2);
			m_BackgroundRect.width = textureSize.x;
			m_BackgroundRect.height = textureSize.y * 2;

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
			m_logoSprite.setOrigin(textureSizeLogo.x / 2, textureSizeLogo.y * 2);
			m_logoSprite.setTextureRect(sf::IntRect(0, 0, textureSizeLogo.x, textureSizeLogo.y));
			m_logoSprite.setPosition(0, m_CreditScreenTexture.getSize().y / 2 * 0.9f);
			// We set the position of the logo 90% down the screen height 
		}

		// line 3 - font 
		std::getline(inputfile, stringLine);
		if (inputfile.good())
		{
			m_CreditFont.loadFromFile(stringLine);
		}

		// line 4 - text position
		std::getline(inputfile, stringLine);
		if (inputfile.good())
		{
			m_CreditAlignment = CENTRE_JUSTIFIED;
			if (inputfile.good())
			{
				if (!std::strcmp(stringLine.c_str(), "LEFT_JUSTIFIED"))
					m_CreditAlignment = LEFT_JUSTIFIED;
				else if (!std::strcmp(stringLine.c_str(), "CENTRE_JUSTIFIED"))
					m_CreditAlignment = CENTRE_JUSTIFIED;
				else if (!std::strcmp(stringLine.c_str(), "RIGHT_JUSTIFIED"))
					m_CreditAlignment = RIGHT_JUSTIFIED;
				
				if (m_CreditAlignment == CENTRE_JUSTIFIED)
				{
					textPos.x = m_BackgroundRect.left  + m_BackgroundRect.width /2;
					textPos.y = m_BackgroundRect.top / 18 + m_CreditBorder.y * 2 ;
				}
				else if (m_CreditAlignment == LEFT_JUSTIFIED)
				{
					textPos.x = m_BackgroundRect.left + m_CreditBorder.x ;
					textPos.y = m_BackgroundRect.top + m_CreditBorder.y;
				}
				else if (m_CreditAlignment == RIGHT_JUSTIFIED)
				{
					textPos.x = m_BackgroundRect.left + m_BackgroundRect.width - m_CreditBorder.x;
					textPos.y = m_BackgroundRect.top + m_CreditBorder.y;
				}
			}
			start.setFont(m_CreditFont);
			start.setCharacterSize(40);
			start.setPosition(0, 5);
			start.setStyle(sf::Text::Bold);
			start.setFillColor(sf::Color::White);
			start.setOutlineColor(sf::Color::Black);
			start.setOutlineThickness(1.0f);
		}

		// line 5- reading text from credit.txt
			do
			{
				// Read the every line 
				std::getline(inputfile, stringLine);
				if (inputfile.good())
				{				
					// Set the Text's position to textpos
					start.setPosition(textPos.x, textPos.y);

					// Set the text's string to stringline (the oen we just read)
					start.setString(stringLine);

					// Set th Text's origin to Mid-left coordinate
					sf::FloatRect textbox = start.getLocalBounds();
					if (m_CreditAlignment == CENTRE_JUSTIFIED)
					{
						start.setOrigin(textbox.width / 2, textbox.height / 2);
					}
					else if (m_CreditAlignment == LEFT_JUSTIFIED)
					{
						start.setOrigin(0, textbox.height / 2);
					}
					else if (m_CreditAlignment == RIGHT_JUSTIFIED)
					{
						start.setOrigin(textbox.width, textbox.height / 2);
					}

					// Store the Text to m_menuText array
					m_CreditText.push_back(start);

					// Calculate the next text position by incrementing its y-position
					textPos.y += start.getLocalBounds().height * 2.2f;
				}
				else
					break;
			} while (true);
	}
	inputfile.close();
}

SFML_CreditScreen::~SFML_CreditScreen()
{
}

void SFML_CreditScreen::update(sf::Time elaspedTime)
{
	m_messageSprite.setColor(sf::Color(255, 255, 255));
	for (std::size_t counter = 0; counter < m_CreditText.size(); counter++)
	{
		//int textPos;
		// Speed for the ext on the credit screen
		float scrollSpeed1 = 0.050f;

		// The position for the text
		sf::Vector2f pos = m_CreditText[counter].getPosition();
		// Moving the text upwards
		pos.y = pos.y - scrollSpeed1;
		start.setPosition(pos);
		m_CreditText[counter].setPosition(pos);
	}
	// Setting the position for the logo on the credit screen and making it move upwards with the text it self
	float scrollSpeed2 = 0.050f ;
	sf::Vector2f Logo = m_logoSprite.getPosition();
	Logo.y = Logo.y - scrollSpeed2;
	m_logoSprite.setPosition(Logo);
}

void SFML_CreditScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_CreditScreenSprite, states);
	target.draw(m_logoSprite, states);

	for (std::size_t count = 0; count < m_CreditText.size(); count++)
	{
		target.draw(m_CreditText[count], states);
	}
}
