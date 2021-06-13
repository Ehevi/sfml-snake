#include "../headers/game.hpp"
#include "../headers/wall.hpp"
#include "../headers/utils.hpp"

void Game::newGame(RenderWindow &window, Vector2f gameResolution, int newInitialSpeed, bool newAcceleration, bool newWallsAround, bool newWallGeneration) {
    srand(time(nullptr)); // for food and walls generation

    resolution = gameResolution;
    initialSpeed = newInitialSpeed;
    speed = initialSpeed;
    acceleration = newAcceleration;
    wallsAround = newWallsAround;
    wallGeneration = newWallGeneration;

    timeSinceLastMove = Time::Zero;
    currentGameState = GameState::RUNNING;
    prevGameState = currentGameState;
    
    sectionsToAdd = 0;
    walls.clear();
    directionQueue.clear();
    snake.newSnake();
    
    if (wallsAround) buildWallsAround();

    run(window);
    moveFood();
}

void Game::moveFood() {
    // find a location to place food

    // divide the field into sections the size of food
    Vector2f foodResolution = Vector2f(resolution.x / BLOCK - 2, resolution.y / BLOCK - 2);
    Vector2f newFoodPosition;
    bool badPosition = true;

    while (badPosition) {
        badPosition = false;

        // generate a random location
        newFoodPosition.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)foodResolution.x)) * BLOCK;
        newFoodPosition.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)foodResolution.y)) * BLOCK;

        for (auto &w : walls)
            if (w.getShape().getGlobalBounds().intersects(Rect<float>(newFoodPosition.x, newFoodPosition.y, BLOCK, BLOCK))) {
                badPosition = true; // food was generated inside the wall
                break;
            }

        if (snake.intersects(Rect<float>(newFoodPosition.x, newFoodPosition.y, BLOCK, BLOCK))) {
            badPosition = true; // food was generated inside the snake
            break;
        }
    }
    
    food.setPosition(newFoodPosition);
}

void Game::buildWallsAround() {
    for (float x = 0; x < SCREEN_WIDTH; x += BLOCK) {
        walls.emplace_back(Vector2f(x, 0));
        walls.emplace_back(Vector2f(x, SCREEN_HEIGHT - BLOCK));

        for (float y = 0; y < SCREEN_HEIGHT; y += BLOCK) {
            walls.emplace_back(Vector2f(0, y));
            walls.emplace_back(Vector2f(SCREEN_WIDTH - BLOCK, y));
        }
    }
}

void Game::generateRandomWall() {
    Vector2f wallResolution = Vector2f(resolution.x / BLOCK - 2, resolution.y / BLOCK - 2);
    Vector2f newWallPosition;
    bool badPosition = true;

    while (badPosition) {
        badPosition = false;

        // generate random position for the new wall
        newWallPosition.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)wallResolution.x)) * BLOCK;
        newWallPosition.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)wallResolution.y)) * BLOCK;

        for (auto &w : walls)
            if (w.getShape().getGlobalBounds().intersects(Rect<float>(newWallPosition.x, newWallPosition.y, BLOCK, BLOCK))) {
                badPosition = true; // we already have a wall at the generated position
                break;
            }
        
        if (snake.intersects(Rect<float>(newWallPosition.x, newWallPosition.y, BLOCK, BLOCK))) {
            badPosition = true; // wall was generated inside the snake
            break;
        }
    }

    walls.emplace_back(newWallPosition);
}

void Game::handlePause() {
    switch (currentGameState) {
        case GameState::RUNNING:
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

void Game::run(RenderWindow &window) {
    Clock clock;

    while (true) {
        Time dt = clock.restart();
        timeSinceLastMove += dt;

        handleInput(window);

        switch (currentGameState) {
            case GameState::PAUSED:
                sleep; // sleep so we don't peg the CPU
                // otherwise the loop will be iterating as fast as it possibly can
                break;
            case GameState::GAMEOVER:
                draw(window);
                sleep;
                break;
            case GameState::EXIT:
                return;
            default:
                if (timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds())
                    update();
                draw(window);
        }
    }
}

void Game::draw(RenderWindow &window) {
    window.clear(Color::Black);

    // draw walls
    for (auto &w : walls)
        window.draw(w.getShape());
    
    // draw food
    window.draw(food.getApple());

    // draw snake
    snake.draw(window);

    window.display();
}
