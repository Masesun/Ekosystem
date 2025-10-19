#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "entities.h"
#include <vector>
#include <iostream>
#include "GameTime.h"

class Game {
public:
    Game(int numberOfFoxesChanged=3, int numberOfRabbitsChanged=10);
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void checkCollisions();
    void changeRabbitDirection();
    void updateInfoText();


    sf::RenderWindow window;
    sf::Clock clock;
    sf::Clock directionChangeClock;
    GameTime gameTime; // Dodaj zegar do mierzenia czasu symulacji
    sf::Font font;
    sf::Text infoAnimalText;
    sf::Text infoTimeText;
    int days;
    std::vector<Fox> foxes;
    std::vector<Rabbit> rabbits;
    sf::Clock reproductionFoxClock, reproductionRabbitClock;
};

#endif // GAME_H
