#include "../headers/game.hpp"

void Game::update() {
    // update snake positions
    if (timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds()) {
        Vector2f thisSectionPosition = head.getPosition();
        Vector2f lastSectionPosition = thisSectionPosition;

        // does the snake need to change direction? (anything in the input queue?)
        if (!directionQueue.empty()) {
            // make sure we don't reverse direction
            switch (snakeDirection) {
                case Direction::UP:
                    if (directionQueue.front() != Direction::DOWN)
                        snakeDirection = directionQueue.front();
                    break;
                case Direction::DOWN:
                    if (directionQueue.front() != Direction::UP)
                        snakeDirection = directionQueue.front();
                    break;
                case Direction::RIGHT:
                    if (directionQueue.front() != Direction::LEFT)
                        snakeDirection = directionQueue.front();
                    break;
                case Direction::LEFT:
                    if (directionQueue.front() != Direction::RIGHT)
                        snakeDirection = directionQueue.front();
                    break;
                default:
                    break;
            }
            // remove the front of the queue
            directionQueue.pop_front();
        }

    // do we need to grow the snake
    if (sectionsToAdd) {
      addSnakeSection();
      sectionsToAdd--;
    }

    // update the head position
    switch (snakeDirection) {
            case Direction::UP:
                head.setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y - BLOCK));
                break;
            case Direction::DOWN:
                head.setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y + BLOCK));
                break;
            case Direction::RIGHT:
                head.setPosition(Vector2f(thisSectionPosition.x + BLOCK, thisSectionPosition.y));
                break;
            case Direction::LEFT:
                head.setPosition(Vector2f(thisSectionPosition.x - BLOCK, thisSectionPosition.y));
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

    // Collision detection - Food
    if (head.getShape().getGlobalBounds().intersects(food.getAppleSpace().getGlobalBounds())) {
        // We hit the food, add more sections to the snake, increase speed and move the food
        // TODO - increment score, foods eaten, add snake sections and check if its time for the next level

        sectionsToAdd++;
        if (acceleration) speed++;
        moveFood();
    }

    // snake body detection
    for (size_t s = 1; s <snake.size(); s++)
        if (head.getShape().getGlobalBounds().intersects(snake[s].getShape().getGlobalBounds()))
            // snake ate itself: gameover
            currentGameState = GameState::GAMEOVER;
    
    // reset the last move timer
    timeSinceLastMove = Time::Zero;
  } // ENDIF: update snake position
}