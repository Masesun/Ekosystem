#include "Game.h"
#include "Menu.h"
#include "config.h"

Game::Game(int numberOfFoxesChanged, int numberOfRabbitsChanged)
    : window(sf::VideoMode(1000, 700), "SIMULATION"), days(0) {
 
    for (int i = 0; i < numberOfFoxesChanged; ++i) {
        foxes.emplace_back();
    }

    for (int i = 0; i < numberOfRabbitsChanged; ++i) {
        rabbits.emplace_back();
    }

    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Font issue!" << std::endl;
        std::exit(0);
    }

    infoAnimalText.setFont(font);
    infoAnimalText.setCharacterSize(24);
    infoAnimalText.setFillColor(sf::Color::Black);
    infoAnimalText.setPosition(10, 10);

    infoTimeText.setFont(font);
    infoTimeText.setCharacterSize(24);
    infoTimeText.setFillColor(sf::Color::Black);
    infoTimeText.setPosition(800, 10);

    updateInfoText();
}

void Game::run() {

    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();
        update(deltaTime);
        render();

        bool allCaught = true;
        for (const auto& rabbit : rabbits) {
            if (!rabbit.isCaught()) {
                allCaught = false;
                break;
            }
        }
        if (allCaught) {
            sf::sleep(sf::seconds(2));
            window.close();
        }
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Game::update(float deltaTime) {
    for (auto& fox : foxes) {
        std::vector<sf::Vector2f> zajacePos;
        for (const auto& rabbit : rabbits) {
            if (!rabbit.isCaught()) {
                zajacePos.push_back(rabbit.getPosition());
            }
        }
        if (fox.canMove) {
            fox.update(deltaTime, zajacePos);
            if (fox.energyTimer.getElapsedTime() >= sf::seconds(1.0f)) {
                if (fox.energy == 0 && fox.canMove)
                    fox.canMove = false;
                else
                    fox.energy--;
                fox.energyTimer.restart();
            }
            if (fox.hungryTimer.getElapsedTime() >= sf::seconds(2.0f)) {
                if (fox.hungry == 0) {
                    fox.destroy();
                }
                else
                    fox.hungry--;
                fox.hungryTimer.restart();

            }
            if (reproductionFoxClock.getElapsedTime() >= sf::seconds(20.0f)) {
                if (foxes.size() >= 2) {
                    Fox newFox;
                    foxes.push_back(newFox);
                }
                reproductionFoxClock.restart();
            }
        }
        else {
            if (fox.energyTimer.getElapsedTime() >= sf::seconds(3.0f)) {
                fox.canMove = true;
                fox.energyTimer.restart();
                fox.energy = 5;
                fox.hungry++;
            }
        }
    }

    if (directionChangeClock.getElapsedTime() > sf::seconds(2)) {
        changeRabbitDirection();
        directionChangeClock.restart();
    }

    for (auto& rabbit : rabbits) {
        if (rabbit.canMove) {
            rabbit.update(deltaTime);
            if (rabbit.timer.getElapsedTime() >= sf::seconds(1.0f)) {
                if (rabbit.energy == 0)
                    rabbit.canMove = false;
                else
                    rabbit.energy--;
                rabbit.timer.restart();
            }
            if (reproductionRabbitClock.getElapsedTime() >= sf::seconds(2.0f)) {
                if (rabbits.size() >= 2) {
                    Rabbit newRabbit;
                    rabbits.push_back(newRabbit);
                }
                reproductionRabbitClock.restart();
            }
        }
        else {
            if (rabbit.timer.getElapsedTime() >= sf::seconds(2.0f)) {
                rabbit.canMove = true;
                rabbit.timer.restart();
                rabbit.energy = 10;
            }
        }
    }
    checkCollisions();
    gameTime.update(deltaTime);
    updateInfoText();
}

void Game::render() {
    window.clear(sf::Color::White);

    sf::RectangleShape infoBackground(sf::Vector2f(1000, 50));
    infoBackground.setFillColor(sf::Color::White);

    sf::RectangleShape bottomEdge(sf::Vector2f(infoBackground.getSize().x, 2.0f));
    bottomEdge.setPosition(infoBackground.getPosition().x, infoBackground.getPosition().y + infoBackground.getSize().y - bottomEdge.getSize().y);
    bottomEdge.setFillColor(sf::Color::Black);

    window.draw(infoBackground);
    window.draw(bottomEdge);

    window.draw(infoAnimalText);
    window.draw(infoTimeText);

    for (const auto& fox : foxes) {
        fox.draw(window);
    }
    for (const auto& rabbit : rabbits) {
        rabbit.draw(window);
    }
    window.display();
}

void Game::checkCollisions() {
    for (auto& fox : foxes) {
        for (auto& rabbit : rabbits) {
            if (!rabbit.isCaught() && distance(fox.getPosition(), rabbit.getPosition()) < 20.0f) {
                rabbit.catchRabbit();
                std::cout << "Fox has caught rabbit!\n";
                fox.energy = 5;
                fox.hungry = 10;
                fox.energyTimer.restart();
                fox.hungryTimer.restart();
            }
        }
    }
}

void Game::changeRabbitDirection() {
    for (auto& rabbit : rabbits) {
        rabbit.changeDirection();
    }
}

void Game::updateInfoText() {
    int numberOfRabbits = 0;
    for (const auto& rabbit : rabbits) {
        if (!rabbit.isCaught()) {
            numberOfRabbits++;
        }
    }

    int numberOfFoxes = 0;
    for (const auto& fox : foxes) {
        if (fox.isAlive)
            numberOfFoxes++;
    }
    infoAnimalText.setString("Fox: " + std::to_string(numberOfFoxes) + "       Rabbit: " + std::to_string(numberOfRabbits));
    infoTimeText.setString("Day: " + std::to_string(gameTime.getDays()));
}

