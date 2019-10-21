#ifndef SFML_GameWorldLayer_H
#define SFML_GameWorldLayer_H


#include <SFML/Graphics.hpp>
#include "SFML_2DCamera.h"
class SFML_GameWorldLayer :
	public sf::Drawable
{
public:
	SFML_GameWorldLayer(std::string textureFileName, float parallaxFactor, int viewPortWidth,  int viewPortHeight );
	~SFML_GameWorldLayer();

	void followCamera(SFML_2DCamera* camera);

	// Member function to set parallax factor after object creation 
	void setParallaxFactor(float parallaxFactor);

	// Member function to get the layer's current parallax factor
	float getParallaxFactor();

	void setScrollSpeed(sf::Vector2f scrollSpeed);

	void Update(float elapsedTime);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Member attribute to store texture object
	sf::Texture m_layerTexture;

	// Member attribute to store the window vertices
	sf::VertexArray m_layerVertices;

	sf::Vector2f m_offset;
	sf::Vector2f m_scrollSpreed;

	// Member attribute to store the layer's parallax factor
	float m_parallaxFactor;

};


#endif // !SFML_GameWorldLayer_H