#include "../headers/game.hpp"

void Game::handleInput() {
    Event event{};
    while(window.pollEvent(event)) {
        switch(event.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                if(event.key.code == Keyboard::Escape) {
                    window.close();
                }
                break;
            default:
                break;
        }
    }
}