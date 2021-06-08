#include "../headers/game.hpp"

const sf::Time Game::TimePerFrame = seconds(1.f/60.f);

Game::Game() {
  resolution = Vector2f(800, 600);
  window.create(VideoMode(resolution.x, resolution.y), "Hello My Snake Game", Style::Default);
  window.setFramerateLimit(FPS);

  newSnake();
}

void Game::draw() {
  window.clear(Color::Black);

  // Draw snake sections
  for (auto & s : snake) {
    window.draw(s.getShape());
  }

  window.display();
}

// This is the initial snake created at the start of each level
void Game::newSnake() {
  snake.clear();
  snake.emplace_back(Vector2f(100,100));
  snake.emplace_back(Vector2f(80,100));
  snake.emplace_back(Vector2f(60,100));
}

void Game::input() {
  Event event{};

  while (window.pollEvent(event)) {
    // Window closed
    if (event.type == Event::Closed) {
      window.close();
    }

    // Handle Keyboard Input
    if (event.type == Event::KeyPressed) {
      // Quit
      if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
      }
    }
  }
}

void Game::addSnakeSection() {
  // Just add the section at the same position as the last section of the snake, it will follow normally
  Vector2f newSectionPosition = snake[snake.size() - 1].getPosition();
  snake.emplace_back(newSectionPosition);
}

void Game::run() {

  // Main loop - Runs until the window is closed
  while (window.isOpen()) {
    input();
    draw();
  }
}
