#include "entities.h"
#include "config.h"
#include <iostream>

Fox::Fox() {
    shape.setRadius(20);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(100 + std::rand() % 1000, 100); 
    direction = randomDirection();
    speed = baseSpeed + static_cast<float>(std::rand()) / RAND_MAX * (maxSpeed - baseSpeed);
    energy = 5;
    hungry = 10;
    isAlive = true;
}

void Fox::update(float deltaTime, const std::vector<sf::Vector2f>& zajacePos) {
    sf::Vector2f lisPos = shape.getPosition();
    sf::Vector2f closestZajacPos;
    float closestZajacDistance = std::numeric_limits<float>::max();

    for (const auto& zajacPos : zajacePos) {
        float distToZajac = distance(lisPos, zajacPos);
        if (distToZajac < closestZajacDistance) {
            closestZajacDistance = distToZajac;
            closestZajacPos = zajacPos;
        }
    }

    if (closestZajacDistance != std::numeric_limits<float>::max()) {
        sf::Vector2f directionToZajac = closestZajacPos - lisPos;
        direction = normalize(directionToZajac);
        speed = chasingSpeed;
    }
    else {
        direction = randomDirection();
        speed = baseSpeed + static_cast<float>(std::rand()) / RAND_MAX * (maxSpeed - baseSpeed);
    }

    move(deltaTime);
    bounce();
}

void Fox::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::Vector2f Fox::getPosition() const {
    return shape.getPosition();
}

void Fox::move(float deltaTime) {
    if (energy != 0)
        shape.move(direction * speed * deltaTime);
}

void Fox::bounce() {
    sf::Vector2f pos = shape.getPosition();
    if (pos.x < 0 || pos.x + shape.getRadius() * 2 > 1000) {
        direction.x = -direction.x;
    }
    if (pos.y < 50 || pos.y + shape.getRadius() * 2 > 700) {
        direction.y = -direction.y;
    }
}

void Fox::destroy() {
    shape.setRadius(0.0f);
    shape.setPosition(0, 0);
    canMove = false;
    std::cout << "Fox has died!" << std::endl;
    isAlive = false;
}

Rabbit::Rabbit() {
    shape.setRadius(15);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(100 + std::rand() % 600, 300);
    direction = randomDirection();
    caught = false;
    energy = 10;
}

void Rabbit::update(float deltaTime) {
    if (!caught) {
        move(deltaTime);
        bounce();
    }
}

void Rabbit::draw(sf::RenderWindow& window) const {
    if (!caught) {
        window.draw(shape);
    }
}

void Rabbit::changeDirection() {
    if (!caught) {
        direction = randomDirection();
    }
}

bool Rabbit::isCaught() const {
    return caught;
}

void Rabbit::catchRabbit() {
    caught = true;
}

sf::Vector2f Rabbit::getPosition() const {
    return shape.getPosition();
}

void Rabbit::move(float deltaTime) {
    shape.move(direction * rabbitSpeed * deltaTime);
}

void Rabbit::bounce() {
    sf::Vector2f pos = shape.getPosition();
    if (pos.x < 0 || pos.x + shape.getRadius() * 2 > 1000) {
        direction.x = -direction.x;
    }
    if (pos.y < 50 || pos.y + shape.getRadius() * 2 > 700) {
        direction.y = -direction.y;
    }
}

