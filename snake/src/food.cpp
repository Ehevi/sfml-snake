#include "../headers/food.hpp"

Food::Food() {
    Vector2f startingPosition(400, 300);
    apple.setRadius(7);
    apple.setFillColor(Color::Red);
    apple.setPosition(startingPosition);
    //apple.setSize(Vector2f(15, 15));
    //sprite.setFillColor(Color::Red);
    //sprite.setPosition(startingPosition);
}

void Food::setPosition(Vector2f newPosition) {
    //sprite.setPosition(newPosition);
    apple.setPosition(newPosition);
}

CircleShape Food::getApple() {
    return apple;
}