#pragma once

#include <sfml/Graphics.hpp>
#include "SFML_Controls.h"
#include "SFML_GameMenu.h"


class SFML_Controls :
	public sf::Drawable, public sf::Transformable
{
public:
	SFML_Controls(std::string TextureFileName, int WindowWidth, int WindowHeight);
	~SFML_Controls();

	void update(sf::Time elaspedTime);


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture m_ControlTexture;
	sf::Sprite m_ControlSprite;
	sf::FloatRect m_BackgroundRect;

	sf::Texture m_messageTexture;
	sf::Sprite m_messageSprite;
	sf::Vector2f m_CreditBorder;

	sf::Font m_ControlFont;
	sf::Text start;
	sf::Vector2f textPos;
	std::vector<sf::Text> m_ControlText;

	MENU_ALIGNMENT m_ControlAlignment;
};
