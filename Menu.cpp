#include "Menu.h"

Menu::Menu(float width, float height) {
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Font issue!" << std::endl;
		std::exit(0);
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Simulation start");
	sf::FloatRect textRect = menu[0].getLocalBounds();
	menu[0].setOrigin(textRect.width / 2, textRect.height / 2);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Custom values");
	textRect = menu[1].getLocalBounds();
	menu[1].setOrigin(textRect.width / 2, textRect.height / 2);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Authors");
	textRect = menu[2].getLocalBounds();
	menu[2].setOrigin(textRect.width / 2, textRect.height / 2);
	menu[2].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 3));

	selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow& window) {
	for (int i = 0; i < 3; i++) {
		window.draw(menu[i]);
	}
}

void Menu::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown() {
	if (selectedItemIndex + 1 < 3) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

int Menu::GetPressedItem() const {
	return selectedItemIndex;
}

