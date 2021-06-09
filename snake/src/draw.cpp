#include "../headers/game.hpp"

void Game::draw() {
    window.clear(Color::Black);

    //newSnake();
    for(auto & s : snake) {
        window.draw(s.getShape());
    }

    window.display();
}