#include "../headers/game.hpp"

void Game::draw() {
  window.clear(Color::Black);

  // draw walls
  for(auto &w : walls)
    window.draw(w.getShape());
  
  // draw food
  window.draw(food.getApple());

  // draw snake
  for(auto &s : snake)
    window.draw(s.getShape());

  window.display();
}