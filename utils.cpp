#include "utils.h"
#include <cmath>
#include <cstdlib>

float distance(sf::Vector2f a, sf::Vector2f b) {
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

sf::Vector2f normalize(sf::Vector2f v) {
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    if (len != 0)
        return v / len;
    return v;
}

sf::Vector2f randomDirection() {
    float angle = static_cast<float>(std::rand()) / RAND_MAX * 2 * 3.14159f;
    return sf::Vector2f(std::cos(angle), std::sin(angle));
}