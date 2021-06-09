#ifndef FOOD_HPP
#define FOOD_HPP

#include <SFML/Graphics.hpp>

#define APPLE_RADIUS 10;

using namespace sf;

class Food {
private:
    CircleShape apple;
    RectangleShape appleSpace;

public:
    Food();

    void setPosition(Vector2f newPosition);
    RectangleShape getAppleSpace();
    CircleShape getApple();
};

#endif //FOOD_HPP