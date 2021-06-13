#include "../headers/game.hpp"

void Game::update() {
    // does the snake need to change direction? (anything in the input queue?)
    if (!directionQueue.empty()) {
        // make sure we don't reverse direction
        switch (snake.getDirection()) {
            case Direction::UP:
                if (directionQueue.front() != Direction::DOWN)
                    snake.setDirection(directionQueue.front());
                break;
            case Direction::DOWN:
                if (directionQueue.front() != Direction::UP)
                    snake.setDirection(directionQueue.front());
                break;
            case Direction::RIGHT:
                if (directionQueue.front() != Direction::LEFT)
                    snake.setDirection(directionQueue.front());
                break;
            case Direction::LEFT:
                if (directionQueue.front() != Direction::RIGHT)
                    snake.setDirection(directionQueue.front());
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
        sectionsToAdd--;
    }

    snake.update();

    if (snake.ate(food.getAppleSpace().getGlobalBounds())) {
        score++;
        sectionsToAdd++;
        if (acceleration) speed++;
        if (wallGeneration) generateRandomWall();
        moveFood();
    }

    if (snake.ateSelf())
        currentGameState = GameState::GAMEOVER;

    // snake ate the wall
    for (auto &w : walls)
        if (snake.ate(w.getShape().getGlobalBounds()))
            currentGameState = GameState::GAMEOVER;
    
    Time gameTime = gameClock.getElapsedTime();
    scoreText.setString("Score: " + to_string(score));
    gameTimeText.setString("Time: " + to_string((int)(gameTime.asSeconds() - totalPausedTime.asSeconds())));
    
    // reset the last move timer
    timeSinceLastMove = Time::Zero;
}
