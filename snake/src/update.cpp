#include "../headers/game.hpp"

void Game::update() {
    // does the snake need to change direction? (anything in the input queue?)
    if (!directionQueue.empty()) {
        // make sure we don't reverse direction
        switch (snake.getDirection()) {
            case Direction::UP:
                if (directionQueue.front() != Direction::DOWN)
                    snake.setDirection(directionQueue.front()); // = directionQueue.front();
                break;
            case Direction::DOWN:
                if (directionQueue.front() != Direction::UP)
                    snake.setDirection(directionQueue.front());
                    //snakeDirection = directionQueue.front();
                break;
            case Direction::RIGHT:
                if (directionQueue.front() != Direction::LEFT)
                    snake.setDirection(directionQueue.front());
                    //snakeDirection = directionQueue.front();
                break;
            case Direction::LEFT:
                if (directionQueue.front() != Direction::RIGHT)
                    snake.setDirection(directionQueue.front());
                    //snakeDirection = directionQueue.front();
                break;
            default:
                break;
        }
        
        // remove the front of the queue
        directionQueue.pop_front();
    }

    // do we need to grow the snake
    if (sectionsToAdd) {
        snake.addSection();
        // addSnakeSection();
        sectionsToAdd--;
    }

    snake.update();
/*
    // update the head position
    switch (snake.getDirection()) {
        case Direction::UP:
            snake.head().setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y - BLOCK));
            break;
        case Direction::DOWN:
            snake.head().setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y + BLOCK));
            break;
        case Direction::RIGHT:
            snake.head().setPosition(Vector2f(thisSectionPosition.x + BLOCK, thisSectionPosition.y));
            break;
        case Direction::LEFT:
            snake.head().setPosition(Vector2f(thisSectionPosition.x - BLOCK, thisSectionPosition.y));
            break;
        default:
            break;
    }

    //update the snake tail positions
    for (size_t s = 1; s<snake.size(); s++) {
        thisSectionPosition = snake[s].getPosition();
        snake[s].setPosition(lastSectionPosition);
        lastSectionPosition = thisSectionPosition;
    }

    // run snake section update function
    for (auto &s : snake)
        s.update();
    
    */

    // Collision detection - Food
    if (snake.ate(food.getAppleSpace().getGlobalBounds())) {
    // if (head.getShape().getGlobalBounds().intersects(food.getAppleSpace().getGlobalBounds())) {
    // We hit the food, add more sections to the snake, increase speed and move the food
    // TODO - increment score, foods eaten, add snake sections and check if its time for the next level

        sectionsToAdd++;
        if (acceleration) speed++;
        if (wallGeneration) generateRandomWall();
        moveFood();
    }

    // snake body detection
    if (snake.ateSelf())
        currentGameState = GameState::GAMEOVER;
    /*
    for (size_t s = 1; s <snake.size(); s++)
        if (head.getShape().getGlobalBounds().intersects(snake[s].getShape().getGlobalBounds()))
            // snake ate itself: gameover
            currentGameState = GameState::GAMEOVER;
    
    */

    // walls detection
    for (auto &w : walls)
        if(snake.ate(w.getShape().getGlobalBounds()))
        // if (head.getShape().getGlobalBounds().intersects(w.getShape().getGlobalBounds()))
            currentGameState = GameState::GAMEOVER;
    
    // reset the last move timer
    timeSinceLastMove = Time::Zero;
}