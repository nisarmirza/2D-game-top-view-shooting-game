#ifndef SFML_SpriteObject_H
#define SFML_SpriteObject_H



#include <SFML/Graphics.hpp>


class SFML_SpriteObject :
	public sf::Drawable, public sf::Transformable
{
public:
	SFML_SpriteObject();
	virtual ~SFML_SpriteObject();

	// Memeber functions to load and set the default texture to use 
	bool setDefaultTexture(std::string textureFileName);
	bool setDefaultTexture(std::string textureFileName, std::string spriteInfoFileName);

	// Member function to set the tint colour 
	void setColor(const sf::Color& color);

	// Member function to get the object's world position
	sf::Vector2f getWorldPosition();

	// Member function to ger the object's screen position
	sf::Vector2f getScreenPosition(sf::Transform cameraScreenTransform);

	// Member function to get the object's global and local bounding rectangles
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

	// Member function to update the object's states
	virtual void update(float elapsedTime);


private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	// Member attribute for default texture
	sf::Texture* m_defaultTexture;

	



protected:

	// Member attribute to store the sfml sprite
	sf::Sprite m_sprite;

	// Member attribute to store texture rectangle 
	sf::Texture* m_spriteTexture;

	// Member attribute to store texture rectangle 
	sf::IntRect m_textureRectangle;

	// Member attribute to store origin point 
	sf::Vector2f m_spriteOrigin;

	// To help us keep track if the object has been successfully initialised 
	bool m_initialised;

};


#endif // !SFML_SpriteObject_H
