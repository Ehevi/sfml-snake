#include "../headers/game.hpp"

const sf::Time Game::TimePerFrame = seconds(1.f/60.f);

Game::Game() {
  resolution = Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
  window.create(VideoMode(resolution.x, resolution.y), "Snake", Style::Default);
  window.setFramerateLimit(FPS);

  speed = 2;
  snakeDirection = Direction::RIGHT;

  timeSinceLastMove = Time::Zero;

  sectionsToAdd = 0;
  newSnake();
  moveFood();
}

void Game::run() {
  Clock clock;
  
  while(window.isOpen()) {
    Time dt = clock.restart();
    timeSinceLastMove += dt;

    handleInput();
    update();
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

void Game::moveFood() {
  srand(time(nullptr));
  // find a location to place food
  // must not be inside the snake or wall

  // divide the field into sections the size of food -- exclude snake and walls
  Vector2f foodResolution = Vector2f(resolution.x / 20 - 2, resolution.y / 20 - 2);
  Vector2f newFoodLocation;
  bool badLocation = false;
  
  do {
    badLocation = false;

    // generate a random location
    newFoodLocation.x = (float)(1 + rand() / (RAND_MAX + 1u) / (int)foodResolution.x * 20);
    newFoodLocation.y = (float)(1 + rand() / (RAND_MAX + 1u) / (int)foodResolution.y * 20);

    // TODO: check if the food is in the wall
    
    // check if it is inside the snake
    for(auto & s : snake) {
      if(s.getShape().getGlobalBounds().intersects(Rect<float>(newFoodLocation.x, newFoodLocation.y, 15, 15))) {
        badLocation = true; // food was generaten inside the snake
        break;
      }
    }
  } while (badLocation);
  food.setPosition(newFoodLocation);
}