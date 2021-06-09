#include "../headers/game.hpp"

void Game::handleInput() {
    Event event{};
    while(window.pollEvent(event)) {
        switch(event.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                switch (event.key.code) {
                    case Keyboard::Escape:
                        window.close();
                        break;
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
                    default:
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