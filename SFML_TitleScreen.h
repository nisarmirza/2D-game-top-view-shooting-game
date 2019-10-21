#ifndef SFML_TitleScreen_H
#define SFML_TitleScreen_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics/Drawable.hpp>

class SFML_TitleScreen :
	public sf::Drawable
{
public:
	SFML_TitleScreen(std::string TextureFileName, int WindowWidth, int WindowHeight);
	~SFML_TitleScreen();

	void update(sf::Time elaspedTime);


private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	sf::Texture m_titleScreenTexture;
	sf::Sprite m_titleScreenSprite;

	sf::Texture m_messageTexture;
	sf::Sprite m_messageSprite;

	sf::Time m_flashingTime;
	sf::Time m_timeScinceLastFlash;

	bool m_flashon;
};


#endif // SFML_TitleScreen_H
