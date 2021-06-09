#include "../headers/food.hpp"

Food::Food() {
  Vector2f startingPosition(400, 300);
  apple.setSize(Vector2f(20,20));
  apple.setFillColor(Color::Red);
  apple.setPosition(startingPosition);
}

void Food::setPosition(Vector2f newPosition) {
  apple.setPosition(newPosition);
}

RectangleShape Food::getApple() {
  return apple;
}