#include "../headers/food.hpp"

Food::Food() {
  Vector2f startingPosition(400, 300);
  appleSpace.setSize(Vector2f(20,20));
  appleSpace.setPosition(startingPosition);
  apple.setRadius(10);
  apple.setPosition(startingPosition);
  apple.setFillColor(Color::Red);
}

void Food::setPosition(Vector2f newPosition) {
  appleSpace.setPosition(newPosition);
  apple.setPosition(newPosition);
}

RectangleShape Food::getAppleSpace() {
  return appleSpace;
}

CircleShape Food::getApple() {
  return apple;
}