#include<iostream>
#include "gameMenu.h"

gameMenu::gameMenu(float width, float height)
{
	if (!font.loadFromFile("font/xirod.ttf")) std::cout<<"Unable to load font!";

    sf::FloatRect textRect;
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color(255,0,0));
	menu[0].setString("New Game");
    textRect = menu[0].getLocalBounds();
    menu[0].setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MENU_ITEMS+1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color(255,255,255));
	menu[1].setString("Load Game");
    textRect = menu[1].getLocalBounds();
    menu[1].setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MENU_ITEMS+1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color(255,255,255));
	menu[2].setString("Exit");
    textRect = menu[2].getLocalBounds();
    menu[2].setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MENU_ITEMS+1) * 3));

	selectedItemIndex = 0;
}//end of constructor

void gameMenu::draw(sf::RenderWindow &app)
{
	for (int i = 0; i < MENU_ITEMS; i++)
		app.draw(menu[i]);
}//end of function

void gameMenu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color(255,255,255));
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color(255,0,0));
	}
}//end of function

void gameMenu::MoveDown()
{
	if (selectedItemIndex + 1 < MENU_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color(255,255,255));
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color(255,0,0));
	}
}//end of function
