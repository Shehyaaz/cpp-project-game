#ifndef GAMEMENU_H_INCLUDED
#define GAMEMENU_H_INCLUDED
#include "SFML/Graphics.hpp"

#define MENU_ITEMS 3

class gameMenu
{
public:
	gameMenu(float width, float height);


	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MENU_ITEMS];

};

#endif // GAMEMENU_H_INCLUDED
