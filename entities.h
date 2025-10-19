#ifndef ENTITIES_H
#define ENTITIES_H

#include <SFML/Graphics.hpp>
#include "utils.h"

class Fox {
public:
    Fox();
    void update(float deltaTime, const std::vector<sf::Vector2f>& rabbitsPos);
    void draw(sf::RenderWindow& window) const;
    sf::Vector2f getPosition() const;
    void destroy();
    bool canMove = true, isAlive = true;
    int energy = 5;
    int hungry = 10;
    sf::Clock energyTimer;
    sf::Clock hungryTimer;


private:
    sf::CircleShape shape;
    sf::Vector2f direction;
    float speed;

    void move(float deltaTime);
    void bounce();

};

class Rabbit {
public:
    Rabbit();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    void changeDirection();
    bool isCaught() const;
    void catchRabbit();
    sf::Vector2f getPosition() const;
    bool canMove = true;
    int energy = 10;
    sf::Clock timer;

private:
    sf::CircleShape shape;
    sf::Vector2f direction;
    bool caught;

    void move(float deltaTime);
    void bounce();
};

#endif // ENTITIES_H
