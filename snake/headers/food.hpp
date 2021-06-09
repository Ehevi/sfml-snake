#ifndef FOOD_HPP
#define FOOD_HPP

#include <SFML/Graphics.hpp>

// #define APPLE_RADIUS 7;

using namespace sf;

class Food {
private:
    // CircleShape apple;
    RectangleShape apple;

public:
    Food();

    void setPosition(Vector2f newPosition);
    RectangleShape getApple();
};

#endif //FOOD_HPP