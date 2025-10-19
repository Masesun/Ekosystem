#ifndef GAMETIME_H
#define GAMETIME_H

#include <SFML/Graphics.hpp>

class GameTime {
public:
	GameTime();

	void reset();
	void update(float deltaTime);
	int getDays() const;

private:
	sf::Clock clock;
	float elapsedTime;
	int days;

	static constexpr float secondsPerDay = 5.0f;
};

#endif // GAMETIME_H