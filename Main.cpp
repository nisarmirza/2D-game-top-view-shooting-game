// week1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\color.hpp>
#include "pch.h"
#include <iostream>
#include "SFML_APPLICATION.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SFML_GameMenu.h"
#include "SFML_TitleScreen.h"



int main()
{


	// Setting the screen size to 1920, 1820 and making the app run on that size
	SFML_APPLICATION app(1980, 1080);
	app.run();
	return 0;

	
	   

	// --------------------------------------- NOT WORTH HAVING A LOOK ----------------------------------------------------
	/*
	int screenWidth = 800;
	int ScreenHeight = 600;

	sf::RenderWindow Window(sf::VideoMode(screenWidth, ScreenHeight), "4109 - week1");


	float circleRadius = 100;
	sf::CircleShape Circle(100);
	Circle.setFillColor(sf::Color::Red);
	Circle.setOutlineThickness(8);
	Circle.setOutlineColor(sf::Color::Yellow);
	




	Circle.setPosition(sf::Vector2f(150,50 ));
	while (Window.isOpen())
	{
		sf::Event Event;
		while (Window.pollEvent(Event))
		{
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					Circle.move(0, 1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					Circle.move(0, -1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					Circle.move(-1, 0);
					Circle.setFillColor(sf::Color::Cyan);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					Circle.move(1, 0);
					Circle.setFillColor(sf::Color::Green);
				}
			
			}
			if (Event.type == sf::Event::Closed)
				Window.close();
		}
		Window.clear();
		Window.draw(Circle);
		Window.display();
	}
	*/
	// -----------------------------------------------------------------------------------------------------------------------
	}

