#include "pch.h"
#include "SFML_2DCamera.h"


SFML_2DCamera::SFML_2DCamera(int projectionWindowWidth, int projectionWindowHeight)
// Setting camera position 
	: m_cameraPosition(0, 0)
	, m_cameraWindowSize(projectionWindowWidth, projectionWindowHeight)
	, m_cameraZoom(1)
{
	// class constructor
}


SFML_2DCamera::~SFML_2DCamera()
{
	// class decontructor
}


sf::FloatRect SFML_2DCamera::getCamerawindow(float parallaxFactor)
{
	// getting a square window for camera
	sf::FloatRect window;

	// Calculating the top-left coodinate of the visible area
	window.left = m_cameraPosition.x - m_cameraWindowSize.x / 2 * m_cameraZoom * parallaxFactor;
	window.top = m_cameraPosition.y - m_cameraWindowSize.y / 2 * m_cameraZoom * parallaxFactor;

	// The width and height are simply x and y attributes
	window.width = m_cameraWindowSize.x * m_cameraZoom * parallaxFactor;
	window.height = m_cameraWindowSize.y * m_cameraZoom * parallaxFactor;

	// Return the rectangle 
	return window;
}

void SFML_2DCamera::setPosition(sf::Vector2f target)
{
	// Set the camera position to the input
	m_cameraPosition = target;
}

void SFML_2DCamera::zoomUp(float elapsedTime)
{
	// setting zoom speed in 
	float zoomSpeed = 60.0f;
	float zoomChange = m_cameraZoom * 0.1f * elapsedTime * zoomSpeed;
	m_cameraZoom = m_cameraZoom - zoomChange;
}

void SFML_2DCamera::zoomDown(float elapsedTime)
{
	// setting zoom speed out
	float zoomSpeed = 60.0f;
	float zoomChange = m_cameraZoom * 0.1f * elapsedTime * zoomSpeed;
	m_cameraZoom = m_cameraZoom + zoomChange;
}

sf::Transform SFML_2DCamera::getViewTransform() const
{
	// Transform the coordinate from WORLD space CAMERA space
	// Centered at the middle of the visible window
	// Example, if camera is at (10,20), an object at (10,20) will be at center
	sf::Transform transform = sf::Transform::Identity;
	transform.translate(m_cameraPosition);
	return transform.getInverse();
}

sf::Transform SFML_2DCamera::getprojTransform() const
{
	// Transform the coordinate from CAMERA space to SCREEN space
	// Note that SCREEN space origin point is at the top left corner
	// So we effectively shifting the coordinatee by half the screen dimension
	sf::Transform transform = sf::Transform::Identity;
	transform.translate(m_cameraWindowSize.x / 2, m_cameraWindowSize.y / 2);
	transform.scale(1.0f / m_cameraZoom, 1.0f / m_cameraZoom);

	return transform;
}

