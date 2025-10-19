#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"

Data data;

void updateText(sf::Text& text, const Data& data) {
    text.setString("Number of foxes: " + std::to_string(data.numberFox) + "\n"
        "Number of rabbits: " + std::to_string(data.numberRabbit));
    text.setFillColor(sf::Color::White);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.height / 2.0f,
        textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(400, 300));
}

void showAuthors(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Font issue!" << std::endl;
        std::exit(0);
    }

    sf::Text authorText;
    authorText.setFont(font);
    authorText.setFillColor(sf::Color::White);
    authorText.setString("Autorzy:\n1. Bartosz Sychowicz\n2. Kamil Sitko");
    sf::FloatRect textRect = authorText.getLocalBounds();
    authorText.setOrigin(textRect.width / 2, textRect.height / 2);
    authorText.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed) {
                return;
            }
        }

        window.clear();
        window.draw(authorText);
        window.display();
    }
}

void changeParameters(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    sf::Text text;
    text.setFont(font); 
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    if (data.activeValue == 1 && data.numberFox > 1)
                        data.numberFox--;
                    else if (data.activeValue == 2 && data.numberRabbit > 1)
                        data.numberRabbit--;
                    /*else if (data.activeValue == 3 && data.speed > 0.1)
                        data.speed -= 0.1;*/
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    if (data.activeValue == 1 && data.numberFox < 10)
                        data.numberFox++;
                    else if (data.activeValue == 2 && data.numberRabbit < 20)
                        data.numberRabbit++;
                    /*else if (data.activeValue == 3 && data.speed < 3.0)
                        data.speed += 0.1;*/
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    if (data.activeValue < 3)
                        data.activeValue++;
                    else
                        data.activeValue = 1;
                    updateText(text, data);
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    if (data.activeValue > 1)
                        data.activeValue--;
                    else
                        data.activeValue = 3;
                    updateText(text, data);
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    return;
                }
            }
        }
        updateText(text, data);

        window.clear();

        window.draw(text);

        window.display();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "MENU");

    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    menu.MoveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    menu.MoveDown();
                }
                else if (event.key.code == sf::Keyboard::Return) {
                    int selectedItem = menu.GetPressedItem();
                    if (selectedItem == 0) {
                        Game game(data.numberFox, data.numberRabbit);
                        game.run();
                    }
                    else if (selectedItem == 1) {
                        changeParameters(window);
                    }
                    else if (selectedItem == 2) {
                        showAuthors(window);
                    }
                }
            }
        }

        window.clear();
        menu.draw(window);
        window.display();
    }

    return 0;
}
