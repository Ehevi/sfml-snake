#include "../headers/game.hpp"

void Game::draw() {
  window.clear(Color::Black);

  // draw food
  window.draw(food.getApple());

  //newSnake();
  for(auto & s : snake) {
    window.draw(s.getShape());
  }

  window.display();
}