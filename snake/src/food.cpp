#include "../headers/food.hpp"
#include "../headers/utils.hpp"

Food::Food() {
  Vector2f startingPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
  appleSpace.setSize(Vector2f(BLOCK, BLOCK));
  appleSpace.setPosition(startingPosition);
  apple.setRadius(APPLE_RADIUS);
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