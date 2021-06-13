#include "../headers/game.hpp"

void Game::handleInput(RenderWindow &window) {
    Event event{};
    while(window.pollEvent(event)) {
        switch(event.type) {
            case Event::Closed:
                currentGameState = GameState::EXIT;
                break;
            case Event::KeyPressed:
                switch (event.key.code) {
                    case Keyboard::Escape:
                        currentGameState = GameState::EXIT;
                        return;
                    case Keyboard::Up:
                        addDirection(Direction::UP);
                        break;
                    case Keyboard::Down:
                        addDirection(Direction::DOWN);
                        break;
                    case Keyboard::Right:
                        addDirection(Direction::RIGHT);
                        break;
                    case Keyboard::Left:
                        addDirection(Direction::LEFT);
                        break;
                    case Keyboard::Space:
                        handlePause();
                        if (currentGameState == GameState::GAMEOVER) {
                            currentGameState = GameState::RUNNING;
                            newGame(window, resolution, initialSpeed, acceleration, wallsAround, wallGeneration);
                        }
                        break;
                    default:
                        if (currentGameState == GameState::GAMEOVER) {
                            currentGameState = GameState::RUNNING;
                            newGame(window, resolution, initialSpeed, acceleration, wallsAround, wallGeneration);
                        }
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void Game::addDirection(int newDirection) {
    if(directionQueue.empty()) {
        directionQueue.emplace_back(newDirection);
    } else {
        if(directionQueue.back() != newDirection) {
            directionQueue.emplace_back(newDirection);
        }
    }
}