#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

struct Data {
	int numberFox = 3, numberRabbit = 10;
	int activeValue = 1;
};

class Menu {
public:
	Menu(float width, float height);
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() const;

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[3];
};

#endif //MENU_H