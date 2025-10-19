#include "GameTime.h"

GameTime::GameTime()
	: elapsedTime(0), days(0) {
}

void GameTime::reset() {
	elapsedTime = 0;
	days = 0;
	clock.restart();
}

void GameTime::update(float deltaTime) {
	elapsedTime += deltaTime;
	days = static_cast<int>(elapsedTime / secondsPerDay);
}

int GameTime::getDays() const {
	return days;
}