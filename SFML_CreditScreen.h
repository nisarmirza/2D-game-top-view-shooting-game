#pragma once

#include <sfml/Graphics.hpp>
#include "SFML_CreditScreen.h"
#include "SFML_GameMenu.h"


class SFML_CreditScreen :
	public sf::Drawable, public sf::Transformable
{
public:
	SFML_CreditScreen(std::string TextureFileName, int WindowWidth, int WindowHeight);
	~SFML_CreditScreen();

	void update(sf::Time elaspedTime);


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture m_CreditScreenTexture;
	sf::Sprite m_CreditScreenSprite;
	sf::FloatRect m_BackgroundRect;

	sf::Texture m_logo;
	sf::Sprite m_logoSprite;

	sf::Texture m_messageTexture;
	sf::Sprite m_messageSprite;
	sf::Vector2f m_CreditBorder;

	sf::Font m_CreditFont;
	sf::Text start;
	sf::Vector2f textPos;
	std::vector<sf::Text> m_CreditText;

	MENU_ALIGNMENT m_CreditAlignment;
};
