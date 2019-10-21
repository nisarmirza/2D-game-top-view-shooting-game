#include "pch.h"
//#include <iostream>
//#include <fstream>
//#include <cstring>
//#include <sstream>
//#include <string>
//#include "BackgroundStory.h"
//#include "SFML_GameMenu.h"
//
//
//
//BackgroundStory::BackgroundStory(std::string TextureFileName, int WindowWidth, int WindowHeight)
//{
//	// Lines and character position for the background text which appears line by line and character by character
//	lines = 0;
//	charpos = 0;
//
//
//	// reading the text file
//	std::ifstream inputfile(TextureFileName);
//	if (inputfile.is_open())
//	{
//		std::string stringLine;
//		std::getline(inputfile, stringLine);
//				
//		// line 1 - setting texture of background
//		if (inputfile.good())
//		{
//			// Load the testure file and set it to the sprite
//			m_BackgroundStoryTexture.loadFromFile(stringLine);
//			m_BackgroundStorySprite.setTexture(m_BackgroundStoryTexture);
//
//			// set the origin, texture rectangle, and position of the sprite
//			sf::Vector2u textureSize = m_BackgroundStoryTexture.getSize();
//			m_BackgroundStorySprite.setOrigin(textureSize.x/2, textureSize.y/2);
//			m_BackgroundStorySprite.setTextureRect(sf::IntRect(0, 0, textureSize.x/ 2, textureSize.y / 2));
//			m_BackgroundStorySprite.setPosition(0, 0);
//			// Note here that we set the origin to the texture centre but placed it
//			// to the top left corner of the screen. We are going to use the sf::transformable
//			// class property later on to shift this to the centre of the screen.
//
//			// Set the rectangle texture which is cenred to 0,0
//			m_BackgroundRect.left = -static_cast<float> (textureSize.x / 2);
//			m_BackgroundRect.top = -static_cast<float> (textureSize.y / 2);
//			m_BackgroundRect.width = textureSize.x;
//			m_BackgroundRect.height = textureSize.y * 2 ;
//
//		}
//
//
//		//line 2 - Setting the font to appear on the screen
//		std::getline(inputfile, stringLine);
//		if (inputfile.good())
//		{
//			m_StoryFont.loadFromFile(stringLine);
//		}
//
//
//		//line 3 -  Text Position
//		std::getline(inputfile, stringLine);
//		if (inputfile.good())
//		{
//			m_StoryAlignment = CENTRE_JUSTIFIED;
//			if (inputfile.good())
//			{
//				if (!std::strcmp(stringLine.c_str(), "LEFT_JUSTIFIED"))
//					m_StoryAlignment = LEFT_JUSTIFIED;
//				else if (!std::strcmp(stringLine.c_str(), "CENTRE_JUSTIFIED"))
//					m_StoryAlignment = CENTRE_JUSTIFIED;
//				else if (!std::strcmp(stringLine.c_str(), "RIGHT_JUSTIFIED"))
//					m_StoryAlignment = RIGHT_JUSTIFIED;
//
//				if (m_StoryAlignment == CENTRE_JUSTIFIED)
//				{
//					textPos.x = m_BackgroundRect.left / 4 + m_BackgroundRect.width / 2;
//					textPos.y = m_BackgroundRect.top / 18 + m_CreditBorder.y * 2;
//				}
//				else if (m_StoryAlignment == LEFT_JUSTIFIED)
//				{
//					textPos.x = m_BackgroundRect.left + m_CreditBorder.x;
//					textPos.y = m_BackgroundRect.top + m_CreditBorder.y;
//				}
//				else if (m_StoryAlignment == RIGHT_JUSTIFIED)
//				{
//					textPos.x = m_BackgroundRect.left + m_BackgroundRect.width - m_CreditBorder.x;
//					textPos.y = m_BackgroundRect.top + m_CreditBorder.y;
//				}
//			}
//			// Setting how the font should look like, font size, style, thickness etc.
//			start.setFont(m_StoryFont);
//			start.setCharacterSize(30);
//			start.setPosition(0, 5);
//			start.setStyle(sf::Text::Bold);
//			start.setFillColor(sf::Color::White);
//			start.setOutlineColor(sf::Color::Black);
//			start.setOutlineThickness(1.0f);
//		}
//
//		// Line 4 - Reading the text from the document BackgroundStory.txt
//		do
//		{
//			std::getline(inputfile, stringLine);
//			if (inputfile.good())
//			{
//				start.setPosition(textPos.x, textPos.y);
//				start.setString(stringLine);
//				sf::FloatRect textbox = start.getLocalBounds();
//
//				if (m_StoryAlignment == CENTRE_JUSTIFIED)
//				{
//					start.setOrigin(textbox.width / 2, textbox.height / 2);
//				}
//				else if (m_StoryAlignment == LEFT_JUSTIFIED)
//				{
//					start.setOrigin(0, textbox.height / 2);
//				}
//				else if (m_StoryAlignment == RIGHT_JUSTIFIED)
//				{
//					start.setOrigin(textbox.width, textbox.height / 2);
//				}
//				m_StoryText.push_back(start);
//				textPos.y += start.getLocalBounds().height * 2.2f;
//			}
//			else
//				break;
//		} while (true);
//	}
//	inputfile.close();
//}
//
//
//BackgroundStory::~BackgroundStory()
//{
//}
//
//void BackgroundStory::update(sf::Time elaspedTime)
//{
//	// Function for getting the size of the text and reading it line by line
//	if (lines < m_StoryText.size())
//	{
//		std::string str = m_StoryText[lines].getString();
//		int len = str.length();
//
//		if (charpos < len - 1)
//			charpos++;
//		else if (lines < m_StoryText.size()-1)
//		{
//			charpos = 0;
//			lines++;
//		}
//	}
//	m_visibleStoryText.clear();
//
//	// reading all the line one by one
//	for (int i = 0; i < lines; i++)
//	{
//		/*std::string str = m_StoryText[lines].getString();
//		sf::Text txt = m_StoryText[i];
//		txt.setString("a");
//		for (int j = 0; j < 10; j++)
//		{
//			m_visibleStoryText.push_back(txt);
//		}*/
//		m_visibleStoryText.push_back(m_StoryText[i]);
//	}
//	
//	// function for setting to display background story text one by one
//	std::string str = m_StoryText[lines].getString();
//	int len = str.length();
//	elaspedTime += clock.restart();
//	//if (elaspedTime >= sf::seconds(.1f))
//	{
//		//elaspedTime -= sf::seconds(.02f);
//		sf::Text txt = m_StoryText[lines];
//		if (charpos > 0)
//		{
//			
//			str = str.substr(1, charpos);
//		}
//		else
//		{
//			str = "";
//		}
//
//
//
//		txt.setString(str);
//		m_visibleStoryText.push_back(txt);
//
//	}
//
//	
//	
//	int seconds = static_cast<unsigned int>(Time.asSeconds());
//
//	if ((seconds > 10) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (seconds >= 10)))
//	{
//		//m_gameWorld.update(elaspedTime.asSeconds());
//	}
//
//	//-------------------------------------- ROUGH WORK ----------------------------------------------
//	
//	//std::string str1 = m_StoryText[charpos].getString();
//	//int lenght;
//	//m_messageSprite.setColor(sf::Color(255, 255, 255));
//	//for (size_t Counter = 0; Counter < m_StoryText.size(); Counter++)
//	//{
//	//	
//	//	std::string str = m_StoryText[Counter].getString();
//	//	if (Counter > str.length())
//	//	{
//	//		char * cstr = new char[str.length() + 1];
//	//		new char[str.length++];
//	//	}
//	//	std::string str = m_StoryText[Counter].getString();
//	//	char * cstr = new char[str.length() + 1];
//	//	std::strcpy(cstr, str.c_str());
//	// cstr now contains a c-string copy of str
//
//	// -------------------------------------------------------------------------------------------------
//}
//
//void BackgroundStory::draw(sf::RenderTarget & target, sf::RenderStates states) const
//{
//	states.transform *= getTransform();
//	target.draw(m_BackgroundStorySprite, states);
//	for (std::size_t count = 0; count < m_visibleStoryText.size(); count++)
//	{
//		// ----------------------------- ROUGH WORK ------------------------
//		//std::string str = m_StoryText[count].getString();
//		//char * cstr = new char[str.length() + 1];
//		//std::strcpy(cstr, str.c_str());
//		// -----------------------------------------------------------------
//		target.draw(m_visibleStoryText[count], states);
//	}
//	
//
//	
//}
