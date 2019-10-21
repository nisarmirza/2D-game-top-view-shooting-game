#ifndef SFML_GameMenu_H
#define SFML_GameMenu_H

#include <SFML/Graphics.hpp>
#include "SFML_GameMenu.h"
#include "SFML_TitleScreen.h"


enum MENU_ALIGNMENT
{
	LEFT_JUSTIFIED,
	CENTRE_JUSTIFIED,
	RIGHT_JUSTIFIED
};

class SFML_GameMenu  :
	public sf::Drawable, public sf::Transformable
{
public:
	SFML_GameMenu(std::string menuFileName, int WindowWidth, int WindowHeight);
	~SFML_GameMenu();
	int update(sf::Time elaspedTime);

private:
	void move(float offsetX, float offsetY);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture m_logo;
	sf::Sprite m_logoSprite;

	sf::Texture m_BackgroundTexture;
	sf::Sprite m_BackgroundSprite;
	sf::FloatRect m_BackgroundRect;

	sf::Font m_gameFont;
	sf::Color m_HighlightTextColour;
	sf::Color m_normalTextColour;
	sf::Color m_normalOutlineColour;
	sf::Color m_highlightOutlineColour;
	sf::Vector2f m_menuItemBorder;
	std::vector<sf::Text> m_menuText;

	

	std::string redString;
	std::string greenString;
	std::string blueString;

	int redInt;
	int greenInt;
	int blueInt;

	std::string xBorderString;
	std::string yBorderString;

	int xBorderInt;
	int yBorderInt;

	sf::Text start;
	sf::Vector2f textPos;

	MENU_ALIGNMENT m_menuAlignment;

	int m_highlightIndex;

	bool m_prevDownKeyPressed;
	bool m_prevUpKeyPressed;
	bool m_PrevReturnKeyPressed;
};




#endif SFML_GameMenu_H