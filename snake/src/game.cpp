#include "../headers/game.hpp"

const sf::Time Game::TimePerFrame = seconds(1.f/60.f);

Game::Game() {
  resolution = Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
  window.create(VideoMode(resolution.x, resolution.y), "Snake", Style::Default);
  window.setFramerateLimit(FPS);

  startGame();
}

void Game::startGame() {
  speed = 2;
  snakeDirection = Direction::RIGHT;
  timeSinceLastMove = Time::Zero;
  currentGameState = GameState::PLAYING;
  lastGameState = currentGameState;
  sectionsToAdd = 0;
  directionQueue.clear();
  newSnake();
  moveFood();
}

// This is the initial snake created at the start of each level
void Game::newSnake() {
  snake.clear(); // czyszczenie wektora
  for(auto &s: snakeInitialPosition) {
    snake.emplace_back(s);
  }
}

void Game::addSnakeSection() {
  Vector2f newSectionPosition = snake[snake.size() - 1].getPosition();
  snake.emplace_back(newSectionPosition);
}

void Game::moveFood() {
  srand(time(nullptr));
  // find a location to place food
  // must not be inside the snake or wall

  // divide the field into sections the size of food -- exclude snake and walls
  Vector2f foodResolution = Vector2f(resolution.x / 20 - 2, resolution.y / 20 - 2);
  Vector2f newFoodLocation;
  bool badLocation = false;
  // srand(time(nullptr));
  // Loop until we find a valid location
  do {
    badLocation = false;
    
    // generate a random location
    newFoodLocation.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)foodResolution.x)) * 20;
    newFoodLocation.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)foodResolution.y)) * 20;

    // TODO: check whether the food was not generated inside the wall

    // check if it is inside the snake
    for(auto &s : snake) {
      if(s.getShape().getGlobalBounds().intersects(Rect<float>(newFoodLocation.x, newFoodLocation.y, 20, 20))) {
        badLocation = true; // food was generated inside the snake
        break;
      }
    }
  } while (badLocation);
  food.setPosition(newFoodLocation);
}

void Game::handlePause() {
  switch(currentGameState) {
    case GameState::PLAYING:
      lastGameState = currentGameState;
      currentGameState = GameState::PAUSED;
      break;
    case GameState::PAUSED:
      currentGameState = lastGameState;
      break;
    default:
      break;
  }
}

void Game::run() {
  Clock clock;

  // main loop - runs until the window is closed
  while (window.isOpen()) {
    Time dt = clock.restart();
    timeSinceLastMove += dt;

    handleInput();

    switch (currentGameState) {
      case GameState::PAUSED:
        sleep(microseconds(2)); // sleep so we don't peg the CPU
      // otherwise the loop will be iterating as fast as it possibly can
        continue;
      case GameState::GAMEOVER:
        draw();
        sleep(microseconds(2));
        continue;
      default:
        update();
        draw();
    }
  }
}