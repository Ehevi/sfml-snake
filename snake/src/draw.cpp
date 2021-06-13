#include "../headers/game.hpp"

void Game::draw(RenderWindow &window) {
  window.clear(Color::Black);

  /*
  vector<Wall> walls = game.getWalls();
  Food food = game.getFood();
  Snake snake = game.getSnake();
  */
  // draw walls
  for(auto &w : walls)
    window.draw(w.getShape());
  
  // draw food
  window.draw(food.getApple());

  // draw snake
  snake.draw(window);
  /*
  for(auto &s : snake)
    window.draw(s.getShape());
  */

  window.display();
}