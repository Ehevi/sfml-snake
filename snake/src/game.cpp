#include "../headers/game.hpp"

const sf::Time Game::TimePerFrame = seconds(1.f/60.f);

Game::Game() {
  resolution = Vector2f(SCREEN_WIDTH, SCREEN_WIDTH);
  window.create(VideoMode(resolution.x, resolution.y), "Snake", Style::Default);
  window.setFramerateLimit(FPS);
}

void Game::run() {
  while(window.isOpen()) {
    handleInput();
    draw();
  }
}

void Game::newSnake() {
  snake.clear(); // czyszczenie vectora
  snake.emplace_back(Vector2f(100, 100));
  snake.emplace_back(Vector2f(80, 100));
  snake.emplace_back(Vector2f(60, 100));
  // horizontal line of snake sections
}

void Game::addSnakeSection() {
  Vector2f newSectionPosition = snake[snake.size() -1].getPosition();
  snake.emplace_back(newSectionPosition);
}