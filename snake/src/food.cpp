#include "../headers/food.hpp"
#include "../headers/utils.hpp"

Food::Food() {
  Vector2f startingPosition(400, 300);
  appleSpace.setSize(Vector2f(BLOCK, BLOCK));
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