#include "../headers/game.hpp"

void Game::update() {
    // update snake positions
    if(timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds()) {
        Vector2f thisSectionPosition = snake[0].getPosition();
        Vector2f lastSectionPosition = thisSectionPosition;

        // does the snake need to change direction? (anything in the input queue?)
        if (!directionQueue.empty()) {
            // make sure we don't reverse direction
            switch (snakeDirection) {
                case Direction::UP:
                    if(directionQueue.front() != Direction::DOWN) {
                        snakeDirection = directionQueue.front();
                    }
                    break;
                case Direction::DOWN:
                    if(directionQueue.front() != Direction::UP) {
                        snakeDirection = directionQueue.front();
                    }
                    break;
                case Direction::RIGHT:
                    if(directionQueue.front() != Direction::LEFT) {
                        snakeDirection = directionQueue.front();
                    }
                    break;
                case Direction::LEFT:
                    if(directionQueue.front() != Direction::RIGHT) {
                        snakeDirection = directionQueue.front();
                    }
                    break;
                default:
                    break;
            }
            // remove the front of the queue
            directionQueue.pop_front();
        }

        // update the head position
        switch (snakeDirection) {
            case Direction::UP:
                snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
                break;
            case Direction::DOWN:
                snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
                break;
            case Direction::RIGHT:
                snake[0].setPosition(Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
                break;
            case Direction::LEFT:
                snake[0].setPosition(Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
                break;
        
            default:
                break;
        }

        //update the snake tail positions

        for(size_t s = 1; s<snake.size(); s++) {
            thisSectionPosition = snake[s].getPosition();
            snake[s].setPosition(lastSectionPosition);
            lastSectionPosition = thisSectionPosition;
        }

        // run snake section update function
        for (auto & s : snake) {
            s.update();
        }

        // reset the last move timer
        timeSinceLastMove = Time::Zero;
    } // ENDIF: update snake position
}