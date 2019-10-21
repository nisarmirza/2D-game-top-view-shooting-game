#include "pch.h"
#include "SFML_SpriteObject.h"

// for functions to open/read files - needed to get sprite information
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

SFML_SpriteObject::SFML_SpriteObject()
	:m_initialised(false)

{
	m_defaultTexture = NULL;
}


SFML_SpriteObject::~SFML_SpriteObject()
{
	if (m_defaultTexture != NULL)
		delete m_defaultTexture;
}

bool SFML_SpriteObject::setDefaultTexture(std::string textureFileName)
{
	if (m_defaultTexture != NULL)
		delete m_defaultTexture;

	m_defaultTexture = new sf::Texture();

	if (!m_defaultTexture->loadFromFile(textureFileName))
	{
		// Failed loading the texture file
		m_initialised = false;
		delete m_defaultTexture;
		m_defaultTexture = NULL;
		return false;
	}

	// Texture file is loaded successfully 
	m_spriteTexture = m_defaultTexture;

	// Setting default origin and rectangle
	m_spriteOrigin = sf::Vector2f(m_defaultTexture->getSize().x / 2, m_defaultTexture->getSize().y / 2);
	m_textureRectangle = sf::IntRect(0, 0, m_defaultTexture->getSize().x, m_defaultTexture->getSize().y);

	m_initialised = true;
	return true;

}

bool SFML_SpriteObject::setDefaultTexture(std::string textureFileName, std::string spriteInfoFileName)
{

	if (m_defaultTexture != NULL)
		delete m_defaultTexture;

	m_defaultTexture = new sf::Texture();

	if (!m_defaultTexture->loadFromFile(textureFileName))
	{
		// Failed loading the texture file
		m_initialised = false;
		delete m_defaultTexture;
		m_defaultTexture = NULL;
		return false;

	}
	
	// Setting default origin and rectangle
	m_spriteTexture = m_defaultTexture;

	// Temoporary variables to read strings of characters from the sprite info file
	std::string s_left, s_top, s_width, s_height, s_xcenter, x_ycenter;

	// We will convert the above into integers and store them here
	int  i_left, i_top, i_width, i_height, i_xcenter, i_ycenter;

	// Open the sprite info file
	std::ifstream inputFile(spriteInfoFileName);

	if (inputFile.is_open())
	{
		// read a line
		std::string stringLine;
		std::getline(inputFile, stringLine);

		if (inputFile.good())
		{
			// Seperate the line into 6 strings
			std::istringstream stringStream(stringLine);
			stringStream >> s_left;
			stringStream >> s_top;
			stringStream >> s_width;
			stringStream >> s_height;
			stringStream >> s_xcenter;
			stringStream >> x_ycenter;


			// Convert each into integers
			i_left = std::stoi(s_left);
			i_top = std::stoi(s_top);
			i_width = std::stoi(s_width);
			i_height = std::stoi(s_height);
			i_xcenter= std::stoi(s_xcenter);
			i_ycenter = std::stoi(x_ycenter);
		}

		m_spriteOrigin = sf::Vector2f(i_xcenter - i_left, i_ycenter - i_top);
		m_textureRectangle = sf::IntRect(i_left, i_top, i_width, i_height);


		inputFile.close();

	}

	m_initialised = true;
	return true;
}

void SFML_SpriteObject::setColor(const sf::Color & color)
{
	m_sprite.setColor(color);
}

sf::Vector2f SFML_SpriteObject::getWorldPosition()
{

	return getTransform().transformPoint(0, 0);

}

sf::Vector2f SFML_SpriteObject::getScreenPosition(sf::Transform cameraScreenTransform)
{
	sf::Transform WorldCameraTransform = cameraScreenTransform * getTransform();
	return WorldCameraTransform * sf::Vector2f();
}

sf::FloatRect SFML_SpriteObject::getLocalBounds() const
{
	float left = static_cast<float> (-m_spriteOrigin.x);
	float top = static_cast<float> (-m_spriteOrigin.y);
	float width = static_cast<float> (m_textureRectangle.width);
	float height = static_cast<float> (m_textureRectangle.height);
	return sf::FloatRect(left, top, width, height);
}

sf::FloatRect SFML_SpriteObject::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

void SFML_SpriteObject::update(float elapsedTime)
{
	if (!m_initialised)
		return;

	// Assign the texture to the sprite
	if (m_spriteTexture != NULL)
		m_sprite.setTexture(*m_spriteTexture);

	// Set the sprite's texture rectangle
	m_sprite.setTextureRect(m_textureRectangle);

	// Set the sprite's origin (pivot)
	m_sprite.setOrigin(m_spriteOrigin);
}

void SFML_SpriteObject::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
}
