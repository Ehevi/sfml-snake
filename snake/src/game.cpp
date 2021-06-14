#include "../headers/game.hpp"
#include "../headers/wall.hpp"
#include "../headers/utils.hpp"

Game::Game() {
    loadFont(font);

    scoreText.setCharacterSize(SMALL_FONT_SIZE);
    scoreText.setString("Score: ");
    scoreText.setFont(font);
    scoreText.setPosition(GAME_TEXT_MARGIN, GAME_TEXT_MARGIN);
    
    gameTimeText.setCharacterSize(SMALL_FONT_SIZE);
    gameTimeText.setString("Time: ");
    gameTimeText.setFont(font);
    gameTimeText.setPosition(GAME_TEXT_MARGIN, SCREEN_HEIGHT - 2 * GAME_TEXT_MARGIN);
    
    _Paused.setCharacterSize(LARGE_FONT_SIZE);
    _Paused.setString("Paused\n");
    _Paused.setFont(font);
    center(_Paused);

    _PressSpace.setCharacterSize(SMALL_FONT_SIZE);
    _PressSpace.setString("\nPress space to continue");
    _PressSpace.setFont(font);
    center(_PressSpace);

    _GameOver.setCharacterSize(LARGE_FONT_SIZE);
    _GameOver.setString("Game Over!\n");
    _GameOver.setFont(font);
    center(_GameOver);

    _PressAny.setCharacterSize(SMALL_FONT_SIZE);
    _PressAny.setString("\nPress any key to continue");
    _PressAny.setFont(font);
    center(_PressAny);
}

void Game::newGame(RenderWindow &window, Vector2f gameResolution, int newInitialSpeed, bool newAcceleration, bool newWallsAround, bool newWallGeneration) {
    srand(time(nullptr)); // for food and walls generation

    resolution = gameResolution;
    initialSpeed = newInitialSpeed;
    speed = initialSpeed;
    acceleration = newAcceleration;
    wallsAround = newWallsAround;
    wallGeneration = newWallGeneration;

    score = 0;
    
    gameClock.restart();
    timeSinceLastMove = Time::Zero;
    totalPausedTime = Time::Zero;
    pausedSince = Time::Zero;

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

    // divide the field into sections the size of block
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

        if (snake.intersects(Rect<float>(newFoodPosition.x, newFoodPosition.y, newFoodPosition.x + BLOCK, newFoodPosition.y + BLOCK)))
            badPosition = true; // food was generated inside the snake
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
            pausedSince = gameClock.getElapsedTime();
            prevGameState = currentGameState;
            currentGameState = GameState::PAUSED;
            break;
        case GameState::PAUSED:
            totalPausedTime += gameClock.getElapsedTime() - pausedSince;
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
            case GameState::GAMEOVER:
                draw(window);
                sleep; // sleep so we don't peg the CPU
                // otherwise the loop will be iterating as fast as it possibly can
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

    window.draw(scoreText);
    window.draw(gameTimeText);

    switch (currentGameState) {
        case GameState::PAUSED:
            window.draw(_Paused);
            window.draw(_PressSpace);
            break;
        case GameState::GAMEOVER:
            window.draw(_GameOver);
            window.draw(_PressAny);
            break;
        default:
            break;
    }
    window.display();
}
