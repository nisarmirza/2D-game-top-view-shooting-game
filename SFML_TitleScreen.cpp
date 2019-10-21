#include "pch.h"
#include "SFML_TitleScreen.h"


SFML_TitleScreen::SFML_TitleScreen(std::string TextureFileName, int WindowWidth, int WindowHeight)
{
	m_titleScreenTexture.loadFromFile(TextureFileName);
	m_titleScreenSprite.setTexture(m_titleScreenTexture);
	sf::Vector2u bkTextureSize = m_titleScreenTexture.getSize();
	m_titleScreenSprite.setTextureRect(sf::IntRect(0, 0, bkTextureSize.x, bkTextureSize.y));
	m_titleScreenSprite.setPosition(0, 0);
	m_messageTexture.loadFromFile("Media/Textures/continue.png");
	m_messageSprite.setTexture(m_messageTexture);
	m_messageSprite.setPosition(WindowWidth * 0.5f, WindowHeight * 0.9f);
	sf::Vector2u msgTextureSize = m_messageTexture.getSize();
	m_messageSprite.setOrigin(msgTextureSize.x / 2, msgTextureSize.y / 2);
	m_messageSprite.setTextureRect(sf::IntRect(0, 0, msgTextureSize.x, msgTextureSize.y));
	m_messageSprite.setColor(sf::Color(255, 0, 0));
	m_timeScinceLastFlash = sf::Time::Zero;
	m_flashingTime = sf::seconds(0.2f);
	
}


SFML_TitleScreen::~SFML_TitleScreen()
{
}

void SFML_TitleScreen::update(sf::Time elaspedTime)
{
	// the flashing picture on title screen (timer has been used for this(seconds)
	{
		m_timeScinceLastFlash += elaspedTime;
		if (m_timeScinceLastFlash > m_flashingTime)
		{
			m_flashon = !m_flashon;
			m_timeScinceLastFlash -= m_flashingTime;
			if (m_flashon)
				m_messageSprite.setColor(sf::Color(255, 255, 255));
			else
				m_messageSprite.setColor(sf::Color(255, 0, 0));
		}
	}
	
}

void SFML_TitleScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_titleScreenSprite);
	target.draw(m_messageSprite);
	
}



