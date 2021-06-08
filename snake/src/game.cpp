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