#include "../headers/game.hpp"
#include "../headers/wall.hpp"
#include "../headers/utils.hpp"

const sf::Time Game::TimePerFrame = seconds(1.f/60.f);

Game::Game() {
  loadFont(font);
  
  resolution = Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
  window.create(VideoMode(resolution.x, resolution.y), "Snake", Style::Default);
  window.setFramerateLimit(FPS);

  // default settings
  initialSpeed = SPEED_SLOW;
  acceleration = true;
  wallGeneration = false;
  wallsAround = false;

  currentGameState = MENU;
}

void Game::startGame() {
  srand(time(nullptr)); // for food and walls generation
  
  speed = initialSpeed;
  timeSinceLastMove = Time::Zero;
  prevGameState = currentGameState;
  sectionsToAdd = 0;

  snake.newSnake();
  walls.clear();
  directionQueue.clear();

  if (wallsAround) drawWallsAround();

  run();
  moveFood();
}

void Game::moveFood() {
  // find a location to place food
  // must not be inside the snake or wall

  // divide the field into sections the size of food -- exclude snake and walls
  Vector2f foodResolution = Vector2f(resolution.x / BLOCK - 2, resolution.y / BLOCK - 2);
  Vector2f newFoodLocation;
  bool badLocation = true;

  while (badLocation) {
    badLocation = false;
    
    // generate a random location
    newFoodLocation.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)foodResolution.x)) * BLOCK;
    newFoodLocation.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)foodResolution.y)) * BLOCK;

    for (auto &w : walls) {
      if (w.getShape().getGlobalBounds().intersects(Rect<float>(newFoodLocation.x, newFoodLocation.y, BLOCK, BLOCK))) {
        badLocation = true; // food was generated inside the wall
        break;
      }
    }

    if (snake.intersects(Rect<float>(newFoodLocation.x, newFoodLocation.y, BLOCK, BLOCK))) {
      badLocation = true; // food was generated inside the snake
      break;
    }

  }
  food.setPosition(newFoodLocation);
}

void Game::drawWallsAround() {
  walls.clear();
  Vector2f wall;
  for (float x = 0; x < SCREEN_WIDTH; x += BLOCK) {
    wall = Vector2f(x, 0);
    walls.emplace_back(wall);
    wall = Vector2f(x, SCREEN_HEIGHT - BLOCK);
    walls.emplace_back(wall);

    for (float y = 0; y < SCREEN_HEIGHT; y += BLOCK) {
      wall = Vector2f(SCREEN_WIDTH - BLOCK, y);
      walls.emplace_back(wall);
      wall = Vector2f(0, y);
      walls.emplace_back(wall);
    }
  }
}

void Game::generateRandomWall() {
  Vector2f newWall;

  Vector2f wallResolution = Vector2f(resolution.x / BLOCK - 2, resolution.y / BLOCK - 2);
  Vector2f newWallPosition;
  bool badPosition = true;

  while (badPosition) {
    badPosition = false;

    // generate random position for new wall
    newWallPosition.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)wallResolution.x)) * BLOCK;
    newWallPosition.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)wallResolution.y)) * BLOCK;

    for (auto &w : walls) {
      if (w.getShape().getGlobalBounds().intersects(Rect<float>(newWallPosition.x, newWallPosition.y, BLOCK, BLOCK))) {
        badPosition = true; // we already have a wall at the generated position
        break;
      }
    }

    if(snake.intersects(Rect<float>(newWallPosition.x, newWallPosition.y, BLOCK, BLOCK))) {
      badPosition = true; // wall was generated inside the snake
      break;
    }
  }

  walls.emplace_back(newWallPosition);
  
  for (auto &w : walls)
    window.draw(w.getShape());
}

void Game::handlePause() {
  switch(currentGameState) {
    case GameState::PLAYING:
      prevGameState = currentGameState;
      currentGameState = GameState::PAUSED;
      break;
    case GameState::PAUSED:
      currentGameState = prevGameState;
      break;
    default:
      break;
  }
}

void Game::run() {
  Clock clock;

  while (true) {
    Time dt = clock.restart();
    timeSinceLastMove += dt;

    handleInput();

    switch (currentGameState) {
      case GameState::PAUSED:
        sleep(microseconds(2)); // sleep so we don't peg the CPU
      // otherwise the loop will be iterating as fast as it possibly can
        break;
      case GameState::GAMEOVER:
        draw();
        sleep(microseconds(2));
        break;
      case GameState::MENU:
      case GameState::EXIT:
        return;
      default:
        if (timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds())
          update();
        draw();
    }
  }
}
