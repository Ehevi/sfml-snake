#include "../headers/game.hpp"

const sf::Time Game::TimePerFrame = seconds(1.f/60.f);

Game::Game() {
  resolution = Vector2f(SCREEN_WIDTH, SCREEN_WIDTH);
  window.create(VideoMode(resolution.x, resolution.y), "Snake", Style::Default);
  window.setFramerateLimit(FPS);
}

void Game::run() {
  while(window.isOpen()) {
    enableClose();
    draw();
  }
}

void Game::draw() {
  window.clear(Color::Black);

  newSnake();
  for(auto & s : snake) {
    window.draw(s.getShape());
  }

  window.display();
}

void Game::enableClose() {
  Event event{};
  while(window.pollEvent(event)) {
    if(event.type == Event::Closed) {
      window.close();
    }

    if(event.type == Event::KeyPressed) {
      if(Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
      }
    }
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